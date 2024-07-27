#include "commandlineparser.h"

CommandLineParser::CommandLineParser(int argc, char *argv[])
{
    for(int i = 0; i < argc; i++)
    {
        QStringList list = QString(argv[i]).split("=");
        if(list.size() != 2)
            continue;

        data[list[0]] = list[1];
    }
}

int CommandLineParser::getInteger(QString key, int defaultValue, const IntPredicate &predicate)
{
    bool ok = false;
    int value = data.value(key, "").toInt(&ok);
    if(ok && predicate(value))
        return value;
    return defaultValue;
}

QColor CommandLineParser::getColor(QString key, const QColor &defaultValue)
{
    QColor value(data.value(key, ""));
    if(value.isValid())
        return value;
    return defaultValue;
}
