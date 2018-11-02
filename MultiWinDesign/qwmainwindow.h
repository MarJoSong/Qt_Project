#ifndef QWMAINWINDOW_H
#define QWMAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>

namespace Ui {
class QWMainWindow;
}

class QWMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QWMainWindow(QWidget *parent = 0);
    ~QWMainWindow();

private slots:
    void on_actWidgetInsite_triggered();

    void on_actWidget_triggered();

    void on_actWindowInsite_triggered();

private:
    Ui::QWMainWindow *ui;

    void paintEvent(QPaintEvent *event);
};

#endif // QWMAINWINDOW_H
