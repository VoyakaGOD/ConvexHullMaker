#include "onelinelog.h"

OneLineLog::OneLineLog() : msgId(0)
{
    setText("Thanks for using!!!");
}

void OneLineLog::setMessage(QString msg)
{
    msgId++;
    setText(QString::number(msgId) + "::" + msg);
}
