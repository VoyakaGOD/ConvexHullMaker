#include "mainwindow.h"

MainWindow::MainWindow(QString initialSavePath)
{
    savePath = initialSavePath;

    QPushButton *fileDialogButton = new QPushButton("...");
    connect(fileDialogButton, &QPushButton::clicked, this, &MainWindow::onFileDialogRequested);
    pathEditor = new QLineEdit(savePath);
    QHBoxLayout *pathLayout = new QHBoxLayout();
    pathLayout->addWidget(pathEditor);
    pathLayout->addWidget(fileDialogButton);

    QPushButton *saveButton = new QPushButton(QString(QChar(0x2193)));
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::onSaveRequested);
    log = new QLabel("Thanks for using!!!");
    log->setSizePolicy(QSizePolicy::Expanding, log->sizePolicy().verticalPolicy());
    rewriteOptionCheckBox = new QCheckBox("rewrite");
    QHBoxLayout *infoLayout = new QHBoxLayout();
    infoLayout->addWidget(log);
    infoLayout->addWidget(rewriteOptionCheckBox);
    infoLayout->addWidget(saveButton);

    builder = new ConvexHullBuilder();
    builder->setMinimumSize(700, 500);
    auto verticalLayout = new QVBoxLayout(this);
    verticalLayout->addWidget(builder);
    verticalLayout->addLayout(pathLayout);
    verticalLayout->addLayout(infoLayout);
}

void MainWindow::onFileDialogRequested()
{

}

void MainWindow::onSaveRequested()
{

}
