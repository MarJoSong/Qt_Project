﻿#include "widget.h"

#include "ui_widget.h"

void Widget::closeEvent(QCloseEvent *event) {
  if (threadA.isRunning()) {
    threadA.stopThread();
    threadA.wait();
  }
  event->accept();
}

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  connect(&threadA, SIGNAL(started()), this, SLOT(onthreadA_started()));
  connect(&threadA, SIGNAL(finished()), this, SLOT(onthreadA_finished()));
  connect(&threadA, SIGNAL(newValue(int, int)), this,
          SLOT(onthreadA_newValue(int, int)));
}

Widget::~Widget() { delete ui; }

void Widget::onthreadA_started() {
  ui->LabA->setText("Thread状态: thread started");
}

void Widget::onthreadA_finished() {
  ui->LabA->setText("Thread状态: thread finished");
}

void Widget::onthreadA_newValue(int seq, int diceValue) {
  QString str = QString::asprintf("第 %d 次掷色子, 点数为 %d", seq, diceValue);
  ui->plainTextEdit->appendPlainText(str);
  QPixmap pic;
  QString filename = QString::asprintf(":/images/images/d%d.jpg", diceValue);
  pic.load(filename);
  ui->labPic->setPixmap(pic);
}

void Widget::on_btnStartThread_clicked() {
  threadA.start();
  ui->btnStartThread->setEnabled(false);
  ui->btnStopThread->setEnabled(true);
  ui->btnDiceBegin->setEnabled(true);
  ui->btnDiceEnd->setEnabled(false);
}

void Widget::on_btnDiceBegin_clicked() {
  threadA.diceBegin();
  ui->btnDiceBegin->setEnabled(false);
  ui->btnDiceEnd->setEnabled(true);
}

void Widget::on_btnDiceEnd_clicked() {
  threadA.dicePause();
  ui->btnDiceBegin->setEnabled(true);
  ui->btnDiceEnd->setEnabled(false);
}

void Widget::on_btnStopThread_clicked() {
  threadA.stopThread();
  threadA.wait();
  ui->btnStartThread->setEnabled(true);
  ui->btnStopThread->setEnabled(false);
  ui->btnDiceBegin->setEnabled(false);
  ui->btnDiceEnd->setEnabled(false);
}

void Widget::on_btnClear_clicked() { ui->plainTextEdit->clear(); }
