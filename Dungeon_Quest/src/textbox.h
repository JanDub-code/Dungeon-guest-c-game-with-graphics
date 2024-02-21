#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <QObject>

class TextBox : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString message READ getActiveMessage NOTIFY messageChanged)
private:
    static int m_message_index;
    static bool m_finished_reading;
    static std::vector<std::string> m_messages;
    static TextBox *m_instance;

    TextBox();
    ~TextBox();
public:
    static void setMessages(std::vector<std::string> messages);
    static QString getActiveMessage();
    static void nextMessage();
    static bool finishedReading();
    static void reset();
    static void instantiate();
    static void destroy();
    static TextBox *getInstance();
signals:
    void messageChanged();
};

#endif // TEXTBOX_H
