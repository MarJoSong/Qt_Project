#include "widget.h"
#include "ui_widget.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::showBtnInfo(QObject* btn)
{
    QPushButton *thebtn = static_cast<QPushButton*>(btn);
    ui->plainTextEdit->appendPlainText(thebtn->text());
    ui->plainTextEdit->appendPlainText(thebtn->toolTip()+"\n");
}

void Widget::on_baseName_clicked()
{
    QFileInfo fileInfo(ui->fileEdit->text());
    QString str = fileInfo.baseName();
    ui->plainTextEdit->appendPlainText(str+"\n");

    showBtnInfo(sender());
}

void Widget::on_openFile_clicked()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getOpenFileName(this, "打开一个文件", curPath, "所有文件(*.*)");
    if(aFileName.isEmpty())
        return;
    ui->fileEdit->setText(aFileName);
    QMessageBox::information(this, "提示", "文件已打开");
}

void Widget::on_clearInfo_clicked()
{
    ui->plainTextEdit->clear();
}

void Widget::on_applicationDirPath_clicked()
{
    showBtnInfo(sender());
    QString str = QCoreApplication::applicationFilePath();
    ui->plainTextEdit->appendPlainText(str+"\n");
}

void Widget::on_applicationFilePath_clicked()
{
    showBtnInfo(sender());
    QString str = QCoreApplication::applicationDirPath();
    ui->plainTextEdit->appendPlainText(str+"\n");
}

void Widget::on_applicationName_clicked()
{
    showBtnInfo(sender());
    QString str = QCoreApplication::applicationName();
    ui->plainTextEdit->appendPlainText(str+"\n");
}

void Widget::on_setOrganizationName_clicked()
{
    showBtnInfo(sender());
    QCoreApplication::setOrganizationName("Huahua");

}

void Widget::on_organizationName_clicked()
{
    showBtnInfo(sender());
    QString str = QCoreApplication::organizationName();
    ui->plainTextEdit->appendPlainText(str+"\n");
}

void Widget::on_exit_clicked()
{
    showBtnInfo(sender());
    QCoreApplication::exit();
}
