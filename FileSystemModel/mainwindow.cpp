#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QFileSystemModel(this);//添加头文件 <QFileSystemModel>
    model->setRootPath(QDir::currentPath());//设置根目录

    ui->treeView->setModel(model);//设置数据模型
    ui->tableView->setModel(model);
    ui->listView->setModel(model);

    connect(ui->treeView, SIGNAL(clicked(QModelIndex)),
            ui->listView, SLOT(setRootIndex(QModelIndex)));
            //treeView单击时获取当前节点的模型索引（目录），作为根目录传递给listView
    connect(ui->treeView, SIGNAL(clicked(QModelIndex)),
            ui->tableView, SLOT(setRootIndex(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    ui->ckbIsDir->setChecked(model->isDir(index));
    ui->labPath->setText(model->filePath(index));
    ui->labFileType->setText(model->type(index));
    ui->labFileName->setText(model->fileName(index));
    int sz = model->size(index)/1024;
    if(sz < 1024)
        ui->labFileSize->setText(QString("%1 KB").arg(sz));
    else
        ui->labFileSize->setText(QString::asprintf("%.1f MB", sz/1024.0));
}
