#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window(QFileInfo(argv[0]).absolutePath() + "/_.svg");
    window.show();
    return a.exec();
}
