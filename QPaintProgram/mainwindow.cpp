#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QGraphicsItemGroup>
#include <QPen>
#include <QColor>
#include <QColorDialog>
#include <QFontDialog>
#include <QInputDialog>

template<class T> void setBrushColor(T* item);

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

void MainWindow::on_mouseMovePoint(QPoint point)
{
    labViewCord->setText(QString::asprintf("View坐标: %d, %d", point.x(), point.y()));
    QPointF pointScene = ui->View->mapToScene(point);
    labSceneCord->setText(QString::asprintf("Scene坐标: %.0f, %.0f", pointScene.x(), pointScene.y()));
}

void MainWindow::on_mouseClicked(QPoint point)
{
    QPointF pointScene = ui->View->mapToScene(point);
    QGraphicsItem* item = NULL;
    item = scene->itemAt(pointScene, ui->View->transform());
    if(item != NULL)
    {
        QPointF pointItem = item->mapFromScene(pointScene);
        labItemCord->setText(QString::asprintf("Item坐标: %.0f, %.0f", pointItem.x(), pointItem.y()));
        labItemInfo->setText(item->data(ItemDesciption).toString()+"\tItemId="+item->data(ItemId).toString());
    }
}

void MainWindow::on_mouseDoubleClicked(QPoint point)
{
    QPointF pointScene = ui->View->mapToScene(point);
    QGraphicsItem* item = NULL;
    item = scene->itemAt(pointScene, ui->View->transform());
    if(item == NULL)
        return;

    switch (item->type())
    {
        case QGraphicsRectItem::Type:
        {
            QGraphicsRectItem* theItem;
            theItem = qgraphicsitem_cast<QGraphicsRectItem*>(item);
            setBrushColor(theItem);
            break;
        }
        case QGraphicsEllipseItem::Type:
        {
            QGraphicsEllipseItem* theItem;
            theItem = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
            setBrushColor(theItem);
            break;
        }
        case QGraphicsPolygonItem::Type:
        {
            QGraphicsPolygonItem* theItem;
            theItem = qgraphicsitem_cast<QGraphicsPolygonItem*>(item);
            setBrushColor(theItem);
            break;
        }
        case QGraphicsLineItem::Type:
        {
            QGraphicsLineItem* theItem;
            theItem = qgraphicsitem_cast<QGraphicsLineItem*>(item);
            QPen pen = theItem->pen();
            QColor color = theItem->pen().color();
            color = QColorDialog::getColor(color, this, "选择线条颜色");
            if(color.isValid())
            {
                pen.setColor(color);
                theItem->setPen(pen);
            }
            break;
        }
        case QGraphicsTextItem::Type:
        {
            QGraphicsTextItem* theItem;
            theItem = qgraphicsitem_cast<QGraphicsTextItem*>(item);
            QFont font = theItem->font();
            bool ok = false;
            font = QFontDialog::getFont(&ok, font, this, "设置字体");
            if(ok)
                theItem->setFont(font);
            break;
        }
    }

}

void MainWindow::on_keyPress(QKeyEvent *event)
{
    if(scene->selectedItems().count() != 1)
        return;
    QGraphicsItem* item = scene->selectedItems().at(0);
    if(event->key() == Qt::Key_Delete)
        scene->removeItem(item);
    else if(event->key() == Qt::Key_Space)
        item->setRotation(90 + item->rotation());
    else if(event->key() == Qt::Key_PageUp)
        item->setScale(0.1111 + item->scale());
    else if(event->key() == Qt::Key_PageDown)
        item->setScale(-0.1 + item->scale());
    else if(event->key() == Qt::Key_Left)
        item->setX(-1 + item->x());
    else if(event->key() == Qt::Key_Right)
        item->setX(1 + item->x());
    else if(event->key() == Qt::Key_Up)
        item->setY(-1 + item->y());
    else if(event->key() == Qt::Key_Down)
        item->setY(1 + item->y());
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
    int cnt=scene->selectedItems().count();
    if (cnt==1)
    {
        QGraphicsItem* item=scene->selectedItems().at(0);
        item->resetTransform();
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

void MainWindow::on_actGroup_triggered()
{
    int cnt = scene->selectedItems().count();
    if(cnt>1)
    {
        QGraphicsItemGroup* group = new QGraphicsItemGroup;
        scene->addItem(group);
        for(int i=0; i<cnt; i++)
        {
            QGraphicsItem* item = scene->selectedItems().at(0);
            item->setSelected(false);
            item->clearFocus();
            group->addToGroup(item);
        }
        group->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        scene->clearSelection();
        group->setSelected(true);
    }
}

void MainWindow::on_actGroupBreak_triggered()
{
    int cnt = scene->selectedItems().count();
    if(cnt==1)
    {
        QGraphicsItemGroup* group;
        group = (QGraphicsItemGroup*)scene->selectedItems().at(0);
        scene->destroyItemGroup(group);
    }
}

void MainWindow::on_actEdit_Delete_triggered()
{
    int cnt = scene->selectedItems().count();
    if(cnt>0)
        for(int i=0; i<cnt; i++)
        {
            QGraphicsItem* item = scene->selectedItems().at(0);
            scene->removeItem(item);
        }
}

template<class T> void setBrushColor(T* item)
{
    QColor color = item->brush().color();
    color = QColorDialog::getColor(color, NULL, "选择填充颜色");
    if(color.isValid())
        item->setBrush(QBrush(color));
}



void MainWindow::on_actItem_Triangle_triggered()
{
    QGraphicsPolygonItem* item = new QGraphicsPolygonItem;
    QPolygonF points;
    points.append(QPointF(0,-40));
    points.append(QPointF(-60,40));
    points.append(QPointF(60,40));
    item->setPolygon(points);
    item->setPos(-50+(qrand() % 100),-50+(qrand() % 100));

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

void MainWindow::on_actItem_Polygon_triggered()
{
    QGraphicsPolygonItem   *item=new QGraphicsPolygonItem;

    QPolygonF   points;
    points.append(QPointF(-40,-40));
    points.append(QPointF(40,-40));
    points.append(QPointF(100,40));
    points.append(QPointF(-100,40));
    item->setPolygon(points);
    item->setPos(-50+(qrand() % 100),-50+(qrand() % 100));

    item->setFlags(QGraphicsItem::ItemIsMovable
                   | QGraphicsItem::ItemIsSelectable
                   | QGraphicsItem::ItemIsFocusable);
    item->setBrush(QBrush(Qt::green));
    item->setZValue(++frontZ);

    item->setData(ItemId,++seqNum);
    item->setData(ItemDesciption,"梯形");

    scene->addItem(item);
    scene->clearSelection();
    item->setSelected(true);
}

void MainWindow::on_actItem_Text_triggered()
{
    QString str=QInputDialog::getText(this,"输入文字","请输入文字");
    if (str.isEmpty())
        return;

    QGraphicsTextItem* item=new QGraphicsTextItem(str);

    QFont   font=this->font();
    font.setPointSize(20);
    font.setBold(true);
    item->setFont(font);

    item->setFlags(QGraphicsItem::ItemIsMovable
                   | QGraphicsItem::ItemIsSelectable
                   | QGraphicsItem::ItemIsFocusable);
    item->setPos(-50+(qrand() % 100),-50+(qrand() % 100));
    item->setZValue(++frontZ);

    item->setData(ItemId,++seqNum);
    item->setData(ItemDesciption,"文字");

    scene->addItem(item);
    scene->clearSelection();
    item->setSelected(true);
}
