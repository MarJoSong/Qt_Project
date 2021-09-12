#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget {
  Q_OBJECT

 public:
  explicit Widget(QWidget *parent = 0);
  ~Widget();

 private slots:
  void btnOpen_clicked();

  void btnOpenMulti_clicked();

  void btnSelDir_clicked();

  void btnSave_clicked();

  void btnColor_clicked();

  void btnFont_clicked();

  void btnInputString_clicked();

  void btnInputInt_clicked();

  void btnInputDouble_clicked();

  void btnInputItem_clicked();

  void btnClear_clicked();

  void btnMsgInformation_clicked();

  void btnMsgWarning_clicked();

  void btnMsgCritical_clicked();

  void btnMsgAbout_clicked();

  void btnMsgQuestion_clicked();

 private:
  Ui::Widget *ui;
};

#endif  // WIDGET_H
