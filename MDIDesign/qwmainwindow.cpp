#include "qwmainwindow.h"
#include "ui_qwmainwindow.h"
#include "qformdoc.h"
#include "QMdiSubWindow"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>

void QWMainWindow::closeEvent(QCloseEvent *event)
{
    ui->mdiArea->closeAllSubWindows(); //关闭所有子窗口
    event->accept();
}

QWMainWindow::QWMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QWMainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->mdiArea);
    this->setWindowState(Qt::WindowMaximized);
    ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

QWMainWindow::~QWMainWindow()
{
    delete ui;
}

void QWMainWindow::on_actDoc_new_triggered()
{
    QFormDoc *formDoc = new QFormDoc(this);
    ui->mdiArea->addSubWindow(formDoc);
    formDoc->show();
}

void QWMainWindow::on_actDoc_Open_triggered()
{
    bool needNew = false;
    QFormDoc *formDoc;
    if(ui->mdiArea->subWindowList().count() > 0)
    {
        formDoc = (QFormDoc*)ui->mdiArea->activeSubWindow()->widget();
        needNew = formDoc->isFileOpened();
    }
    else
        needNew = true;


    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getOpenFileName(this, "打开一个文件",
                        curPath, "C程序文件(*.h *.cpp);;所有文件(*.*)");
    if(aFileName.isEmpty())
        return;

    if(needNew)
    {
        formDoc = new QFormDoc(this);
        ui->mdiArea->addSubWindow(formDoc);
    }
    formDoc->loadFromFile(aFileName);
    formDoc->show();
    ui->actCut->setEnabled(true);
    ui->actCopy->setEnabled(true);
    ui->actPaste->setEnabled(true);
    ui->actSetFont->setEnabled(true);
}

void QWMainWindow::on_actMDI_triggered(bool checked)
{
    if(checked)
    {
        ui->mdiArea->setViewMode(QMdiArea::TabbedView);
        ui->mdiArea->setTabsClosable(true);
        ui->actCascade->setEnabled(false);
        ui->actTile->setEnabled(false);
    }
    else
    {
        ui->mdiArea->setViewMode(QMdiArea::SubWindowView);
        ui->actCascade->setEnabled(true);
        ui->actTile->setEnabled(true);
    }
}

void QWMainWindow::on_actCascade_triggered()
{
    ui->mdiArea->tileSubWindows();
}

void QWMainWindow::on_actTile_triggered()
{
    ui->mdiArea->cascadeSubWindows();
}

void QWMainWindow::on_actCloseAll_triggered()
{
    ui->mdiArea->closeAllSubWindows();
}

void QWMainWindow::on_mdiArea_subWindowActivated(QMdiSubWindow *arg1)
{
    Q_UNUSED(arg1);
    if(ui->mdiArea->subWindowList().count() == 0)
    {
        ui->actCut->setEnabled(false);
        ui->actCopy->setEnabled(false);
        ui->actPaste->setEnabled(false);
        ui->actSetFont->setEnabled(false);
        ui->statusbar->clearMessage();
    }
    else
    {
        QFormDoc* formDoc = static_cast<QFormDoc*>
                (ui->mdiArea->activeSubWindow()->widget());
        ui->statusbar->showMessage(formDoc->currentFileName());
        ui->actCut->setEnabled(true);
        ui->actCopy->setEnabled(true);
        ui->actPaste->setEnabled(true);
        ui->actSetFont->setEnabled(true);
    }
}

void QWMainWindow::on_actCut_triggered()
{
    QFormDoc* formDoc = (QFormDoc*)ui->mdiArea->activeSubWindow()->widget();
    formDoc->textCut();
}

void QWMainWindow::on_actCopy_triggered()
{
    QFormDoc* formDoc = (QFormDoc*)ui->mdiArea->activeSubWindow()->widget();
    formDoc->textCopy();
}

void QWMainWindow::on_actPaste_triggered()
{
    QFormDoc* formDoc = (QFormDoc*)ui->mdiArea->activeSubWindow()->widget();
    formDoc->textPaste();
}

void QWMainWindow::on_actSave_triggered()
{
    QFormDoc* formDoc = (QFormDoc*)ui->mdiArea->activeSubWindow()->widget();

    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getSaveFileName(this, "保存文件",
                        curPath, "C程序文件(*.h *.cpp);;所有文件(*.*)");
    if(aFileName.isEmpty())
        return;

    formDoc->fileSave(aFileName);
}
