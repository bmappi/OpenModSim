#ifndef DATASIMULATOR_H
#define DATASIMULATOR_H

#include <QTimer>
#include <QModbusDataUnit>
#include "modbussimulationparams.h"

typedef QMap<QPair<QModbusDataUnit::RegisterType, quint16>, ModbusSimulationParams> ModbusSimulationMap;

///
/// \brief The DataSimulator class
///
class DataSimulator : public QObject
{
    Q_OBJECT
public:
    explicit DataSimulator(QObject* parent = nullptr);
    ~DataSimulator() override;

    void startSimulation(DataDisplayMode mode, QModbusDataUnit::RegisterType type, quint16 addr, const ModbusSimulationParams& params);
    void stopSimulation(QModbusDataUnit::RegisterType type, quint16 addr);
    void stopSimulations();

    void pauseSimulations();
    void resumeSimulations();
    void restartSimulations();

    ModbusSimulationParams simulationParams(QModbusDataUnit::RegisterType type, quint16 addr) const;
    ModbusSimulationMap simulationMap() const;

signals:
    void simulationStarted(QModbusDataUnit::RegisterType type, quint16 addr);
    void simulationStopped(QModbusDataUnit::RegisterType type, quint16 addr);
    void dataSimulated(DataDisplayMode mode, QModbusDataUnit::RegisterType type, quint16 addr, QVariant value);

private slots:
    void on_timeout();

private:
    void randomSimulation(DataDisplayMode mode, QModbusDataUnit::RegisterType type, quint16 addr, const RandomSimulationParams& params);
    void incrementSimulation(DataDisplayMode mode, QModbusDataUnit::RegisterType type, quint16 addr, const IncrementSimulationParams& params);
    void decrementSimailation(DataDisplayMode mode, QModbusDataUnit::RegisterType type, quint16 addr, const DecrementSimulationParams& params);
    void toggleSimulation(QModbusDataUnit::RegisterType type, quint16 addr);

private:
    QTimer _timer;
    quint32 _elapsed;
    const int _interval = 1;

    struct SimulationParams {
        DataDisplayMode Mode;
        ModbusSimulationParams Params;
        QVariant CurrentValue;
    };
    QMap<QPair<QModbusDataUnit::RegisterType, quint16>, SimulationParams> _simulationMap;
};

#endif // DATASIMULATOR_H
