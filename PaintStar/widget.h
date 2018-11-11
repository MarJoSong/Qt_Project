#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPoint>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *event);

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
