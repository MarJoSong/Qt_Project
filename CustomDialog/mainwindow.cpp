#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qwdialogsize.h"
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    theModel = new QStandardItemModel(this);
    ui->tableView->setModel(theModel);

    theSelection = new QItemSelectionModel(theModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setACellText(int row, int column, QString text)
{
    QModelIndex index = theModel->index(row, column);
    theSelection->clearSelection();
    theSelection->setCurrentIndex(index, QItemSelectionModel::Select);
    theModel->setData(index, text, Qt::DisplayRole);
}

void MainWindow::setActLocateEnable(bool enable)
{
    ui->actLocate->setEnabled(enable);
}

void MainWindow::setDlgLocateNull()
{
    dlgLocate = NULL;
}

void MainWindow::on_actSetSize_triggered()
{
    QWDialogSize *dlgTableSize = new QWDialogSize(this);
    Qt::WindowFlags flags = dlgTableSize->windowFlags();
    dlgTableSize->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    dlgTableSize->setRowColumn(theModel->rowCount(), theModel->columnCount());
    int ret = dlgTableSize->exec();
    if(ret == QDialog::Accepted)
    {
        int cols = dlgTableSize->columnCount();
        theModel->setColumnCount(cols);
        int row = dlgTableSize->rowCount();
        theModel->setRowCount(row);
    }
    delete dlgTableSize;
}

void MainWindow::on_actSetHeader_triggered()
{
    if(dlgSetHeaders == NULL)
        dlgSetHeaders = new QWDialogHeaders(this);
    if(dlgSetHeaders->headerList().count() != theModel->columnCount())
    {
        QStringList strList;
        for(int i=0; i<theModel->columnCount(); i++)
            strList.append(theModel->headerData(i, Qt::Horizontal,
                Qt::DisplayRole).toString());
        dlgSetHeaders->setHeaderList(strList);
    }

    int ret = dlgSetHeaders->exec();
    if(ret == QDialog::Accepted)
    {
        QStringList strList = dlgSetHeaders->headerList();
        theModel->setHorizontalHeaderLabels(strList);
    }
}

void MainWindow::on_actLocate_triggered()
{
    ui->actLocate->setEnabled(false);
    dlgLocate = new QWDialogLocate(this);
    dlgLocate->setAttribute(Qt::WA_DeleteOnClose);
    Qt::WindowFlags flags = dlgLocate->windowFlags();
    dlgLocate->setWindowFlags(flags | Qt::WindowStaysOnTopHint);

    //dlgLocate->setSpinRange(theModel->rowCount(), theModel->columnCount());
    QModelIndex curIndex = theSelection->currentIndex();

    if(curIndex.isValid())
        dlgLocate->setSpinValue(curIndex.row(), curIndex.column());
    dlgLocate->show();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    if(dlgLocate!=NULL)
        dlgLocate->setSpinValue(index.row(), index.column());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton result = QMessageBox::question(this,
        "确认", "确认要退出本程序吗? ", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
        QMessageBox::No);
    if(result == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}
