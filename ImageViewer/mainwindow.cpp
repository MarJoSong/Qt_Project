#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTreeWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LabFileName = new QLabel("");
    ui->statusBar->addWidget(LabFileName);
    this->setCentralWidget(ui->scrollArea);
    iniTree();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iniTree()
{
    QString dataStr = "";
    ui->treeFiles->clear();
    QIcon icon;
    icon.addFile(":/images/icons/15.ico");

    QTreeWidgetItem * item = new QTreeWidgetItem(MainWindow::itTopItem);//使用枚举参数1001
    item->setIcon(MainWindow::colItem, icon);
    item->setText(MainWindow::colItem, "图片文件");
    item->setText(MainWindow::colItemType, "type=itTopItem");
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    item->setCheckState(colItem, Qt::Checked);

    item->setData(MainWindow::colItem, Qt::UserRole, QVariant(dataStr));
    ui->treeFiles->addTopLevelItem(item);
}



void MainWindow::on_actAddFolder_triggered()
{
//    QString dir = QFileDialog::getExistingDirectory();
//    if(!dir.isEmpty())
    {
        QTreeWidgetItem * parItem = ui->treeFiles->currentItem();
        //addFolderItem(parItem, dir);
        QTreeWidgetItem * item = new QTreeWidgetItem(MainWindow::itGroupItem);
        item->setText(colItem, "NodeText");
        item->setText(colItemType, "type=itGroupItem");
        parItem->addChild(item);
    }
}

void MainWindow::addFolderItem(QTreeWidgetItem * parItem, QString dirName)
{
    //QIcon icon(":/images/icons/open3.bmp");
    QString NodeText = getFinalFolderName(dirName);

    QTreeWidgetItem * item = new QTreeWidgetItem(MainWindow::itGroupItem);
    //item->setIcon(colItem, icon);
    item->setText(colItem, NodeText);
    item->setText(colItemType, "type=itGroupItem");
    //item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    //item->setCheckState(colItem, Qt::Checked);
    //item->setData(colItem, Qt::UserRole, QVariant(dirName));
    parItem->addChild(item);
}

QString MainWindow::getFinalFolderName(const QString &fullPathName)
{
    int cnt = fullPathName.length();
    int i = fullPathName.lastIndexOf("/");
    QString str = fullPathName.right(cnt-i-1);
    ui->label->setText(str);
    return str;
}

void MainWindow::addImageItem(QTreeWidgetItem *parItem, QString aFileName)
{
    QIcon icon(":/images/icons/31.ico");
    QString NodeText = getFinalFolderName(aFileName);

    QTreeWidgetItem * item = new QTreeWidgetItem(MainWindow::itImageItem);
    item->setIcon(colItem, icon);
    item->setText(colItem, NodeText);
    item->setText(colItemType, "type=itGroupItem");
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsAutoTristate);
    item->setCheckState(colItem, Qt::Checked);
    item->setData(colItem, Qt::UserRole, QVariant(aFileName));
    parItem->addChild(item);
}



void MainWindow::on_actAddFiles_triggered()
{
    QStringList files = QFileDialog::getOpenFileNames(this,
        "选择一个或多个文件", "", "Images(*.jpg)");
    if(files.isEmpty())
        return;
    QTreeWidgetItem * parItem, * item;
    item = ui->treeFiles->currentItem();
    if(item->type() == itImageItem)
        parItem = item->parent();
    else
        parItem = item;

    for(int i = 0; i < files.size(); i++)
    {
        QString aFilename = files.at(i);
        addImageItem(parItem, aFilename);
    }
}















