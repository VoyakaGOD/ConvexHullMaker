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

public:
    ConvexHullBuilder(const PointsAndHullStyle &style, const QVector<QPoint> &points = QVector<QPoint>());
    const QVector<QPoint> &getPoints() const;
    const QVector<QPoint> &getHull() const;
    void addPoint(QPoint point, ActionHistory *history = nullptr);
    void removePoint(int index, ActionHistory *history = nullptr);
    void clear(ActionHistory *history = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // CONVEXHULLBUILDER_H
