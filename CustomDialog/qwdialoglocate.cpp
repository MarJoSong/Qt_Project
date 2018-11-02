#include "qwdialoglocate.h"
#include "ui_qwdialoglocate.h"

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

void QWDialogLocate::setSpinRange(int rowCount, int ColCount)
{
    ui->sbRow->setMaximum(rowCount);
    ui->sbColumn->setMaximum(ColCount);
}

void QWDialogLocate::setSpinValue(int rowNo, int colNo)
{
    ui->sbRow->setValue(rowNo + 1);
    ui->sbColumn->setValue(colNo + 1);
}

void QWDialogLocate::on_btnSetText_clicked()
{
    int row = ui->sbRow->value();
    int col = ui->sbColumn->value();
    QString text = ui->edtCaption->text();
    emit changeCellText(row, col, text);
    if(ui->chkBoxRow->isChecked())
        ui->sbRow->setValue(1 + ui->sbRow->value());
    if(ui->chkBoxCol->isChecked())
        ui->sbColumn->setValue(1 + ui->sbColumn->value());
}

void QWDialogLocate::closeEvent(QCloseEvent *event)
{
    emit changeActionEnable(true);
}

void QWDialogLocate::showEvent(QShowEvent *event)
{
    emit changeActionEnable(false);
}
