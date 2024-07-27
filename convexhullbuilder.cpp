#include "convexhullbuilder.h"

ConvexHullBuilder::ConvexHullBuilder(const PointsAndHullStyle &style, const QVector<QPoint> &points) :
    style(style), points(points), hull(points), history(nullptr)
{
    setFrameShape(QFrame::Shape::Panel);
    setFrameShadow(QFrame::Shadow::Raised);
    setLineWidth(2);
}

void ConvexHullBuilder::setHistoryPointer(ActionHistory *history)
{
    this->history = history;
}

const QVector<QPoint> &ConvexHullBuilder::getPoints() const
{
    return points;
}

const QVector<QPoint> &ConvexHullBuilder::getHull() const
{
    return hull.getPoints();
}

void ConvexHullBuilder::clear(bool __keep)
{
    if(history && __keep)
    {
        QVector<QPoint> oldPoints = points;
        ReversibleAction action("All[" + QString::number(points.size()) + "] points have been removed again!",
                                new LambdaAction([this](){ clear(false); }),
                                "All[" + QString::number(points.size()) + "] points have been restored!",
                                new LambdaAction([this, oldPoints](){ for(const auto &point : oldPoints) addPoint(point, false); }));
        history->addRecord(action);
    }

    points.clear();
    hull.clear();
    update();
}

void ConvexHullBuilder::addPoint(QPoint point, bool __keep)
{
    if(history && __keep)
    {
        int index = points.size();
        ReversibleAction action("",
                                new LambdaAction([this, point](){ addPoint(point, false); }),
                                "",
                                new LambdaAction([this, index](){ removePoint(index, false); }));
        history->addRecord(action);
    }

    points.push_back(point);
    hull.addPoint(point);
    update();
}

void ConvexHullBuilder::removePoint(int index, bool __keep)
{   
    if(history && __keep)
    {
        QPoint point = points[index];
        ReversibleAction action("",
                                new LambdaAction([this, index](){ removePoint(index, false); }),
                                "",
                                new LambdaAction([this, point](){ addPoint(point, false); }));
        history->addRecord(action);
    }

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
