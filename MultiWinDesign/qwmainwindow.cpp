#include "qformdoc.h"
#include "qformtable.h"
#include "qwmainwindow.h"
#include "ui_qwmainwindow.h"

#include <QPainter>

QWMainWindow::QWMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QWMainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setVisible(false);
    ui->tabWidget->clear();
    ui->tabWidget->setTabsClosable(true);
    this->setCentralWidget(ui->tabWidget);
    this->setWindowState(Qt::WindowFullScreen);
}

QWMainWindow::~QWMainWindow()
{
    delete ui;
}

void QWMainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(0,ui->mainToolBar->height(),this->width(),
                       this->height()-ui->mainToolBar->height(),
                       QPixmap(":/images/images/back2.jpg"));
}

void QWMainWindow::on_actWidgetInsite_triggered()
{
    QFormDoc *formDoc = new QFormDoc(this);
    formDoc->setAttribute(Qt::WA_DeleteOnClose);
    int cur = ui->tabWidget->addTab(formDoc,
            QString::asprintf("Doc %d", ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}

void QWMainWindow::on_actWidget_triggered()
{
    QFormDoc *formDoc = new QFormDoc();
    formDoc->setAttribute(Qt::WA_DeleteOnClose);
    formDoc->setWindowFlag(Qt::Window, true);
    formDoc->setWindowTitle("独立窗体，无父窗口，关闭时删除");
    //formDoc->setWindowOpacity(0.8);
    formDoc->show();
}

void QWMainWindow::on_actWindowInsite_triggered()
{
    QFormTable* formTable = new QFormTable(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose);
    int cur = ui->tabWidget->addTab(formTable,
            QString::asprintf("表格 %d", ui->tabWidget->count()+1));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}

void QWMainWindow::on_actWindow_triggered()
{
    QFormTable* formTable = new QFormTable(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose);
    formTable->setWindowTitle("基于MainWindow的窗体, 无父窗口, 关闭时删除");
    formTable->setWindowFlag(Qt::Window, true);
    formTable->show();
}

void QWMainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if(index < 0)
        return;
    QWidget* aForm = ui->tabWidget->widget(index);
    aForm->close();
}

void QWMainWindow::on_tabWidget_currentChanged(int index)
{
    bool en = ui->tabWidget->count()>0;
    ui->tabWidget->setVisible(en);
}
