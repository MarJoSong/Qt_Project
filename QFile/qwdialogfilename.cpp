#include "qwdialogfilename.h"
#include "ui_qwdialogfilename.h"

QWDialogFileName::QWDialogFileName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogFileName)
{
    ui->setupUi(this);

}

QWDialogFileName::~QWDialogFileName()
{
    delete ui;
}

void QWDialogFileName::setCopyName(const QString& str)
{
    ui->editCopyName->setText(str);
}

QString QWDialogFileName::copyName()
{
    return ui->editCopyName->text();
}
