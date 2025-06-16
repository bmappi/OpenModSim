#ifndef DIALOGFORCEMULTIPLEREGISTERS_H
#define DIALOGFORCEMULTIPLEREGISTERS_H

#include <QDialog>
#include <QTableWidgetItem>
#include <QModbusDataUnit>
#include "numericlineedit.h"
#include "modbuswriteparams.h"

namespace Ui {
class DialogForceMultipleRegisters;
}

///
/// \brief The DialogForceMultipleRegisters class
///
class DialogForceMultipleRegisters : public QDialog
{
    Q_OBJECT

public:
    explicit DialogForceMultipleRegisters(ModbusWriteParams& params, QModbusDataUnit::RegisterType type, int length, QWidget *parent = nullptr);
    ~DialogForceMultipleRegisters();

    void accept() override;

private slots:
    void on_pushButton0_clicked();
    void on_pushButtonRandom_clicked();
    void on_pushButtonValue_clicked();

private:
    void updateTableWidget();
    QLineEdit* createLineEdit();
    NumericLineEdit* createNumEdit(int idx);

private:
    Ui::DialogForceMultipleRegisters *ui;
    QVector<quint16> _data;
    ModbusWriteParams& _writeParams;
    QModbusDataUnit::RegisterType _type;
    bool _hexView = false;
};

#endif // DIALOGFORCEMULTIPLEREGISTERS_H
