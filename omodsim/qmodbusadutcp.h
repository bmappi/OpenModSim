#ifndef QMODBUSADUTCP_H
#define QMODBUSADUTCP_H

#include "qmodbusadu.h"
#include "numericutils.h"

///
/// \brief The QModbusAduTcp class
///
class QModbusAduTcp : public QModbusAdu
{
public:
    explicit QModbusAduTcp(const QByteArray& rawData)
        : QModbusAdu()
    {
        setRawData(rawData);
    }

    ///
    /// \brief isValid
    /// \return
    ///
    bool isValid() const override {
        return _pdu.isValid() && length() == _pdu.size() + 1;
    }

    ///
    /// \brief setRawData
    /// \param data
    ///
    void setRawData(const QByteArray& data) override {
        _data = data;
        _pdu.setFunctionCode(QModbusPdu::FunctionCode((quint8)_data[7]));
        _pdu.setData(_data.mid(8));
    }

    ///
    /// \brief transactionId
    /// \return
    ///
    quint16 transactionId() const {
        return makeUInt16(_data[1], _data[0], ByteOrder::Direct);
    }

    ///
    /// \brief setTransactionId
    /// \param id
    ///
    void setTransactionId(quint16 id) {
        quint8 lo,hi;
        breakUInt16(id, lo, hi, ByteOrder::Direct);
        _data[1] = lo; _data[0] = hi;
    }

    ///
    /// \brief protocolId
    /// \return
    ///
    quint16 protocolId() const {
        return makeUInt16(_data[3], _data[2], ByteOrder::Direct);
    }

    ///
    /// \brief length
    /// \return
    ///
    quint16 length() const {
        return makeUInt16(_data[5], _data[4], ByteOrder::Direct);
    }

    ///
    /// \brief serverAddress
    /// \return
    ///
    quint8 serverAddress() const override {
        return quint8(_data[6]);
    }

};

#endif // QMODBUSADUTCP_H
