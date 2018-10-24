#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QStringList cityList;
    cityList << "北京" << "上海" << "芜湖" << "武汉";
    model = new QStringListModel(this);
    model->setStringList(cityList);
    ui->listView->setModel(model);
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked |
                                  QAbstractItemView::SelectedClicked);
    //QAbstractItemView::NoEditTriggers为设置为不可编辑
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnAppendList_clicked()
{
    model->insertRow(model->rowCount());
    QModelIndex index = model->index(model->rowCount()-1, 0);
    model->setData(index, "new item", Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
}

void Widget::on_btnInsertList_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    model->insertRow(index.row());
    model->setData(index, "inserted item", Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
}

void Widget::on_btnListDelete_clicked()
{
    QModelIndex index = ui->listView->currentIndex();
    model->removeRow(index.row());
}

void Widget::on_btnListClear_clicked()
{
    model->removeRows(0,model->rowCount());
}

void Widget::on_btnShowStringList_clicked()
{
    QStringList tmpList = model->stringList();
    ui->plainTextEdit->clear();
    for(int i=0; i<tmpList.count(); i++)
        ui->plainTextEdit->appendPlainText(tmpList.at(i));
}

void Widget::on_listView_clicked(const QModelIndex &index)
{
    ui->labShowPos->setText(QString::asprintf("Row = %d, column = %d",index.row(), index.column()));
}
