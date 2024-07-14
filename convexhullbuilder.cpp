#include "convexhullbuilder.h"

ConvexHullBuilder::ConvexHullBuilder(const PointsAndHullStyle &style) : style(style)
{
    setFrameShape(QFrame::Shape::Panel);
    setFrameShadow(QFrame::Shadow::Raised);
    setLineWidth(2);
}

const QList<QPoint> &ConvexHullBuilder::getPoints() const
{
    return points;
}

const QList<QPoint> &ConvexHullBuilder::getHull() const
{
    return hull;
}

void ConvexHullBuilder::clear()
{
    points.clear();
    hull.clear();
    update();
}

void ConvexHullBuilder::updateHull()
{
    update();
}

void ConvexHullBuilder::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setBrush(QBrush(style.pointColor));
    painter.setPen(QPen(QBrush(style.pointStrokeColor), style.pointStrokeWidth));
    for(auto point : points)
        painter.drawEllipse(point, style.pointSize, style.pointSize);

    QFrame::paintEvent(event);
}

void ConvexHullBuilder::mousePressEvent(QMouseEvent *event)
{
    bool already_exists = false;
    for(int i = 0; i < points.size(); i++)
    {
        if(QVector2D(event->pos() - points[i]).lengthSquared() <= style.pointSize*style.pointSize)
        {
            points.removeAt(i);
            already_exists = true;
            break;
        }
    }

    if(!already_exists)
        points.push_back(event->pos());

    updateHull();
}
