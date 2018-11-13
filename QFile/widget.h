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
    void showBtnInfo(QObject*);

private slots:
    void on_baseName_clicked();

    void on_openFile_clicked();

    void on_clearInfo_clicked();

    void on_applicationDirPath_clicked();

    void on_applicationFilePath_clicked();

    void on_applicationName_clicked();

    void on_setOrganizationName_clicked();

    void on_organizationName_clicked();

    void on_exit_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
