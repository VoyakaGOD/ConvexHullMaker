#ifndef CONVEXHULLBUILDER_H
#define CONVEXHULLBUILDER_H

#include <QMouseEvent>
#include <QFrame>
#include <QPainter>
#include <Qlist>
#include <math.h>

class ConvexHullBuilder : public QFrame
{
    Q_OBJECT

private:
    QList<QPoint> points;
    QList<QPoint> hull;

    void updateHull();

public:
    ConvexHullBuilder();
    const QList<QPoint> &getPoint();
    const QList<QPoint> &getHull();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // CONVEXHULLBUILDER_H
