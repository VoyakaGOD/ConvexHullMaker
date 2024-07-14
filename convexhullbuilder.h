#ifndef CONVEXHULLBUILDER_H
#define CONVEXHULLBUILDER_H

#include <QMouseEvent>
#include <QFrame>
#include <QPainter>
#include <Qlist>
#include <math.h>
#include "pointsandhullstyle.h"

class ConvexHullBuilder : public QFrame
{
    Q_OBJECT

private:
    QList<QPoint> points;
    QList<QPoint> hull;
    PointsAndHullStyle style;

    void updateHull();

public:
    ConvexHullBuilder(const PointsAndHullStyle &style);
    const QList<QPoint> &getPoints();
    const QList<QPoint> &getHull();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // CONVEXHULLBUILDER_H
