#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QLabel>
#include <QPoint>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    const static int ItemId = 1;
    static const int ItemDesciption = 2;
    int seqNum = 0;
    int frontZ = 0;
    int backZ = 0;
    QGraphicsScene* scene;
    QLabel* labViewCord;
    QLabel* labSceneCord;
    QLabel* labItemCord;
    QLabel* labItemInfo;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_mouseMovePoint(QPoint point);

    void on_mouseClicked(QPoint point);

    void on_mouseDoubleClicked(QPoint point);

    void on_keyPress(QKeyEvent *event);

    void on_actItem_Ellipse_triggered();

    void on_actItem_Rect_triggered();

    void on_actItem_Circle_triggered();

    void on_actItem_Line_triggered();

    void on_actZoomIn_triggered();

    void on_actZoomOut_triggered();

    void on_actRotateLeft_triggered();

    void on_actRotateRight_triggered();

    void on_actRestore_triggered();

    void on_actEdit_Front_triggered();

    void on_actEdit_Back_triggered();

    void on_actGroup_triggered();

    void on_actGroupBreak_triggered();

    void on_actEdit_Delete_triggered();

    void on_actItem_Triangle_triggered();

    void on_actItem_Polygon_triggered();

    void on_actItem_Text_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
