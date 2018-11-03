#include "qwdialogheader.h"
#include "ui_qwdialogheader.h"

#include <QMessageBox>

QWDialogHeader::QWDialogHeader(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogHeader)
{
    ui->setupUi(this);
    model = new QStringListModel;
    ui->listView->setModel(model);
}

QWDialogHeader::~QWDialogHeader()
{
    delete ui;
    QMessageBox::information(this,"提示", "~QWDialogHeader()");
}

void QWDialogHeader::setHeaders(QStringList &headers)
{
    model->setStringList(headers);
}

QStringList QWDialogHeader::headerList()
{
    return model->stringList();
}
