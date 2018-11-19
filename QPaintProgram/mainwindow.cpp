#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    labViewCord = new QLabel("View坐标: ");
    labSceneCord = new QLabel("Scene坐标: ");
    labItemCord = new QLabel("Item坐标: ");
    labItemInfo = new QLabel("Item信息: ");
    ui->statusBar->addWidget(labViewCord, 1);
    ui->statusBar->addWidget(labSceneCord, 1);
    ui->statusBar->addWidget(labItemCord, 1);
    ui->statusBar->addWidget(labItemInfo, 1);

    scene = new QGraphicsScene(-300, -200, 600, 400);
    ui->View->setScene(scene);
    ui->View->setCursor(Qt::CrossCursor);
    ui->View->setMouseTracking(true);
    ui->View->setDragMode(QGraphicsView::RubberBandDrag);
    this->setCentralWidget(ui->View);

    QObject::connect(ui->View, SIGNAL(mouseMovePoint(QPoint)),
                     this, SLOT(on_mouseMovePoint(QPoint)));
    QObject::connect(ui->View, SIGNAL(mouseClicked(QPoint)),
                     this, SLOT(on_mouseClicked(QPoint)));
    QObject::connect(ui->View, SIGNAL(mouseDoubleClicked(QPoint)),
                     this, SLOT(on_mouseDoubleClicked(QPoint)));
    QObject::connect(ui->View, SIGNAL(keyPress(QKeyEvent*)),
                     this, SLOT(on_keyPress(QKeyEvent*)));
    qsrand(QTime::currentTime().second());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actItem_Ellipse_triggered()
{
    QGraphicsEllipseItem* item = new QGraphicsEllipseItem(-50, -30, 100, 60);
    item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    item->setBrush(QBrush(Qt::blue));
    item->setZValue(++frontZ);
    item->setPos(-50+(qrand()%100), -50+(qrand()%100));
    item->setData(ItemId, ++seqNum);
    item->setData(ItemDesciption, "椭圆");

    scene->addItem(item);
    scene->clearSelection();
    item->setSelected(true);
}

void MainWindow::on_actItem_Rect_triggered()
{
     QGraphicsRectItem* item = new QGraphicsRectItem(-40,-40 ,80, 80);
     item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
     item->setBrush(QBrush(Qt::yellow));
     item->setZValue(++frontZ);
     item->setPos(-50+(qrand()%100), -50+(qrand()%100));
     item->setData(ItemId, ++seqNum);
     item->setData(ItemDesciption, "矩形");

     scene->addItem(item);
     scene->clearSelection();
     item->setSelected(true);
}

void MainWindow::on_actItem_Circle_triggered()
{
    QGraphicsEllipseItem* item = new QGraphicsEllipseItem(-30, -30, 60, 60);
    item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    item->setBrush(QBrush(Qt::green));
    item->setZValue(++frontZ);
    item->setPos(-50+(qrand()%100), -50+(qrand()%100));
    item->setData(ItemId, ++seqNum);
    item->setData(ItemDesciption, "椭圆");

    scene->addItem(item);
    scene->clearSelection();
    item->setSelected(true);
}

void MainWindow::on_actItem_Line_triggered()
{
    QGraphicsLineItem* item = new QGraphicsLineItem(-40, -0, 40, 0);
    item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    item->setZValue(++frontZ);
    item->setPos(-50+(qrand()%100), -50+(qrand()%100));
    item->setData(ItemId, ++seqNum);
    item->setData(ItemDesciption, "椭圆");

    scene->addItem(item);
    scene->clearSelection();
    item->setSelected(true);
}

void MainWindow::on_actZoomIn_triggered()
{
    int cnt = scene->selectedItems().count();
    if(cnt!=0)
    {
        for(int i=0; i<cnt; i++)
        {
            QGraphicsItem* item = scene->selectedItems().at(i);
            item->setScale(item->scale()*1.1111);
        }
    }
    else
        ui->View->scale(1.1111, 1.1111);
}

void MainWindow::on_actZoomOut_triggered()
{
    int cnt = scene->selectedItems().count();
    if(cnt!=0)
    {
        for(int i=0; i<cnt; i++)
        {
            QGraphicsItem* item = scene->selectedItems().at(i);
            item->setScale(item->scale()*0.9);
        }
    }
    else
        ui->View->scale(0.9, 0.9);
}

void MainWindow::on_actRotateLeft_triggered()
{
    int cnt = scene->selectedItems().count();
    if(cnt!=0)
    {
        for(int i=0; i<cnt; i++)
        {
            QGraphicsItem* item = scene->selectedItems().at(i);
            item->setRotation(-30+item->rotation());
        }
    }
    else
        ui->View->rotate(-30);
}

void MainWindow::on_actRotateRight_triggered()
{
    int cnt = scene->selectedItems().count();
    if(cnt!=0)
    {
        for(int i=0; i<cnt; i++)
        {
            QGraphicsItem* item = scene->selectedItems().at(i);
            item->setRotation(30+item->rotation());
        }
    }
    else
        ui->View->rotate(30);
}

void MainWindow::on_actRestore_triggered()
{
    int cnt = scene->selectedItems().count();
    if(cnt!=0)
    {
        for(int i=0; i<cnt; i++)
        {
            QGraphicsItem* item = scene->selectedItems().at(i);
            item->resetTransform();
        }
    }
    else
        ui->View->resetTransform();
}

void MainWindow::on_actEdit_Front_triggered()
{
    int cnt = scene->selectedItems().count();
    if(cnt>0)
    {
        QGraphicsItem* item = scene->selectedItems().at(0);
        item->setZValue(++frontZ);
    }
}

void MainWindow::on_actEdit_Back_triggered()
{
    int cnt = scene->selectedItems().count();
    if(cnt>0)
    {
        QGraphicsItem* item = scene->selectedItems().at(0);
        item->setZValue(--backZ);
    }
}
