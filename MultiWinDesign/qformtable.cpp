#include "qformtable.h"
#include "ui_qformtable.h"

#include <QMessageBox>
#include <QToolBar>
#include <QVBoxLayout>

QFormTable::QFormTable(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QFormTable)
{
    ui->setupUi(this);
}

QFormTable::~QFormTable()
{
    delete ui;
    QMessageBox::information(this, "消息", "QFormTab对象被删除和释放");
}
