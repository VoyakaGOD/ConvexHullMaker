#include "randompoint.h"

QPoint getPointInRect(int minX, int minY, int maxX, int maxY)
{
    QRandomGenerator *random = QRandomGenerator::global();
    int x = random->bounded(minX, maxX + 1);
    int y = random->bounded(minY, maxY + 1);
    return QPoint(x, y);
}
