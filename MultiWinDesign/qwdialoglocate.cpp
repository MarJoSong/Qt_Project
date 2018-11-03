#include "qwdialoglocate.h"
#include "ui_qwdialoglocate.h"
#include "qformtable.h"

QWDialogLocate::QWDialogLocate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogLocate)
{
    ui->setupUi(this);
}

QWDialogLocate::~QWDialogLocate()
{
    delete ui;
}

void QWDialogLocate::setSpinRange(int row, int col)
{
    ui->sbRow->setMaximum(row);
    ui->sbCol->setMaximum(col);
}

void QWDialogLocate::setSpinValue(int row, int col)
{
    ui->sbRow->setValue(row+1);
    ui->sbCol->setValue(col+1);
}

void QWDialogLocate::on_btnText_clicked()
{
    int row = ui->sbRow->value();
    int col = ui->sbCol->value();
    QString text = ui->lineEdit->text();
    emit changeACellText(row, col, text);
    if(ui->chkRow->isChecked())
        ui->sbRow->setValue(1+ui->sbRow->value());
    if(ui->chkCol->isChecked())
        ui->sbCol->setValue(1+ui->sbCol->value());
}

void QWDialogLocate::closeEvent(QCloseEvent *event)
{
    emit actLocateEnable(true);
}

void QWDialogLocate::showEvent(QShowEvent *event)
{
    emit actLocateEnable(false);
}
