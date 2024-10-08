#include "convexhullbuilder.h"

#define FRAME_WIDTH 2

ConvexHullBuilder::ConvexHullBuilder(const PointsAndHullStyle &style, int initialPointsCount) : style(style), history(nullptr)
{
    setFrameShape(QFrame::Shape::Panel);
    setFrameShadow(QFrame::Shadow::Raised);
    setLineWidth(FRAME_WIDTH);

    generateRandomPoints(initialPointsCount);
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
        ConvexPolygon oldHull = hull;
        ReversibleAction action("All[" + QString::number(points.size()) + "] points have been removed again!",
                                new LambdaAction([this](){ clear(false); }),
                                "All[" + QString::number(points.size()) + "] points have been restored!",
                                new LambdaAction([this, oldPoints, oldHull](){
                                    points = oldPoints;
                                    hull = oldHull;
                                    update();
                                }));
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
    points.removeAt(index);
    if(hullPointIndex > -1)
    {
        const QVector<QPoint> &hullPoints = hull.getPoints();
        int cnt = hullPoints.size();
        QVector<QPoint> fragmentPoints;
        for(auto point : points)
            if(isPointInTriangle(hullPoints[(hullPointIndex + cnt - 1) % cnt],
                                hullPoints[hullPointIndex],
                                hullPoints[(hullPointIndex + 1) % cnt], point))
                fragmentPoints << point;
        ConvexPolygon fragment(fragmentPoints);

        hull.removePoint(hullPointIndex);
        hull.MergeWith(fragment);
    }

    update();
}

int ConvexHullBuilder::generateRandomPoints(int count)
{
    QVector<QPoint> oldPoints;
    ConvexPolygon oldHull;
    if(history)
    {
        oldPoints = points;
        oldHull = hull;
    }

    points.clear();
    while((count--) > 0)
    {
        QPoint newPoint = getPointInRect(FRAME_WIDTH, FRAME_WIDTH, width() - FRAME_WIDTH, height() - FRAME_WIDTH);
        if(points.indexOf(newPoint) < 0)
            points << newPoint;
    }
    hull = ConvexPolygon(points);

    if(history)
    {
        QVector<QPoint> newPoints = points;
        ConvexPolygon newHull = hull;
        ReversibleAction action("New[" + QString::number(newPoints.size()) + "] points have been generated!",
                                new LambdaAction([this, newPoints, newHull](){
                                    points = newPoints;
                                    hull = newHull;
                                    update();
                                }),
                                "Old[" + QString::number(oldPoints.size()) + "] points have been restored!",
                                new LambdaAction([this, oldPoints, oldHull](){
                                    points = oldPoints;
                                    hull = oldHull;
                                    update();
                                }));
        history->addRecord(action);
    }

    update();
    return points.size();
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
