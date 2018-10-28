#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_btnOpen_clicked();

    void on_btnOpenMulti_clicked();

    void on_btnSelDir_clicked();

    void on_btnSave_clicked();

    void on_btnColor_clicked();

    void on_btnFont_clicked();

    void on_btnInputString_clicked();

    void on_btnInputInt_clicked();

    void on_btnInputDouble_clicked();

    void on_btnInputItem_clicked();

    void on_btnClear_clicked();

    void on_btnMsgInformation_clicked();

    void on_btnMsgWarning_clicked();

    void on_btnMsgCritical_clicked();

    void on_btnMsgAbout_clicked();

    void on_btnMsgQuestion_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
