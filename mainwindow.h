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
#include "actionhistory.h"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    QLineEdit *pathEditor;
    OneLineLog *log;
    QCheckBox *rewriteOptionCheckBox;
    ConvexHullBuilder *builder;
    PointsAndHullStyle style;
    ActionHistory history;
    int randomPointsCount;

public:
    MainWindow(QString initialSavePath, const PointsAndHullStyle &style = PointsAndHullStyle(), int rnd = 0);
    void setHistoryCapacity(int capacity);

private slots:
    void onFileDialogRequested();
    void onSaveRequested();
    void onClearingRequested();
    void changeRewriteOption();
    void onUndo();
    void onRedo();
    void onRandomPointsRequested();
};

#endif // MAINWINDOW_H
