#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QColorDialog>
#include <QDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui {
class MyDialog;
}
QT_END_NAMESPACE

class MyDialog : public QDialog {
  Q_OBJECT

 public:
  MyDialog(QWidget *parent = nullptr);
  ~MyDialog();

 private slots:
  void btnOpen_clicked();
  void btnOpenMulti_clicked();
  void btnSelDir_clicked();
  void btnSave_clicked();
  void btnColor_clicked();
  void btnFont_clicked();

  void btnInputString_clicked();
  void btnInputInt_clicked();
  void btnInputFloat_clicked();
  void btnInputItem_clicked();

  void btnInputString_clicked();

 private:
  Ui::MyDialog *ui;
};
#endif  // MYDIALOG_H
