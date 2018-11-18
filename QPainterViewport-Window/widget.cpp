#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QRect>
#include <QPen>
#include <QBrush>

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    int W = this->width();
    int H = this->height();

    int side = qMin(W, H);
    QRect rect((W-side)/2, (H-side)/2, side, side);
    //painter.drawRect(rect);
    painter.setViewport(rect);
    painter.setWindow(-100, -100, 200, 200);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::red);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);

    for(int i=0; i<60; i++)
    {
        painter.drawEllipse(QPoint(50, 0), 50, 50);
        painter.rotate(6);
    }
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowNoState);
    setPalette(QPalette(Qt::white));    //设置调色板颜色
    setAutoFillBackground(true);        //是否自动填充
}

Widget::~Widget()
{
    delete ui;
}
