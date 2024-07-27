#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include <QMap>
#include <QString>
#include <QColor>
#include "intpredicate.h"

class CommandLineParser
{
private:
    QMap<QString, QString> data;

public:
    CommandLineParser(int argc, char *argv[]);
    int getInteger(QString key, int defaultValue, const IntPredicate &predicate);
    QColor getColor(QString key, const QColor &defaultValue);
};

#endif // COMMANDLINEPARSER_H
