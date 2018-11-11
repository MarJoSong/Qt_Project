#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QtGlobal>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
        QStandardItem* aItem = theModel->item(i, 0);
        qint16 ceShen = aItem->data(Qt::DisplayRole).toInt();
        aStream << ceShen;

        aItem = theModel->item(i, 1);
        qreal chuiShen = aItem->data(Qt::DisplayRole).toFloat();
        aStream << chuiShen;

        aItem = theModel->item(i, 2);
        qreal fangWei = aItem->data(Qt::DisplayRole).toFloat();
        aStream << fangWei;

        aItem = theModel->item(i, 3);
        qreal weiYi = aItem->data(Qt::DisplayRole).toFloat();
        aStream << weiYi;

        aItem = theModel->item(i, 4);
        QString zhiLiang = aItem->data(Qt::DisplayRole).toString();
        aStream << zhiLiang;
        aItem = theModel->item(i, 5);
        bool quYang = (aItem->checkState()==Qt::Checked);
        aStream << quYang;
    }
    aFile.close();
    return true;
}
