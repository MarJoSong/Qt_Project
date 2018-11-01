#include "qwdialoglocate.h"
#include "ui_qwdialoglocate.h"
#include "mainwindow.h"

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

void QWDialogLocate::setSpinValue(int rowNo, int colNo)
{
    ui->sbRow->setValue(rowNo);
    ui->sbColumn->setValue(colNo);
}

void QWDialogLocate::on_btnSetText_clicked()
{
    int row = ui->sbRow->value();
    int col = ui->sbColumn->value();
    MainWindow *parWind = (MainWindow*)parentWidget();
    parWind->setACellText(row, col, ui->edtCaption->text());
    if(ui->chkBoxRow->isChecked())
        ui->sbRow->setValue(1 + ui->sbRow->value());
    if(ui->chkBoxCol->isChecked())
        ui->sbColumn->setValue(1 + ui->sbColumn->value());
}

void QWDialogLocate::closeEvent(QCloseEvent *event)
{
    MainWindow *parWind = (MainWindow*)parentWidget();
    parWind->setActLocateEnable(true);
    parWind->setDlgLocateNull();
}
