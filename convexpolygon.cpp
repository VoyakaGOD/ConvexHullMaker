#include "convexpolygon.h"

int getSquaredDistance(QPoint first, QPoint second)
{
    QPoint delta = second - first;
    return delta.x()*delta.x() + delta.y()*delta.y();
}

//f<-o->s
int getCrossProduct(QPoint origin, QPoint first, QPoint second)
{
    QPoint v1 = first - origin;
    QPoint v2 = second - origin;
    return v1.x()*v2.y() - v1.y()*v2.x();
}

//fo->fp<-so
int getConvergentCrossProduct(QPoint finalPoint, QPoint firstOrigin, QPoint secondOrigin)
{
    QPoint v1 = finalPoint - firstOrigin;
    QPoint v2 = finalPoint - secondOrigin;
    return v1.x()*v2.y() - v1.y()*v2.x();
}

//including interior only
bool isPointInTriangle(QPoint A, QPoint B, QPoint C, QPoint point)
{
    long long orientation = getCrossProduct(A, B, C);
    return (getCrossProduct(A, B, point) * orientation > 0) &&
        (getCrossProduct(B, C, point) * orientation > 0) &&
        (getCrossProduct(C, A, point) * orientation > 0);
}

//Graham scan
ConvexPolygon::ConvexPolygon(QVector<QPoint> points)
{
    if(points.size() <= 3)
    {
        for(auto point : points)
            addPoint(point);
        return;
    }

    int originIndex = 0;
    for(int i = 1; i < points.size(); i++)
    {
        if((points[i].y() < points[originIndex].y()) ||
            (points[i].y() == points[originIndex].y() && points[i].x() < points[originIndex].x()))
        {
            originIndex = i;
        }
    }

    QPoint origin = points[originIndex];
    std::swap(points[0], points[originIndex]);
    std::sort(points.begin() + 1, points.end(), [origin](QPoint left, QPoint right){ return getCrossProduct(origin, left, right) > 0; });

    int i = 1;
    QVector<QPoint> sparsePoints;
    sparsePoints << origin;
    while(points[i] == origin)
        i++;
    sparsePoints << points[i];
    for(i++; i < points.size();)
    {
        QPoint farthest = points[i];
        int maxSquaredDistance = getSquaredDistance(origin, farthest);
        i++;

        while((i < points.size()) && (getCrossProduct(origin, points[i], farthest) == 0))
        {
            if(getSquaredDistance(origin, points[i]) > maxSquaredDistance)
            {
                farthest = points[i];
                maxSquaredDistance = getSquaredDistance(origin, farthest);
            }
            i++;
        }
        sparsePoints << farthest;
    }

    this->points << sparsePoints[0];
    this->points << sparsePoints[1];
    this->points << sparsePoints[2];
    for (int i = 3; i < sparsePoints.size(); i++)
    {
        while (this->points.size() > 1 && getCrossProduct(this->points.back(), this->points[this->points.size() - 2], sparsePoints[i]) > 0)
            this->points.pop_back();
        this->points.push_back(sparsePoints[i]);
    }
}

void ConvexPolygon::addPoint(QPoint point)
{
    //creating first triangle
    if(points.size() < 3)
    {
        points.push_back(point);

        if((points.size() == 3) && (getCrossProduct(points[0], points[1], points[2]) < 0))
            std::swap(points[1], points[2]);

        return;
    }

    int segmentIndex = 0;
    int position = getRelativePosition(point, &segmentIndex);
    if(position >= 0)
    {
        if(position == 0)
            points.insert(segmentIndex + 1, point);
        return;
    }

    int indent = 0;
    while((indent < points.size()) && !isSegmentVisibleFrom(point, indent))
        indent++;

    int directIndex = indent;
    while((directIndex < points.size()) && isSegmentVisibleFrom(point, directIndex))
        directIndex++;

    //visible part not separated by zero index
    if((indent > 0) || !isSegmentVisibleFrom(point, points.size() - 1))
    {
        points.erase(points.cbegin() + indent + 1, points.cbegin() + directIndex);
        points.insert(indent + 1, point);
        return;
    }

    indent = directIndex;
    while((indent < points.size()) && !isSegmentVisibleFrom(point, indent))
        indent++;

    points.erase(points.cbegin() + indent + 1, points.cend());
    points.erase(points.cbegin(), points.cbegin() + directIndex);
    points.push_front(point);
}

void ConvexPolygon::removePoint(int index)
{
    points.removeAt(index);
}

//only for polygons with no intersections
void ConvexPolygon::MergeWith(const ConvexPolygon &other)
{
    points << other.points;
    ConvexPolygon merged(points);
    points = std::move(merged.points);
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

//positive result means that interior of polygon contains point
//zero means that point lying on border
//negative means that point is out of poly
int ConvexPolygon::getRelativePosition(QPoint point, int *segmentIndex) const
{
    if(points.size() < 3)
        return -1;

    int lowerBould = getLowerBoundIndexByAngleOf(point);
    if((lowerBould == 0) || (lowerBould == (points.size() - 1)))
        return -1;

    QPoint prevPoint = points[lowerBould];
    QPoint nextPoint = points[lowerBould + 1];

    int result = getCrossProduct(prevPoint, nextPoint, point);
    if(result == 0)
        *segmentIndex = lowerBould;
    return result;
}

bool ConvexPolygon::contains(QPoint point) const
{
    int unused = 0;
    return getRelativePosition(point, &unused) > 0;
}

bool ConvexPolygon::isSegmentVisibleFrom(QPoint point, int segmentIndex) const
{
    return getConvergentCrossProduct(points[(segmentIndex + 1) % points.size()], points[segmentIndex], point) > 0;
}

const QVector<QPoint> &ConvexPolygon::getPoints() const
{
    return points;
}

void ConvexPolygon::clear()
{
    points.clear();
}
