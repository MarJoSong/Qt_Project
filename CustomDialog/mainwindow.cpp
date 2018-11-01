#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qwdialogsize.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    theModel = new QStandardItemModel(this);
    ui->tableView->setModel(theModel);
}

MainWindow::~MainWindow()
{
    delete ui;
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
