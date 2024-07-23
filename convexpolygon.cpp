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

int getConvergentCrossProduct(QPoint finalPoint, QPoint firstOrigin, QPoint secondOrigin)
{
    QPoint v1 = finalPoint - firstOrigin;
    QPoint v2 = finalPoint - secondOrigin;
    return v1.x()*v2.y() - v1.y()*v2.x();
}

ConvexPolygon::ConvexPolygon(const QVector<QPoint> &points) : points(points) {}

void ConvexPolygon::addPoint(QPoint point)
{
    if(points.size() < 3)
    {
        points.push_back(point);

        if((points.size() == 3) && (getCrossProduct(points[0], points[1], points[2]) < 0))
            std::swap(points[1], points[2]);

        return;
    }

    if(contains(point))
        return;

    int directIndex = 0;
    findTheNearestPointTo(point, &directIndex);
    int reverseIndex = directIndex;

    while(getConvergentCrossProduct(points[(directIndex + 1) % points.size()], points[directIndex], point) > 0)
        directIndex = (directIndex + 1) % points.size();
    while(getConvergentCrossProduct(points[(reverseIndex + points.size() - 1) % points.size()], points[reverseIndex], point) < 0)
        reverseIndex = (reverseIndex + points.size() - 1) % points.size();

    if(reverseIndex > directIndex)
    {
        points.erase(points.cbegin() + reverseIndex + 1, points.cend());
        points.erase(points.cbegin(), points.cbegin() + directIndex);
        points.push_front(point);
    }
    else
    {
        points.erase(points.cbegin() + reverseIndex + 1, points.cbegin() + directIndex);
        points.insert(reverseIndex + 1, point);
    }
}

//todo
void ConvexPolygon::removePoint(int index)
{
    points.removeAt(index);
}

//zero means no lower bound
int ConvexPolygon::getLowerBoundIndexByAngleOf(QPoint point) const
{
    if(points.size() == 0)
        return 0;

    int low = 0;
    int high = points.size() - 1;

    while(low < high)
    {
        int mid = (low + high + 1) / 2;
        if(getCrossProduct(points[0], points[mid], point) >= 0)
            low = mid;
        else
            high = mid - 1;
    }

    return low;
}

bool ConvexPolygon::contains(QPoint point) const
{
    if(points.size() < 3)
        return false;

    int lowerBould = getLowerBoundIndexByAngleOf(point);
    if((lowerBould == 0) || (lowerBould == (points.size() - 1)))
        return false;

    QPoint prevPoint = points[lowerBould];
    QPoint nextPoint = points[(lowerBould + 1) % points.size()];

    return getCrossProduct(prevPoint, nextPoint, point) > 0;
}

QPoint ConvexPolygon::findTheNearestPointTo(QPoint point, int *index) const
{
    if(points.size() == 0)
    {
        if(index)
            *index = -1;
        return QPoint();
    }

    if(points.size() == 1)
    {
        if(index)
            *index = 0;
        return points[0];
    }

    int polyIndex = 0;
    QPoint result = points[0];
    int minSquaredDistance = getSquaredDistance(point, result);
    for(int i = 0; i < points.size(); i++)
    {
        QPoint polyPoint = points[i];
        int squaredDistance = getSquaredDistance(polyPoint, point);
        if(squaredDistance < minSquaredDistance)
        {
            minSquaredDistance = squaredDistance;
            result = polyPoint;
            polyIndex = i;
        }
    }

    if(index)
        *index = polyIndex;
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
