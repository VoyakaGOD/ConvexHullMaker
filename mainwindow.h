#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QFileDialog>
#include "convexhullbuilder.h"
#include "fileutils.h"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    QString savePath;
    QLineEdit *pathEditor;
    QLabel *log;
    QCheckBox *rewriteOptionCheckBox;
    ConvexHullBuilder *builder;
    PointsAndHullStyle style;

public:
    MainWindow(QString initialSavePath, const PointsAndHullStyle &style = PointsAndHullStyle());

private slots:
    void onFileDialogRequested();
    void onSaveRequested();
    void onClearingRequested();
};

#endif // MAINWINDOW_H
