#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDataWidgetMapper>
#include <QItemSelectionModel>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlTableModel>

#include "qwcomboboxdelegate.h"
#include "stdafx.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 private:
  QSqlDatabase DB;
  QSqlTableModel *tabModel;
  QItemSelectionModel *theSelection;
  QDataWidgetMapper *dataMappler;
  QWComboBoxDelegate delegateSex;
  QWComboBoxDelegate delegateDepart;
  void openTable();
  void getFieldNames();

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_currentChanged(const QModelIndex &current,
                         const QModelIndex &previous);
  void on_currentRowChanged(const QModelIndex &current,
                            const QModelIndex &previous);

  void on_actOpenDB_triggered();

  void on_actRecAppend_triggered();

  void on_actRecInsert_triggered();

  void on_actRecDelete_triggered();

  void on_actSubmit_triggered();

  void on_actRevert_triggered();

  void on_actPhoto_triggered();

  void on_actPhotoClear_triggered();

  void on_actScan_triggered();

  void on_comboFields_currentIndexChanged(int index);

  void on_radioBtnAscend_clicked();

  void on_radioBtnDescend_clicked();

  void on_radioBtnMan_clicked();

  void on_radioBtnWoman_clicked();

  void on_radioBtnBoth_clicked();

 private:
  Ui::MainWindow *ui;
};

#endif  // MAINWINDOW_H
