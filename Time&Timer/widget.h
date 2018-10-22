#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTime>
#include <QTimer>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    QTimer * fTimer;
    QTime fTimeCounter;

private slots:
    void on_btnGetTime_clicked();

    void on_pushButton_4_clicked();

    void on_calendarWidget_selectionChanged();

    void on_timer_timeout();

    void on_btnStart_clicked();

    void on_btnStop_clicked();

    void on_btnSetIntv_clicked();

    void on_intVedit_valueChanged(const QString &arg1);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
