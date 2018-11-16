#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QRect>
#include <QPen>
#include <QBrush>
#include <QTime>

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    int W = this->width();
    int H = this->height();

    QRadialGradient radiaGrad(W/2, H/2, qMax(W/8, H/8), W/2, H/2);
    radiaGrad.setColorAt(1, Qt::white);
    radiaGrad.setColorAt(0, Qt::black);
    radiaGrad.setSpread(QGradient::RepeatSpread);
    painter.setBrush(radiaGrad);

    painter.drawRect(this->rect());
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowFullScreen);
    setPalette(QPalette(Qt::white));    //设置调色板颜色
    setAutoFillBackground(true);        //是否自动填充
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintWhiteBlack()
{
    QPainter painter(this);
    int W = this->width();
    int H = this->height();

    QRadialGradient radiaGrad(W/2, H/2, qMax(W/8, H/8), W/2, H/2);
    radiaGrad.setColorAt(0, Qt::white);
    radiaGrad.setColorAt(1, Qt::black);
    radiaGrad.setSpread(QGradient::RepeatSpread);
    painter.setBrush(radiaGrad);

    painter.drawRect(this->rect());
}

void Widget::paintBlackWhite()
{
    QPainter painter(this);
    int W = this->width();
    int H = this->height();

    QRadialGradient radiaGrad(W/2, H/2, qMax(W/8, H/8), W/2, H/2);
    radiaGrad.setColorAt(1, Qt::white);
    radiaGrad.setColorAt(0, Qt::black);
    radiaGrad.setSpread(QGradient::RepeatSpread);
    painter.setBrush(radiaGrad);

    painter.drawRect(this->rect());
}

void Widget::on_pushButton_2_clicked()
{
    paintBlackWhite();
}

void Widget::on_pushButton_3_clicked()
{
    paintWhiteBlack();
}
