#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QList>
#include <QPoint>
#include "pointsandhullstyle.h"

class FileUtils
{
public:
    FileUtils() = delete;

    static bool createSVG(const QList<QPoint> &points, const QList<QPoint> &hull, QString savePath, const PointsAndHullStyle &style);
    static QString getVacantName(QString name);
};

#endif // FILEUTILS_H
