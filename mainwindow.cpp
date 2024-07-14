#include "mainwindow.h"

MainWindow::MainWindow(QString initialSavePath, const PointsAndHullStyle &style) : savePath(initialSavePath), style(style)
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
    QPushButton *clearButton = new QPushButton("clear(X)");
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::onClearingRequested);
    log = new OneLineLog();
    log->setSizePolicy(QSizePolicy::Expanding, log->sizePolicy().verticalPolicy());
    rewriteOptionCheckBox = new QCheckBox("rewrite");
    QHBoxLayout *infoLayout = new QHBoxLayout();
    infoLayout->addWidget(log);
    infoLayout->addWidget(rewriteOptionCheckBox);
    infoLayout->addWidget(saveButton);
    infoLayout->addWidget(clearButton);

    builder = new ConvexHullBuilder(style);
    builder->setMinimumSize(700, 500);
    auto verticalLayout = new QVBoxLayout(this);
    verticalLayout->addWidget(builder);
    verticalLayout->addLayout(pathLayout);
    verticalLayout->addLayout(infoLayout);
}

void MainWindow::onFileDialogRequested()
{
    QString newPath = QFileDialog::getSaveFileName(this, "select save directory", QFileInfo(savePath).absoluteDir().path());
    if(newPath.isNull())
    {
        log->setMessage("File dialog was canceled!");
        return;
    }

    savePath = newPath;
    pathEditor->setText(savePath);
}

void MainWindow::onSaveRequested()
{
    QString path = savePath;
    if(rewriteOptionCheckBox->checkState() != Qt::CheckState::Checked)
        path = FileUtils::getVacantName(path);

    if(!FileUtils::createSVG(builder->getPoints(), builder->getPoints(), path, style))
        log->setMessage("Can't save file with name [" + path +"]!");
    else
        log->setMessage("File saved with name [" + path + "]");
}

void MainWindow::onClearingRequested()
{
    log->setMessage("All[" + QString::number(builder->getPoints().size()) +"] points removed!");
    builder->clear();
}
