#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStringListModel>

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
    void on_btnAppendList_clicked();

    void on_btnInsertList_clicked();

    void on_btnListDelete_clicked();

    void on_btnListClear_clicked();

    void on_btnShowStringList_clicked();

    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::Widget *ui;
    QStringListModel *model;
};

#endif // WIDGET_H
