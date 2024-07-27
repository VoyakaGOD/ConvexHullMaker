#include "randompoint.h"

QPoint getPointInRect(const QRect &rect)
{
    QRandomGenerator *random = QRandomGenerator::global();
    int x = random->bounded(rect.x(), rect.x() + rect.width() + 1);
    int y = random->bounded(rect.y(), rect.y() + rect.height() + 1);
    return QPoint(x, y);
}
