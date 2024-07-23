#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QCheckBox>
#include <QFileDialog>
#include <QShortcut>
#include "convexhullbuilder.h"
#include "fileutils.h"
#include "onelinelog.h"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    QLineEdit *pathEditor;
    OneLineLog *log;
    QCheckBox *rewriteOptionCheckBox;
    ConvexHullBuilder *builder;
    PointsAndHullStyle style;

public:
    MainWindow(QString initialSavePath, const PointsAndHullStyle &style = PointsAndHullStyle());

private slots:
    void onFileDialogRequested();
    void onSaveRequested();
    void onClearingRequested();
    void changeRewriteOption();
};

#endif // MAINWINDOW_H
