#ifndef CONVEXHULLBUILDER_H
#define CONVEXHULLBUILDER_H

#include <QMouseEvent>
#include <QFrame>
#include <QPainter>
#include <QVector>
#include <math.h>
#include "pointsandhullstyle.h"
#include "convexpolygon.h"

class ConvexHullBuilder : public QFrame
{
    Q_OBJECT

private:
    QVector<QPoint> points;
    ConvexPolygon hull;
    PointsAndHullStyle style;

public:
    ConvexHullBuilder(const PointsAndHullStyle &style);
    const QVector<QPoint> &getPoints() const;
    const QVector<QPoint> &getHull() const;
    void addPointToHull(QPoint point);
    void removePointFromHull(int index);
    void clear();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // CONVEXHULLBUILDER_H
