#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStandardItemModel>
#include <QItemSelectionModel>

#define FixedColumnCount 6

namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel *labCurFile;
    QLabel *labCurPos;
    QLabel *labCurText;
    QStandardItemModel *model;
    QItemSelectionModel *selection;
    void iniModelFromStringList(QStringList&);

private slots:
    void on_currentChanged(const QModelIndex &current, const QModelIndex &previous);
    void on_actOpen_triggered();
};

#endif // MAINWINDOW_H
