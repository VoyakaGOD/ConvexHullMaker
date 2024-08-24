#include "onelinelog.h"

#define MAX_PART 0.95f

OneLineLog::OneLineLog() : msgId(0)
{
    msgText = "Here will be information about your latest activities.";
    updateLog();
}

void OneLineLog::updateLog()
{
    QString text = QString::number(msgId) + "::" + msgText;

    float targetWidth = QFontMetrics(font()).boundingRect(text).width();
    float part = targetWidth / width();

    if(part > MAX_PART)
        text = text.left(MAX_PART * text.length() / part) + ".....";

    setText(text);
}

void OneLineLog::setMessage(QString msg)
{
    msgId++;
    msgText = msg;
    updateLog();
}

void OneLineLog::resizeEvent(QResizeEvent* event)
{
    updateLog();
}
