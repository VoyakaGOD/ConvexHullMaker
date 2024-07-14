#ifndef ONELINELOG_H
#define ONELINELOG_H

#include <QLabel>

class OneLineLog : public QLabel
{
    Q_OBJECT

private:
    int msgId;

public:
    OneLineLog();
    void setMessage(QString msg);
};

#endif // ONELINELOG_H
