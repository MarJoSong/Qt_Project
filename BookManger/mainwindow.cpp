#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList bookList;
    bookList << "C++ Prime Plus" << "Qt5.9 C++ 开发指南";
    bookModel = new QStringListModel(this);
    bookModel->setStringList(bookList);
    ui->listView->setModel(bookModel);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actImportLibrary_triggered()
{
    QString curPath = QCoreApplication::applicationDirPath();
    aFileName = QFileDialog::getOpenFileName(this, "选择一个文件", curPath,
                                             "书库文件(*.book)");
    if(aFileName.isEmpty())
        return;

    QStringList readBookLib;
    QFile aFile(aFileName);

    if(aFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream aStream(&aFile);
        bookModel->removeRows(0,bookModel->rowCount());

        while(!aStream.atEnd())
        {
            QString str = aStream.readLine();
            readBookLib.append(str);
        }
        aFile.close();
        bookModel->setStringList(readBookLib);
        //ui->listView->setModel(bookModel);
        ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}

void MainWindow::on_actAddBook_triggered()
{
    bookModel->insertRow(bookModel->rowCount());
    QModelIndex index = bookModel->index(bookModel->rowCount()-1, 0);
    bookModel->setData(index, "新书籍Got！", Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked);
}

void MainWindow::on_actEditUnable_triggered()
{
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_actSave_triggered()
{
    QFile aFile(aFileName);
    if(!(aFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)))
        return;
    QTextStream aStream(&aFile);
    QString str = "";
    QStringList tmpList = bookModel->stringList();
    for(int i=0; i<tmpList.count(); i++)
    {
        str.append(tmpList.at(i));
        str = str + "\n";
    }
    aStream << str;
}
