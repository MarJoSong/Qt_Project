#include "qwdialogheaders.h"
#include "ui_qwdialogheaders.h"

QWDialogHeaders::QWDialogHeaders(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogHeaders)
{
    ui->setupUi(this);
    stringList =new QStringListModel;
    ui->listView->setModel(stringList);
}

QWDialogHeaders::~QWDialogHeaders()
{
    delete ui;
}

void QWDialogHeaders::setHeaders(QStringList& headers)
{
    stringList->setStringList(headers);
}

QStringList QWDialogHeaders::headerList()
{
    return stringList->stringList();
}

