#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>

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
    void on_actImportLibrary_triggered();

    void on_actAddBook_triggered();

    void on_actEditUnable_triggered();

    void on_actSave_triggered();

private:
    Ui::MainWindow *ui;
    QStringListModel *bookModel;
    QString aFileName;
};

#endif // MAINWINDOW_H
