#include "widget.h"

#include "ui_widget.h"

void Widget::closeEvent(QCloseEvent *event) {
  if (threadProducer.isRunning()) {
    threadProducer.stopThread();
    threadProducer.wait();
  }
  if (threadConsumer.isRunning()) {
    threadConsumer.terminate();  //可能处于阻塞状态,调用stopThread无法关闭
    threadConsumer.wait();
  }
  event->accept();
}

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  connect(&threadProducer, SIGNAL(started()), this,
          SLOT(onthreadProducer_started()));
  connect(&threadProducer, SIGNAL(finished()), this,
          SLOT(onthreadProducer_finished()));

  connect(&threadConsumer, SIGNAL(started()), this,
          SLOT(onthreadConsumer_started()));
  connect(&threadConsumer, SIGNAL(finished()), this,
          SLOT(onthreadConsumer_finished()));

  connect(&threadConsumer, SIGNAL(newValue(int, int)), this,
          SLOT(onthreadConsumer_newValue(int, int)));
}

Widget::~Widget() { delete ui; }

void Widget::onthreadProducer_started() {
  ui->LabA->setText("Thread Producer状态: started");
}

void Widget::onthreadProducer_finished() {
  ui->LabA->setText("Thread Producer状态: finished");
}

void Widget::onthreadConsumer_started() {
  ui->LabB->setText("Thread Consumer状态: started");
}

void Widget::onthreadConsumer_finished() {
  ui->LabB->setText("Thread Consumer状态: finished");
}

void Widget::onthreadConsumer_newValue(int seq, int diceValue) {
  QString str = QString::asprintf("第 %d 次掷色子, 点数为 %d", seq, diceValue);
  ui->plainTextEdit->appendPlainText(str);
  QPixmap pic;
  QString filename = QString::asprintf(":/images/images/d%d.jpg", diceValue);
  pic.load(filename);
  ui->labPic->setPixmap(pic);
}

void Widget::on_btnStartThread_clicked() {
  threadProducer.start();
  threadConsumer.start();
  ui->btnStartThread->setEnabled(false);
  ui->btnStopThread->setEnabled(true);
}

void Widget::on_btnStopThread_clicked() {
  threadProducer.stopThread();
  threadProducer.wait();
  threadConsumer.terminate();
  threadConsumer.wait();
  ui->btnStartThread->setEnabled(true);
  ui->btnStopThread->setEnabled(false);
}

void Widget::on_btnClear_clicked() { ui->plainTextEdit->clear(); }
