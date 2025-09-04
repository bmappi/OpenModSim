#include <QApplication>
#include <QFontDatabase>
#include <QMessageBox>
#include <iostream>
#include <ios>

#ifdef Q_OS_WIN
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#endif
#include "mainwindow.h"
#include "cmdlineparser.h"
///
/// \brief enableConsole
/// Tries to attach to the parent console or allocates a new one.
///
static void enableConsole() {
#ifdef Q_OS_WIN
    // Try to attach to the parent process's console
    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
        // Successfully attached. Redirect stdout/stderr.
        // Get the standard output handle.
        HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
        int hCrt_out = _open_osfhandle((long) handle_out, _O_TEXT);
        FILE* hf_out = _fdopen(hCrt_out, "w");
        *stdout = *hf_out;
        // Get the standard error handle.
        HANDLE handle_err = GetStdHandle(STD_ERROR_HANDLE);
        int hCrt_err = _open_osfhandle((long) handle_err, _O_TEXT);
        FILE* hf_err = _fdopen(hCrt_err, "w");
        *stderr = *hf_err;

    } else if (GetLastError() == ERROR_ACCESS_DENIED) {
         // Console already exists but couldn't attach (e.g., run from IDE)
         // AllocConsole might fail if one already exists for the process.
         // Let's try AllocConsole anyway, it might work if not already allocated by *this* process.
         if (AllocConsole()) {
             // freopen to redirect standard streams to the new console
             // Use "CONOUT$" for output/error
             FILE* dummy;
             freopen_s(&dummy, "CONOUT$", "w", stdout);
             freopen_s(&dummy, "CONOUT$", "w", stderr);
             // Ensure C++ streams are synced
             std::cout.clear();
             std::clog.clear();
             std::cerr.clear();
         }
    } else {
        // No parent console, allocate a new one.
        if (AllocConsole()) {
            // Redirect standard input, output, and error streams to the new console.
            FILE* dummy;
            freopen_s(&dummy, "CONIN$", "r", stdin);
            freopen_s(&dummy, "CONOUT$", "w", stdout);
            freopen_s(&dummy, "CONOUT$", "w", stderr);
            // Ensure C++ streams are synced
            std::cout.clear();
            std::clog.clear();
            std::cerr.clear();
        }
    }
    // Make C++ streams use the new handles
    std::ios::sync_with_stdio(true);
#endif
}

///
/// \brief showVersion
/// \param useGui If true, shows a QMessageBox. If false, prints to stdout.
///
static inline void showVersion(bool useGui = false)
{
    const QString versionText = QString("%1\n").arg(APP_VERSION); // Ensure newline for console

    if (useGui) {
#ifdef Q_OS_WIN
        QMessageBox msgBox;
        msgBox.setWindowTitle(QApplication::applicationName());
        msgBox.setTextFormat(Qt::PlainText); // Ensure plain text
        msgBox.setText(versionText.trimmed()); // Remove trailing newline for GUI
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
#endif
    } else {
        fputs(qPrintable(versionText), stdout);
        fflush(stdout);
    }
}

///
/// \brief showHelp
/// \param helpText The help text to display.
/// \param useGui If true, shows a QMessageBox. If false, prints to stdout.
///
static inline void showHelp(const QString& helpText, bool useGui = false)
{
    // The help text from QCommandLineParser usually ends with \n, which is fine for console.
    // For GUI, we might want to remove the trailing newline for better appearance.
    const QString cleanHelpText = helpText.trimmed(); // Remove leading/trailing whitespace/newlines for GUI

    if (useGui) {
#ifdef Q_OS_WIN
        QMessageBox msgBox;
        msgBox.setWindowTitle(QObject::tr("Help")); // Or QApplication::applicationName() + " Help"
        msgBox.setTextFormat(Qt::PlainText); // Ensure plain text display
        msgBox.setText(cleanHelpText);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok);
        // Optional: Make it wider if help text is long
        // msgBox.setStyleSheet("QLabel{min-width: 400px; white-space: pre-wrap;}");
        msgBox.exec();
#endif
    } else {
        fputs(qPrintable(helpText), stdout); // Use original helpText including potential trailing \n
        fflush(stdout);
    }
}

///
/// \brief showErrorMessage
/// \param message The error message to display.
/// \param useGui If true, shows a QMessageBox. If false, prints to stderr.
///
static void showErrorMessage(const QString &message, bool useGui = false)
{
    const QString errorMessage = message + QLatin1Char('\n'); // Ensure newline for console

    if (useGui) {
#ifdef Q_OS_WIN
        QMessageBox msgBox;
        msgBox.setWindowTitle(QObject::tr("Error")); // Or QApplication::applicationName() + " Error"
        msgBox.setTextFormat(Qt::PlainText); // Ensure plain text
        msgBox.setText(message); // Message likely already formatted, no trim needed here usually
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
#endif
    } else {
        fputs(qPrintable(errorMessage), stderr);
        fflush(stderr);
    }
}


///
/// \brief main
/// \param argc
/// \param argv
/// \return
///
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(APP_NAME);
    a.setApplicationVersion(APP_VERSION);
    a.setStyle("windowsvista");

    QFontDatabase::addApplicationFont(":/fonts/firacode.ttf");

    CmdLineParser parser;
    if(!parser.parse(a.arguments()))
    {
        // Decide based on platform for error display during parsing
#ifdef Q_OS_WIN
        // On Windows, prefer GUI for startup errors if no console is obviously attached.
        // A simple heuristic: if launched from a console, stdout might work.
        // However, for errors during argument parsing, GUI is often clearer.
        // Let's default to GUI for startup errors on Windows.
        showErrorMessage(parser.errorText(), true); // Use GUI on Windows
#else
        showErrorMessage(parser.errorText(), false); // Use console on non-Windows
#endif
        return EXIT_FAILURE;
    }

    // Determine if we should use GUI for --help/--version
    // A simple heuristic for Windows: if we are likely run from a GUI context (e.g., double-clicked),
    // showing a message box is better. If run from console, printing is better.
    // AttachConsole can help detect this, but let's keep it simple for now.
    // We can assume GUI mode for --help/--version on Windows.
    bool useGuiForInfo = false;
#ifdef Q_OS_WIN
    useGuiForInfo = true;
    // Optional advanced check (uncomment if needed):
    // useGuiForInfo = !AttachConsole(ATTACH_PARENT_PROCESS); // If attach fails, likely no parent console
#endif


    if(parser.isSet(CmdLineParser::_version))
    {
        showVersion(useGuiForInfo);
        return EXIT_SUCCESS;
    }

    if(parser.isSet(CmdLineParser::_help))
    {
        showHelp(parser.helpText(), useGuiForInfo);
        return EXIT_SUCCESS;
    }

    QString cfg;
    if(parser.isSet(CmdLineParser::_config))
    {
        cfg = parser.value(CmdLineParser::_config);
        // If --config is used, we are likely run from console or script.
        enableConsole();
    }

    MainWindow w;
    if(!cfg.isEmpty())
    {
        w.loadConfig(cfg, true);
    }
    w.show();

    return a.exec();
}
