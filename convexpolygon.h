#ifndef CONVEXPOLYGON_H
#define CONVEXPOLYGON_H

#include <QVector>
#include <QPoint>

int getSquaredDistance(QPoint first, QPoint second);
int getCrossProduct(QPoint origin, QPoint first, QPoint second);
int getConvergentCrossProduct(QPoint finalPoint, QPoint firstOrigin, QPoint secondOrigin);

class ConvexPolygon
{
private:
    //counterclock-wise
    QVector<QPoint> points;

public:
    ConvexPolygon(const QVector<QPoint> &points);
    void addPoint(QPoint point);
    void removePoint(int index);
    int getLowerBoundIndexByAngleOf(QPoint point) const;
    bool contains(QPoint point) const;
    QPoint findTheNearestPointTo(QPoint point, int *index = nullptr) const;
    const QVector<QPoint> &getPoints() const;
    void clear();
};

#endif // CONVEXPOLYGON_H
