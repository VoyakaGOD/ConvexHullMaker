#include "convexpolygon.h"


int getSquaredDistance(QPoint first, QPoint second)
{
    QPoint delta = second - first;
    return delta.x()*delta.x() + delta.y()*delta.y();
}

int getCrossProduct(QPoint origin, QPoint first, QPoint second)
{
    QPoint v1 = first - origin;
    QPoint v2 = second - origin;
    return v1.x()*v2.y() - v1.y()*v2.x();
}

ConvexPolygon::ConvexPolygon(const QVector<QPoint> &points) : points(points) {}

//todo
void ConvexPolygon::addPoint(QPoint point)
{
    points.push_back(point);
}

//todo
void ConvexPolygon::removePoint(int index)
{
    points.removeAt(index);
}

//check
int ConvexPolygon::getLowerBoundIndexByAngleOf(QPoint point) const
{
    if(points.size() == 0)
        return -1;

    int count = points.size();
    int index = points.size() >> 1;
    while(count > 0)
    {
        count >>= 1;
        if(getCrossProduct(points[0], points[index], point) > 0)
            index += count >> 1;
        else
            index -= count >> 1;
    }

    return index;
}

bool ConvexPolygon::contains(QPoint point) const
{
    if(points.size() < 3)
        return false;

    int lowerBould = getLowerBoundIndexByAngleOf(point);
    QPoint prevPoint = points[lowerBould];
    QPoint nextPoint = points[(lowerBould + 1) % points.size()];

    return getCrossProduct(prevPoint, nextPoint, point) > 0;
}

QPoint ConvexPolygon::findTheNearestPointTo(QPoint point) const
{
    if(points.size() == 0)
        return QPoint();

    if(points.size() == 1)
        return points[0];

    QPoint result = points[0];
    int minSquaredDistance = getSquaredDistance(point, result);
    for(auto polyPoint : points)
    {
        int squaredDistance = getSquaredDistance(polyPoint, point);
        if(squaredDistance < minSquaredDistance)
        {
            minSquaredDistance = squaredDistance;
            result = polyPoint;
        }
    }

    return result;
}

const QVector<QPoint> &ConvexPolygon::getPoints() const
{
    return points;
}

void ConvexPolygon::clear()
{
    points.clear();
}
