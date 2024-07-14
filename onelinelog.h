#ifndef ONELINELOG_H
#define ONELINELOG_H

#include <QLabel>
#include <QResizeEvent>

class OneLineLog : public QLabel
{
    Q_OBJECT

private:
    int msgId;
    QString msgText;
    void updateLog();

public:
    OneLineLog();
    void setMessage(QString msg);

protected:
    void resizeEvent(QResizeEvent* event);
};

#endif // ONELINELOG_H
