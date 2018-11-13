#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QtGlobal>
#include "qwdialogsize.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    theModel = new QStandardItemModel(6, FixedColumnCount, this);
    theSelection = new QItemSelectionModel(theModel);
    connect(theSelection, SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(on_currentChanged(QModelIndex, QModelIndex)));
    ui->tableView->setModel(theModel);
    ui->tableView->setSelectionModel(theSelection);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);

    QStringList headerList;
    headerList << "1" << "2" << "3" << "4" << "5" << "6";
    theModel->setHorizontalHeaderLabels(headerList);

    LabCellPos = new QLabel("当前单元格");
    LabCellText = new QLabel("单元格内容");
    ui->statusBar->addWidget(LabCellPos, 1);
    ui->statusBar->addWidget(LabCellText, 1);
}

void MainWindow::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if(current.isValid())
    {
        LabCellPos->setText(QString::asprintf("当前单元格: %d行, %d列", current.row()+1, current.column()+1));
        QStandardItem* aItem = theModel->itemFromIndex(current);
        LabCellText->setText("单元格内容: "+aItem->text());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actSave_triggered()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getSaveFileName(this, "选择保存文件",
                curPath, "Qt预定义编码数据文件(*.stm)");
    if(aFileName.isEmpty())
        return;
    if(saveDataAsStream(aFileName))
        QMessageBox::information(this, "提示", "文件已成功保存！");
}

bool MainWindow::saveDataAsStream(QString &aFileName)
{
    QFile aFile(aFileName);
    if(!(aFile.open(QIODevice::WriteOnly | QIODevice::Truncate)))
        return false;
    QDataStream aStream(&aFile);
    aStream.setVersion(QDataStream::Qt_5_9);
    qint16 rowCount = theModel->rowCount();
    qint16 colCount = theModel->columnCount();
    aStream << rowCount;
    aStream << colCount;

    for(int i=0; i < theModel->columnCount(); i++)
    {
        QString str = theModel->horizontalHeaderItem(i)->text();
        aStream << str;
    }

    for(int i=0; i < theModel->rowCount(); i++)
    {
        QStandardItem* aItem;
        for(int j=0; j<theModel->columnCount(); j++)
        {
            aItem = theModel->item(i, j);
            QString str = aItem->data(Qt::DisplayRole).toString();
            aStream << str;
        }
    }
    aFile.close();
    return true;
}

void MainWindow::on_actOpen_triggered()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getOpenFileName(this, "打开一个文件",
            curPath, "Qt预定义编码数据文件(*.stm)");
    if(aFileName.isEmpty())
        return;
    if(openDataAsStream(aFileName))
        QMessageBox::information(this, "提示", "文件已成功打开！");
}


bool MainWindow::openDataAsStream(QString &aFileName)
{
    QFile aFile(aFileName);
    if(!(aFile.open(QIODevice::ReadOnly)))
        return false;
    QDataStream aStream(&aFile);
    aStream.setVersion(QDataStream::Qt_5_9);

    qint16 rowCount, colCount;
    aStream >> rowCount;
    aStream >> colCount;
    theModel->setRowCount(rowCount);
    theModel->setColumnCount(colCount);
    QStringList headerList;
    QString str;
    for(int i=0; i< colCount; i++)
    {
        aStream >> str;
        headerList << str;
    }
    theModel->setHorizontalHeaderLabels(headerList);

    QModelIndex index;
    QStandardItem* aItem;
    for(int i=0; i<rowCount; i++)
    {
        for(int j=0; j<colCount; j++)
        {
            index = theModel->index(i, j);
            aItem = theModel->itemFromIndex(index);
            aStream >> str;
            aItem->setData(str, Qt::DisplayRole);
        }
    }

    aFile.close();
    return true;
}

void MainWindow::on_actNew_triggered()
{
    on_actSetSize_triggered();
    on_actSetHeader_triggered();
}

void MainWindow::on_actSetSize_triggered()
{
    QWDialogSize* dlgTableSize = new QWDialogSize(this);
    Qt::WindowFlags flags = dlgTableSize->windowFlags();
    dlgTableSize->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    dlgTableSize->setRowCol(theModel->rowCount(), theModel->columnCount());
    int ret = dlgTableSize->exec();
    if(ret == QDialog::Accepted)
    {
        int row = dlgTableSize->rowCount();
        int col = dlgTableSize->colCount();
        theModel->setRowCount(row);
        theModel->setColumnCount(col);
    }
    delete dlgTableSize;
}

void MainWindow::on_actSetHeader_triggered()
{
    if(dlgSetHeader==NULL)
        dlgSetHeader = new QWDialogHeaders(this);
    if(dlgSetHeader->headerList().count()!=theModel->columnCount())
    {
        QStringList strList;
        for(int i=0; i<theModel->columnCount(); i++)
            strList.append(theModel->headerData(i, Qt::Horizontal,
                    Qt::DisplayRole).toString());
        dlgSetHeader->setHeaders(strList);
    }

    int ret = dlgSetHeader->exec();
    if(ret==QDialog::Accepted)
    {
        QStringList strList = dlgSetHeader->headerList();
        theModel->setHorizontalHeaderLabels(strList);
    }
}
