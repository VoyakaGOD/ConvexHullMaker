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

public:
    MainWindow(QString initialSavePath,
               const PointsAndHullStyle &style = PointsAndHullStyle(),
               const QVector<QPoint> &initialPoints = QVector<QPoint>());
    void setHistoryCapacity(int capacity);

private slots:
    void onFileDialogRequested();
    void onSaveRequested();
    void onClearingRequested();
    void changeRewriteOption();
    void onUndo();
    void onRedo();
};

#endif // MAINWINDOW_H
