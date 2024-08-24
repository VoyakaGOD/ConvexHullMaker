#include "mainwindow.h"

#include <QApplication>
#include "commandlineparser.h"

int main(int argc, char *argv[])
{
    int one = 1;
    char *nameOnly[] = { argv[0] };
    QApplication a(one, nameOnly);
    a.setWindowIcon(QIcon(":/icons/appIcon.png"));

    CommandLineParser parser(argc, argv);

    PointsAndHullStyle style;
    style.pointSize = parser.getInteger("ps", style.pointSize, IntMinPredicate(1));
    style.pointColor = parser.getColor("pc", style.pointColor);
    style.pointStrokeWidth = parser.getInteger("psw", style.pointStrokeWidth, IntMinPredicate(1));
    style.pointStrokeColor = parser.getColor("psc", style.pointStrokeColor);
    style.hullLineWidth = parser.getInteger("hlw", style.hullLineWidth, IntAny());
    style.hullLineColor = parser.getColor("hlc", style.hullLineColor);

    int rnd = parser.getInteger("rnd", 0, IntClampPredicate(0, 100));
    int historyCapacity = parser.getInteger("undo", 100, IntMinPredicate(0));

    MainWindow window(QFileInfo(argv[0]).absolutePath() + "/_.svg", style, rnd);
    window.setHistoryCapacity(historyCapacity);
    window.show();

    return a.exec();
}
