#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPaintEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *event);

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void sleep(unsigned int);
    void paintWhiteBlack();
    void paintBlackWhite();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
