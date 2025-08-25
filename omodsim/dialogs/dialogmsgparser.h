#ifndef DIALOGMSGPARSER_H
#define DIALOGMSGPARSER_H

#include <QDialog>
#include "enums.h"
#include "modbusmessage.h"

namespace Ui {
class DialogMsgParser;
}

///
/// \brief The DialogMsgParser class
///
class DialogMsgParser : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMsgParser(DataDisplayMode mode, ModbusMessage::ProtocolType protocol, QWidget *parent = nullptr);
    ~DialogMsgParser();

protected:
    void changeEvent(QEvent* event) override;

private slots:
    void on_awake();
    void on_hexView_toggled(bool);
    void on_bytesData_valueChanged(const QByteArray& value);
    void on_pushButtonParse_clicked();

private:
    Ui::DialogMsgParser *ui;
    QSharedPointer<const ModbusMessage> _mm;
};

#endif // DIALOGMSGPARSER_H
