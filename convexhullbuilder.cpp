#include "convexhullbuilder.h"

ConvexHullBuilder::ConvexHullBuilder(const PointsAndHullStyle &style, const QVector<QPoint> &points) :
    style(style), points(points), hull(points)
{
    setFrameShape(QFrame::Shape::Panel);
    setFrameShadow(QFrame::Shadow::Raised);
    setLineWidth(2);
}

const QVector<QPoint> &ConvexHullBuilder::getPoints() const
{
    return points;
}

const QVector<QPoint> &ConvexHullBuilder::getHull() const
{
    return hull.getPoints();
}

void ConvexHullBuilder::clear(ActionHistory *history)
{
    points.clear();
    hull.clear();
    update();
}

void ConvexHullBuilder::addPoint(QPoint point, ActionHistory *history)
{
    if(history)
    {
        int index = points.size();
        ReversibleAction action("",
                                new LambdaAction([this, point](){ addPoint(point);}),
                                "",
                                new LambdaAction([this, index](){ removePoint(index);}));
        history->addRecord(action);
    }

    points.push_back(point);
    hull.addPoint(point);
    update();
}

void ConvexHullBuilder::removePoint(int index, ActionHistory *history)
{
    int hullPointIndex = hull.getPoints().indexOf(points[index]);
    if(hullPointIndex > -1)
        hull.removePoint(hullPointIndex);
    points.removeAt(index);
    update();
}

void ConvexHullBuilder::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    const QVector<QPoint> &hullPoints = hull.getPoints();
    painter.setPen(QPen(QBrush(style.hullLineColor), style.hullLineWidth));
    painter.drawPolyline(hullPoints);
    if(hullPoints.size() > 2)
        painter.drawLine(hullPoints.first(), hullPoints.last());

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
        if(getSquaredDistance(event->pos(), points[i]) <= style.pointSize*style.pointSize)
        {
            removePoint(i);
            already_exists = true;
            break;
        }
    }

    if(!already_exists)
        addPoint(event->pos());
}
