#include "convexhullbuilder.h"

ConvexHullBuilder::ConvexHullBuilder()
{
    setFrameShape(QFrame::Shape::Panel);
    setFrameShadow(QFrame::Shadow::Raised);
    setLineWidth(2);
}

const QList<QPoint> &ConvexHullBuilder::getPoint()
{
    return points;
}

const QList<QPoint> &ConvexHullBuilder::getHull()
{
    return hull;
}

void ConvexHullBuilder::updateHull()
{

}

void ConvexHullBuilder::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(QBrush(Qt::red));
    for(auto point : points)
        painter.drawEllipse(point, 5, 5);

    QFrame::paintEvent(event);
}

void ConvexHullBuilder::mousePressEvent(QMouseEvent *event)
{
    points.push_back(event->pos());
    updateHull();
    update();
}
