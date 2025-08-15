#ifndef DIALOGWRITEHOLDINGREGISTER_H
#define DIALOGWRITEHOLDINGREGISTER_H

#include "modbuswriteparams.h"
#include "modbussimulationparams.h"
#include "qfixedsizedialog.h"

namespace Ui {
class DialogWriteHoldingRegister;
}

///
/// \brief The DialogWriteHoldingRegister class
///
class DialogWriteHoldingRegister : public QFixedSizeDialog
{
    Q_OBJECT

public:
    explicit DialogWriteHoldingRegister(ModbusWriteParams& writeParams, ModbusSimulationParams& simParams, bool hexAddress, QWidget *parent = nullptr);
    ~DialogWriteHoldingRegister();

    void accept() override;

private slots:
    void on_pushButtonSimulation_clicked();

private:
    Ui::DialogWriteHoldingRegister *ui;

private:
    ModbusWriteParams& _writeParams;
    ModbusSimulationParams& _simParams;
};

#endif // DIALOGWRITEHOLDINGREGISTER_H
