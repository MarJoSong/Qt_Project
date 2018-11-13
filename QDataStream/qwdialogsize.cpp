#include "qwdialogsize.h"
#include "ui_qwdialogsize.h"

QWDialogSize::QWDialogSize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogSize)
{
    ui->setupUi(this);
}

QWDialogSize::~QWDialogSize()
{
    delete ui;
}

int QWDialogSize::rowCount()
{
    return ui->spinBoxRow->value();
}

int QWDialogSize::colCount()
{
    return ui->spinBoxCol->value();
}

void QWDialogSize::setRowCol(int row, int col)
{
    ui->spinBoxRow->setValue(row);
    ui->spinBoxCol->setValue(col);
}
