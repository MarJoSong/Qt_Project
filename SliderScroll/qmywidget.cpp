#include "qmywidget.h"
#include "ui_qmywidget.h"

QmyWidget::QmyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QmyWidget)
{
    ui->setupUi(this);
    QObject::connect(ui->greenSlider, SIGNAL(valueChanged(int)),
                     this, SLOT(on_redSlider_valueChanged(int)));
    QObject::connect(ui->blueSlider, SIGNAL(valueChanged(int)),
                     this, SLOT(on_redSlider_valueChanged(int)));
    QObject::connect(ui->alphaSlider, SIGNAL(valueChanged(int)),
                     this, SLOT(on_redSlider_valueChanged(int)));
}

QmyWidget::~QmyWidget()
{
    delete ui;
}

void QmyWidget::on_redSlider_valueChanged(int value)
{
    Q_UNUSED(value);
    QColor color;
    int R = ui->redSlider->value();
    int G = ui->greenSlider->value();
    int B = ui->blueSlider->value();
    int alpha = ui->alphaSlider->value();
    color.setRgb(R, G, B, alpha);
    QPalette pal = ui->textEdit->palette();
    pal.setColor(QPalette::Base, color);
    ui->textEdit->setPalette(pal);
}

void QmyWidget::on_dial_valueChanged(int value)
{
    ui->lcdNumber->display(value);
}

void QmyWidget::on_radioDec_clicked()
{
    ui->lcdNumber->setDigitCount(3);
    ui->lcdNumber->setDecMode();
}

void QmyWidget::on_radioBin_clicked()
{
    ui->lcdNumber->setDigitCount(8);
    ui->lcdNumber->setBinMode();
}

void QmyWidget::on_radioOct_clicked()
{
    ui->lcdNumber->setDigitCount(4);
    ui->lcdNumber->setOctMode();
}

void QmyWidget::on_radioHex_clicked()
{
    ui->lcdNumber->setDigitCount(3);
    ui->lcdNumber->setHexMode();
}
