#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QStringListModel>
#include <qwdialogheaders.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actSetSize_triggered();

    void on_actSetHeader_triggered();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *theModel;
    QWDialogHeaders *dlgSetHeaders = NULL;

};

#endif // MAINWINDOW_H
