#ifndef DIALOGFORCEMULTIPLECOILS_H
#define DIALOGFORCEMULTIPLECOILS_H

#include <QDialog>
#include <QTableWidgetItem>
#include <QModbusDataUnit>
#include "modbuswriteparams.h"

namespace Ui {
class DialogForceMultipleCoils;
}

class DialogForceMultipleCoils : public QDialog
{
    Q_OBJECT

public:
    explicit DialogForceMultipleCoils(ModbusWriteParams& params, QModbusDataUnit::RegisterType type, int length, bool hexAddress, QWidget *parent = nullptr);
    ~DialogForceMultipleCoils();

    void accept() override;

private slots:
    void on_pushButton0_clicked();
    void on_pushButton1_clicked();
    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);

private:
    void updateTableWidget();

private:
    Ui::DialogForceMultipleCoils *ui;
    QVector<quint16> _data;
    ModbusWriteParams& _writeParams;
    QModbusDataUnit::RegisterType _type;
    bool _hexAddress;
};

#endif // DIALOGFORCEMULTIPLECOILS_H
