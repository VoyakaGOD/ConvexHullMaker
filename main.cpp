#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(QFileInfo(argv[0]).absolutePath() + "/_.svg");
    w.show();
    return a.exec();
}
