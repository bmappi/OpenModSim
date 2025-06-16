#include <QRegularExpressionValidator>
#include <QMimeData>
#include "formatutils.h"
#include "bytelisttextedit.h"

///
/// \brief ByteListTextEdit::ByteListTextEdit
/// \param parent
///
ByteListTextEdit::ByteListTextEdit(QWidget* parent)
    :QPlainTextEdit(parent)
    ,_separator(' ')
    ,_validator(nullptr)
{
    setInputMode(DecMode);
    connect(this, &QPlainTextEdit::textChanged, this, &ByteListTextEdit::on_textChanged);
}

///
/// \brief ByteListTextEdit::ByteListTextEdit
/// \param mode
/// \param parent
///
ByteListTextEdit::ByteListTextEdit(InputMode mode, QWidget *parent)
    :QPlainTextEdit(parent)
    ,_separator(' ')
    ,_validator(nullptr)
{
    setInputMode(mode);
    connect(this, &QPlainTextEdit::textChanged, this, &ByteListTextEdit::on_textChanged);
}

///
/// \brief ByteListTextEdit::value
/// \return
///
QByteArray ByteListTextEdit::value() const
{
    return _value;
}

///
/// \brief ByteListTextEdit::setValue
/// \param value
///
void ByteListTextEdit::setValue(const QByteArray& value)
{
    switch(_inputMode)
    {
        case DecMode:
        {
            const auto text = formatUInt8Array(DataDisplayMode::UInt16, value);
            if(text != toPlainText())
                setPlainText(formatUInt8Array(DataDisplayMode::UInt16, value));
        }
        break;

        case HexMode:
        {
            const auto text = formatUInt8Array(DataDisplayMode::Hex, value);
            if(text != toPlainText())
                setPlainText(formatUInt8Array(DataDisplayMode::Hex, value));
        }
        break;
    }

    if(value != _value)
    {
        _value = value;
        emit valueChanged(_value);
    }
}

///
/// \brief ByteListTextEdit::inputMode
/// \return
///
ByteListTextEdit::InputMode ByteListTextEdit::inputMode() const
{
    return _inputMode;
}

///
/// \brief ByteListTextEdit::setInputMode
/// \param mode
///
void ByteListTextEdit::setInputMode(InputMode mode)
{
    _inputMode = mode;

    if(_validator)
    {
        delete _validator;
        _validator = nullptr;
    }

    const auto sep = (_separator == ' ')? "\\s" : QString(_separator);
    switch(_inputMode)
    {
        case DecMode:
            _validator =new QRegularExpressionValidator(QRegularExpression("(?:[0-9]{1,2}[" + sep + "]{0,1})*"), this);
        break;

        case HexMode:
            _validator = new QRegularExpressionValidator(QRegularExpression("(?:[0-9a-fA-F]{1,2}[" + sep + "]{0,1})*"), this);
        break;
    }

    setValue(_value);
}

///
/// \brief ByteListTextEdit::text
/// \return
///
QString ByteListTextEdit::text() const
{
    return toPlainText();
}

///
/// \brief ByteListTextEdit::setText
/// \param text
///
void ByteListTextEdit::setText(const QString& text)
{
    setPlainText(text);
    updateValue();
}

///
/// \brief ByteListTextEdit::focusOutEvent
/// \param event
///
void ByteListTextEdit::focusOutEvent(QFocusEvent* e)
{
    updateValue();
    QPlainTextEdit::focusOutEvent(e);
}

///
/// \brief ByteListTextEdit::keyPressEvent
/// \param e
///
void ByteListTextEdit::keyPressEvent(QKeyEvent *e)
{
    if(!_validator)
    {
        QPlainTextEdit::keyPressEvent(e);
        return;
    }

    if(e->key() == Qt::Key_Enter ||
       e->key() == Qt::Key_Return)
    {
        return;
    }

    int pos = 0;
    auto text = toPlainText() + e->text();
    const auto state = _validator->validate(text, pos);

    if(state == QValidator::Acceptable ||
        e->key() == Qt::Key_Backspace ||
        e->key() == Qt::Key_Delete ||
        e->key() == Qt::Key_Space ||
        e->matches(QKeySequence::Cut) ||
        e->matches(QKeySequence::Copy) ||
        e->matches(QKeySequence::Paste) ||
        e->matches(QKeySequence::Undo) ||
        e->matches(QKeySequence::Redo) ||
        e->matches(QKeySequence::SelectAll))
    {
        QPlainTextEdit::keyPressEvent(e);
    }
}

///
/// \brief ByteListTextEdit::canInsertFromMimeData
/// \param source
/// \return
///
bool ByteListTextEdit::canInsertFromMimeData(const QMimeData* source) const
{
    int pos = 0;
    auto text = source->text().trimmed();
    const auto state = _validator->validate(text, pos);

    return state == QValidator::Acceptable;
}

///
/// \brief ByteListTextEdit::insertFromMimeData
/// \param source
///
void ByteListTextEdit::insertFromMimeData(const QMimeData* source)
{
    int pos = 0;
    auto text = source->text().trimmed();
    const auto state = _validator->validate(text, pos);

    if(state == QValidator::Acceptable)
    {
        QPlainTextEdit::insertFromMimeData(source);
        updateValue();
    }
}

///
/// \brief ByteListTextEdit::on_textChanged
///
void ByteListTextEdit::on_textChanged()
{
    QByteArray value;
    switch(_inputMode)
    {
        case DecMode:
        {
            for(auto&& s : text().split(_separator))
            {
                bool ok;
                const quint8 v = s.trimmed().toUInt(&ok);
                if(ok) value.push_back(v);
            }
        }
        break;

        case HexMode:
        {
            for(auto&& s : text().split(_separator))
            {
                bool ok;
                const quint8 v = s.trimmed().toUInt(&ok, 16);
                if(ok) value.push_back(v);
            }
        }
        break;
    }

    if(value != _value)
    {
        _value = value;
        emit valueChanged(_value);
    }
}

///
/// \brief ByteListTextEdit::updateValue
///
void ByteListTextEdit::updateValue()
{
    QByteArray value;
    switch(_inputMode)
    {
        case DecMode:
        {
            for(auto&& s : text().split(_separator))
            {
                bool ok;
                const quint8 v = s.trimmed().toUInt(&ok);
                if(ok) value.push_back(v);
            }

            if(!value.isEmpty()) setValue(value);
            else setValue(_value);
        }
        break;

        case HexMode:
        {
            for(auto&& s : text().split(_separator))
            {
                bool ok;
                const quint8 v = s.trimmed().toUInt(&ok, 16);
                if(ok) value.push_back(v);
            }

            if(!value.isEmpty()) setValue(value);
            else setValue(_value);
        }
        break;
    }
}
