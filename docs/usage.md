# Open ModSim Command Line Usage

Open ModSim supports a few command line options to customize its behavior at startup.

## Available Options

*   `--help`: Displays the help message listing these options.
*   `--version`: Displays the application version.
*   `--config <file path>`: Loads a previously saved configuration file automatically on startup.

## Auto-Connecting using `--config`

As of version 1.5.1, automatic connection is achieved by using a saved configuration file.

### How to Set Up Auto-Connection

1.  **Configure and Connect Manually:**
    *   Open Open ModSim.
    *   Set up your desired connection (Modbus/TCP or Serial) and any other settings (like data definitions) through the graphical interface.
    *   Establish the connection.
2.  **Save the Configuration:**
    *   Go to the **File** menu.
    *   Select **Save Config** (or **Save Config As...**).
    *   Choose a location and save the `.cfg` file (e.g., `config.bin`).
3.  **Use the `--config` Option:**
    *   Close Open ModSim if it's running.
    *   Start Open ModSim from the command line, providing the path to your saved configuration file using the `--config` option.

### Example Command

```bash
# On Windows
omodsim.exe --config "C:\path\to\your\config.bin"

# On Linux/macOS
./omodsim --config "/path/to/your/config.bin"