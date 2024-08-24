#include "mainwindow.h"

MainWindow::MainWindow(QString initialSavePath, const PointsAndHullStyle &style, int rnd) : style(style), randomPointsCount(rnd)
{
    QPushButton *fileDialogButton = new QPushButton("...");
    connect(fileDialogButton, &QPushButton::clicked, this, &MainWindow::onFileDialogRequested);
    pathEditor = new QLineEdit(initialSavePath);
    QHBoxLayout *pathLayout = new QHBoxLayout();
    pathLayout->addWidget(pathEditor);
    pathLayout->addWidget(fileDialogButton);

    QPushButton *saveButton = new QPushButton(QString(QChar(0x2193)));
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::onSaveRequested);
    QPushButton *clearButton = new QPushButton("clear(X)");
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::onClearingRequested);
    log = new OneLineLog();
    log->setSizePolicy(QSizePolicy::Expanding, log->sizePolicy().verticalPolicy());
    log->setWordWrap(true);
    rewriteOptionCheckBox = new QCheckBox("rewrite");
    QHBoxLayout *infoLayout = new QHBoxLayout();
    infoLayout->addWidget(log);
    infoLayout->addWidget(rewriteOptionCheckBox);
    infoLayout->addWidget(saveButton);
    infoLayout->addWidget(clearButton);

    builder = new ConvexHullBuilder(style, randomPointsCount);
    builder->setMinimumSize(700, 500);
    builder->setHistoryPointer(&history);
    auto verticalLayout = new QVBoxLayout(this);
    verticalLayout->addWidget(builder);
    verticalLayout->addLayout(pathLayout);
    verticalLayout->addLayout(infoLayout);

    setFocus();
    connect(new QShortcut(Qt::Key_X, this), &QShortcut::activated, this, &MainWindow::onClearingRequested);
    connect(new QShortcut(Qt::Key_P, this), &QShortcut::activated, this, &MainWindow::onFileDialogRequested);
    connect(new QShortcut(Qt::Key_R, this), &QShortcut::activated, this, &MainWindow::changeRewriteOption);
    connect(new QShortcut(Qt::Key_G, this), &QShortcut::activated, this, &MainWindow::onRandomPointsRequested);
    connect(new QShortcut(Qt::CTRL | Qt::Key_S, this), &QShortcut::activated, this, &MainWindow::onSaveRequested);
    connect(new QShortcut(Qt::CTRL | Qt::Key_Z, this), &QShortcut::activated, this, &MainWindow::onUndo);
    connect(new QShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_Z, this), &QShortcut::activated, this, &MainWindow::onRedo);
    connect(new QShortcut(Qt::CTRL | Qt::Key_Y, this), &QShortcut::activated, this, &MainWindow::onRedo);
}

void MainWindow::setHistoryCapacity(int capacity)
{
    history.setCapacity(capacity);
}

void MainWindow::onFileDialogRequested()
{
    QString newPath = QFileDialog::getSaveFileName(this, "select save directory", QFileInfo(pathEditor->text()).absoluteDir().path());
    if(newPath.isNull())
    {
        log->setMessage("File dialog was canceled!");
        return;
    }

    pathEditor->setText(newPath);
}

void MainWindow::onSaveRequested()
{
    QString path = pathEditor->text();
    if(!rewriteOptionCheckBox->isChecked())
        path = FileUtils::getVacantName(path);

    if(!FileUtils::createSVG(builder->getPoints(), builder->getHull(), path, style))
        log->setMessage("Can't save file with name [" + path +"]!");
    else
        log->setMessage("File saved with name [" + path + "]");
}

void MainWindow::onClearingRequested()
{
    log->setMessage("All[" + QString::number(builder->getPoints().size()) +"] points have been removed!");
    builder->clear();
}

void MainWindow::changeRewriteOption()
{
    rewriteOptionCheckBox->setChecked(!rewriteOptionCheckBox->isChecked());
}

void MainWindow::onUndo()
{
    QString message = history.undo();
    if(message.isEmpty())
        return;

    log->setMessage(message);
}

void MainWindow::onRedo()
{
    QString message = history.redo();
    if(message.isEmpty())
        return;

    log->setMessage(message);
}

void MainWindow::onRandomPointsRequested()
{
    log->setMessage("New[" + QString::number(randomPointsCount) + "] points have been generated!");
    builder->generateRandomPoints(randomPointsCount);
}
