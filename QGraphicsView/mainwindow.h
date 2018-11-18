#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QGraphicsScene>
#include <QResizeEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLabel* labViewPos;
    QLabel* labScenePos;
    QLabel* labItemPos;
    QLabel* labNone;

    QGraphicsScene *scene;
    void iniGraphicsSystem();

protected:
    void resizeEvent(QResizeEvent *event);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_mouseMovePoint(QPoint point);
    void on_mouseClicked(QPoint point);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
