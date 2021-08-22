#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "qdicethread.h"
#include "stdafx.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT
 private:
  QDiceThread threadA;

 protected:
  void closeEvent(QCloseEvent *event);

 public:
  explicit Widget(QWidget *parent = nullptr);
  ~Widget();

 private slots:
  void onthreadA_started();
  void onthreadA_finished();
  void onthreadA_newValue(int seq, int diceValue);

  void on_btnStartThread_clicked();

  void on_btnDiceBegin_clicked();

  void on_btnDiceEnd_clicked();

  void on_btnStopThread_clicked();

  void on_btnClear_clicked();

 private:
  Ui::Widget *ui;
};
#endif  // WIDGET_H
