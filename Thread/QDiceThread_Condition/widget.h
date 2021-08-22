#ifndef WIDGET_H
#define WIDGET_H

#include <QTimer>
#include <QWidget>

#include "qmythread.h"
#include "stdafx.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT
 private:
  QThreadProducer threadProducer;
  QThreadConsumer threadConsumer;

 protected:
  void closeEvent(QCloseEvent *event);

 public:
  explicit Widget(QWidget *parent = nullptr);
  ~Widget();

 private slots:
  void onthreadProducer_started();
  void onthreadProducer_finished();
  void onthreadConsumer_started();
  void onthreadConsumer_finished();
  void onthreadConsumer_newValue(int seq, int diceValue);

  void on_btnStartThread_clicked();

  void on_btnStopThread_clicked();

  void on_btnClear_clicked();

 private:
  Ui::Widget *ui;
};
#endif  // WIDGET_H
