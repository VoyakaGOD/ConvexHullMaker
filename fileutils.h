#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QVector>
#include <QPoint>
#include "pointsandhullstyle.h"

class FileUtils
{
public:
    FileUtils() = delete;

    static bool createSVG(const QVector<QPoint> &points, const QVector<QPoint> &hull, QString savePath, const PointsAndHullStyle &style);
    static QString getVacantName(QString name);
};

#endif // FILEUTILS_H
