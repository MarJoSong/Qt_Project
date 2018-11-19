#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsItem>

void MainWindow::iniGraphicsSystem()
{
    QRectF rect(-200, -100, 400, 200);
    scene = new QGraphicsScene(rect);
    ui->View->setScene(scene);

    QGraphicsRectItem *item = new QGraphicsRectItem(rect);
    item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);

    QPen pen;
    pen.setWidth(2);
    item->setPen(pen);
    scene->addItem(item);

    QGraphicsEllipseItem *item2 = new QGraphicsEllipseItem(-100, -50, 200, 100);
    item2->setPos(0 ,0);
    item2->setBrush(QBrush(Qt::blue));
    item2->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    scene->addItem(item2);

    QGraphicsEllipseItem *item3 = new QGraphicsEllipseItem(-50, -50, 100, 100);
    item3->setPos(rect.right(), rect.bottom());
    item3->setBrush(QBrush(Qt::red));
    item3->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    scene->addItem(item3);
    scene->clearSelection();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->labViewSize->setText(QString::asprintf("Graphics View坐标, 左上方总是(0, 0), 宽度=%d, 高度=%d",ui->View->width(), ui->View->height()));
    QRectF rectF = ui->View->sceneRect();
    ui->labSceneRect->setText(QString::asprintf("QGraphicsView::sceneRect=(Lefi, Top, Width, Height)=%.0f, %.0f, %.0f, %.0f", rectF.left(),rectF.top(), rectF.width(), rectF.height()));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    labViewPos = new QLabel("View坐标: ", this);
    labScenePos = new QLabel("Scene坐标: ");
    labItemPos = new QLabel("Item坐标: ");
    labNone = new QLabel("");
    ui->statusBar->addWidget(labViewPos, 1);
    ui->statusBar->addWidget(labScenePos, 1);
    ui->statusBar->addWidget(labItemPos, 1);
    ui->statusBar->addWidget(labNone, 1);

    ui->View->setCursor(Qt::CrossCursor);
    ui->View->setMouseTracking(true);
    ui->View->setDragMode(QGraphicsView::RubberBandDrag);
    QObject::connect(ui->View, SIGNAL(mouseMovePoint(QPoint)),
            this, SLOT(on_mouseMovePoint(QPoint)));
    QObject::connect(ui->View, SIGNAL(mouseClicked(QPoint)),
            this, SLOT(on_mouseClicked(QPoint)));
    iniGraphicsSystem();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_mouseMovePoint(QPoint point)
{
    labViewPos->setText(QString::asprintf("View坐标: %d, %d", point.x(), point.y()));
    QPointF pointScene = ui->View->mapToScene(point);
    labScenePos->setText(QString::asprintf("Scene坐标: %.0f, %.0f", pointScene.x(), pointScene.y()));
}

void MainWindow::on_mouseClicked(QPoint point)
{
    QPointF pointScene = ui->View->mapToScene(point);
    QGraphicsItem *item = NULL;
    item = scene->itemAt(pointScene, ui->View->transform());
    if(item != NULL)
    {
        QPointF pointItem = item->mapFromScene(pointScene);
        labItemPos->setText(QString::asprintf("Item坐标: %.0f, %.0f", pointItem.x(), pointItem.y()));
    }
}
