#ifndef QMYWIDGET_H
#define QMYWIDGET_H

#include <QWidget>

namespace Ui {
class QmyWidget;
}

class QmyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QmyWidget(QWidget *parent = 0);
    ~QmyWidget();

private slots:
    void on_redSlider_valueChanged(int value);

    void on_dial_valueChanged(int value);

    void on_radioDec_clicked();

    void on_radioBin_clicked();

    void on_radioOct_clicked();

    void on_radioHex_clicked();

private:
    Ui::QmyWidget *ui;
};

#endif // QMYWIDGET_H
