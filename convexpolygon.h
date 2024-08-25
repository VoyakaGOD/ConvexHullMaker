#ifndef CONVEXPOLYGON_H
#define CONVEXPOLYGON_H

#include <QVector>
#include <QPoint>
#include <algorithm>

int getSquaredDistance(QPoint first, QPoint second);
int getCrossProduct(QPoint origin, QPoint first, QPoint second);
int getConvergentCrossProduct(QPoint finalPoint, QPoint firstOrigin, QPoint secondOrigin);

class ConvexPolygon
{
private:
    //counterclock-wise
    QVector<QPoint> points;

public:
    ConvexPolygon(QVector<QPoint> points = QVector<QPoint>());
    void addPoint(QPoint point);
    void removePoint(int index);
    void attachToTheSide(int side, const ConvexPolygon &other);
    int getLowerBoundIndexByAngleOf(QPoint point) const;
    int getRelativePosition(QPoint point, int *segmentIndex) const;
    bool contains(QPoint point) const;
    bool isSegmentVisibleFrom(QPoint point, int segmentIndex) const;
    const QVector<QPoint> &getPoints() const;
    void clear();
};

#endif // CONVEXPOLYGON_H
