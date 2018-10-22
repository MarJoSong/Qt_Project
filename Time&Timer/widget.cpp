#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    fTimer = new QTimer(this);
    fTimer->stop();
    fTimer->setInterval(1000);
    connect(fTimer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnGetTime_clicked()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    ui->timeEdit->setTime(currentDateTime.time());
    ui->editTime->setText(currentDateTime.toString("hh:mm:ss"));
    ui->dateEdit->setDate(currentDateTime.date());
    ui->editDate->setText(currentDateTime.toString("yyyy-MM-dd"));
    ui->dateTimeEdit->setDateTime(currentDateTime);
    ui->editTimedate->setText(currentDateTime.toString("yyyy-MM-dd hh:mm:ss"));
}

void Widget::on_pushButton_4_clicked()
{
    QString str = ui->editTimedate->text();
    str.trimmed();
    if(!str.isEmpty())
    {
        QDateTime datetime = QDateTime::fromString(str, "yyyy-MM-dd hh:mm:ss");
        ui->dateTimeEdit->setDateTime(datetime);
    }
}

void Widget::on_calendarWidget_selectionChanged()
{
    QDate dt = ui->calendarWidget->selectedDate();
    QString str = dt.toString("yyyy年M月d日");
    ui->calenderEdit->setText(str);
}

void Widget::on_timer_timeout()
{
    QTime cutTime = QTime::currentTime();
    ui->lcdNumber->display(cutTime.hour());
    ui->lcdNumber_2->display(cutTime.minute());
    ui->lcdNumber_3->display(cutTime.second());
    int va = ui->progressBar->value();
    if(++va >= 100)
        va = 0;
    ui->progressBar->setValue(va);
}

void Widget::on_btnStart_clicked()
{
    fTimer->start();
    fTimeCounter.start();
    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
    ui->btnSetIntv->setEnabled(false);
}

void Widget::on_btnStop_clicked()
{
    fTimer->stop();
    int tmMsec = fTimeCounter.elapsed();
    int ms = tmMsec % 1000;
    int sec = tmMsec /1000;
    QString str = QString::asprintf("流逝时间: %d 秒, %d 毫秒", sec, ms);
    ui->elapseTime->setText(str);
    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);
    ui->btnSetIntv->setEnabled(true);
}

void Widget::on_btnSetIntv_clicked()
{
    fTimer->setInterval(ui->intVedit->value());
    ui->btnSetIntv->setEnabled(false);
}

void Widget::on_intVedit_valueChanged(const QString &arg1)
{
    ui->btnSetIntv->setEnabled(true);
}
