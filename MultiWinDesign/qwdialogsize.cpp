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
    return ui->sbRow->value();
}

int QWDialogSize::colCount()
{
    return ui->sbCol->value();
}

void QWDialogSize::setRowColumn(int row, int col)
{
    ui->sbRow->setValue(row);
    ui->sbCol->setValue(col);
}
