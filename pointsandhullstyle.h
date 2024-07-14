#ifndef POINTSANDHULLSTYLE_H
#define POINTSANDHULLSTYLE_H

#include <QColor>

struct PointsAndHullStyle
{
    int pointSize = 5;
    QColor pointColor = Qt::red;
    int pointStrokeWidth = 1;
    QColor pointStrokeColor = Qt::black;

    int hullLineWidth = 2;
    QColor hullLineColor = Qt::black;

    PointsAndHullStyle() = default;
};

#endif // POINTSANDHULLSTYLE_H
