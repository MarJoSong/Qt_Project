#ifndef QMYWIDGET_H
#define QMYWIDGET_H

#include <QWidget>

namespace Ui {
class qMYWidget;
}

class qMYWidget : public QWidget
{
    Q_OBJECT

public:
    explicit qMYWidget(QWidget *parent = 0);
    ~qMYWidget();
    void seeOK(bool);

private slots:
    void on_btnAppend_clicked();

    void on_btnPrepend_clicked();

    void on_btnToUpper_clicked();

    void on_toLower_clicked();

    void on_btnCount_clicked();

    void on_btnSize_clicked();

    void on_btnTrimmed_clicked();

    void on_btnSimplified_clicked();

    void on_btnIndexOf_clicked();

    void on_bnLastIndexof_clicked();

    void on_btnIsNull_clicked();

    void on_btnIsEmpty_clicked();

    void on_btnContains_clicked();

    void on_endsWith_clicked();

    void on_btnStartsWith_clicked();

    void on_btnLeft_clicked();

    void on_btnRight_clicked();

    void on_btnSection_clicked();

private:
    Ui::qMYWidget *ui;
};

#endif // QMYWIDGET_H
