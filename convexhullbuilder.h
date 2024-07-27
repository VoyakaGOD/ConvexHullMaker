#ifndef CONVEXHULLBUILDER_H
#define CONVEXHULLBUILDER_H

#include <QMouseEvent>
#include <QFrame>
#include <QPainter>
#include <QVector>
#include "pointsandhullstyle.h"
#include "convexpolygon.h"
#include "actionhistory.h"

class ConvexHullBuilder : public QFrame
{
    Q_OBJECT

private:
    QVector<QPoint> points;
    ConvexPolygon hull;
    PointsAndHullStyle style;
    ActionHistory *history;

public:
    ConvexHullBuilder(const PointsAndHullStyle &style, const QVector<QPoint> &points = QVector<QPoint>());
    void setHistoryPointer(ActionHistory *history);
    const QVector<QPoint> &getPoints() const;
    const QVector<QPoint> &getHull() const;
    void addPoint(QPoint point, bool __keep = true);
    void removePoint(int index, bool __keep = true);
    void clear(bool __keep = true);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // CONVEXHULLBUILDER_H
