#include "textbox.h"

int TextBox::m_message_index = 0;
bool TextBox::m_finished_reading = false;
std::vector<std::string> TextBox::m_messages = { "Sample text!" };
TextBox *TextBox::m_instance = nullptr;

TextBox::TextBox()
{
}

TextBox::~TextBox()
{
}

void TextBox::setMessages(std::vector<std::string> messages)
{
    m_messages = messages;
    emit m_instance->messageChanged();
}

QString TextBox::getActiveMessage()
{
    return QString::fromStdString(m_messages[m_message_index]);
}

void TextBox::nextMessage()
{
    if (m_message_index < int(m_messages.size()) - 1)
    {
        m_message_index++;
        emit m_instance->messageChanged();
    }
    else
    {
        m_finished_reading = true;
    }
}

bool TextBox::finishedReading()
{
    return m_finished_reading;
}

void TextBox::instantiate()
{
    if (!m_instance)
    {
        m_instance = new TextBox();
    }
}

void TextBox::destroy()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = nullptr;
    }
}

TextBox *TextBox::getInstance()
{
    return m_instance;
}

void TextBox::reset()
{
    m_message_index = 0;
    m_finished_reading = false;
    m_messages = { "Sample text!" };
    emit m_instance->messageChanged();
}
