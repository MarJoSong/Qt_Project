#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QStringListModel>
#include <qwdialogheaders.h>
#include <qwdialoglocate.h>
#include <qwdialogsize.h>
#include <QItemSelectionModel>
#include <QMessageBox>
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setACellText(int row, int column, QString text);

    void setActLocateEnable(bool enable);

    void setDlgLocateNull();

private slots:
    void on_actSetSize_triggered();

    void on_actSetHeader_triggered();

    void on_actLocate_triggered();

    void on_tableView_clicked(const QModelIndex &index);


private:
    Ui::MainWindow *ui;

    QStandardItemModel *theModel;
    QItemSelectionModel *theSelection;
    QWDialogHeaders *dlgSetHeaders = NULL;
    QWDialogLocate  *dlgLocate = NULL;

    void closeEvent(QCloseEvent *event);

signals:
    void cellIndexChange(int rowNo, int colSNo);

};




#endif // MAINWINDOW_H
