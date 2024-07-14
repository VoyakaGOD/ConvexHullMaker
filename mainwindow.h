#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include "convexhullbuilder.h"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    QString savePath;
    QLineEdit *pathEditor;
    QLabel *log;
    QCheckBox *rewriteOptionCheckBox;
    ConvexHullBuilder *builder;

public:
    MainWindow(QString initialSavePath);

private slots:
    void onFileDialogRequested();
    void onSaveRequested();
};

#endif // MAINWINDOW_H
