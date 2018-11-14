#include "widget.h"
#include "ui_widget.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include "qwdialogfilename.h"
#include <QFileInfo>
#include <QDateTime>

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
    ui->plainTextEdit->appendPlainText(thebtn->text()+":  "+thebtn->toolTip());
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


void Widget::on_Remove_clicked()
{
    QFile::remove(ui->fileEdit->text());
    QMessageBox::information(this, "提示", "文件已删除");
}

void Widget::on_Copy_clicked()
{
    if(ui->fileEdit->text()=="")
    {
        QMessageBox::information(this, "提示", "需要先打开一个文件");
        return;
    }
    QWDialogFileName* copyName = new QWDialogFileName(this);
    copyName->setCopyName(ui->fileEdit->text());
    int ret = copyName->exec();
    if(ret == QDialog::Accepted)
    {
        QString str = copyName->copyName();
        if(str == ui->fileEdit->text())
        {
            QMessageBox::information(this, "提示", "命名不能和原件相同");
            return;
        }
        QFile::copy(ui->fileEdit->text(), str);
        QMessageBox::information(this, "提示", "复制成功");
    }
    delete copyName;
}

void Widget::on_Rename_clicked()
{
    if(ui->fileEdit->text()=="")
    {
        QMessageBox::information(this, "提示", "需要先打开一个文件");
        return;
    }
    QWDialogFileName* rename = new QWDialogFileName(this);
    rename->setCopyName(ui->fileEdit->text());
    int ret = rename->exec();
    if(ret == QDialog::Accepted)
    {
        QString str = rename->copyName();
        if(str == ui->fileEdit->text())
        {
            QMessageBox::information(this, "提示", "命名一致，不予操作");
            return;
        }
        QFile::rename(ui->fileEdit->text(), str);
        QMessageBox::information(this, "提示", "重命名成功");
    }
    delete rename;
}

void Widget::on_Exist_clicked()
{
    if(QFile::exists(ui->fileEdit->text()))
    {
        QMessageBox::information(this, "提示", "文件存在");
        return;
    }
    QMessageBox::information(this, "提示", "文件不存在");
}

void Widget::on_fileCopy_clicked()
{
    QFile aFile;
    aFile.setFileName(ui->fileEdit->text());
    QFileInfo fileInfo(aFile);
    QString newFile = fileInfo.path() + "/" + fileInfo.baseName() + "--副本." + fileInfo.suffix();
    aFile.copy(newFile);
    QMessageBox::information(this, "提示", "复制成功");
}

void Widget::on_fileRename_clicked()
{
    showBtnInfo(sender());
    QFile aFile;
    aFile.setFileName(ui->fileEdit->text());

    QWDialogFileName* rename = new QWDialogFileName(this);
    rename->setCopyName(ui->fileEdit->text());
    int ret = rename->exec();
    if(ret == QDialog::Accepted)
    {
        QString newFile = rename->copyName();
        if(newFile == ui->fileEdit->text())
        {
            QMessageBox::information(this, "提示", "命名一致，不予操作");
            return;
        }
        aFile.copy(newFile);
        QMessageBox::information(this, "提示", "重命名成功");
    }
    delete rename;
}

void Widget::on_fileRemove_clicked()
{
    showBtnInfo(sender());
    QFile aFile(ui->fileEdit->text());
    QFileInfo fileInfo(aFile);
    aFile.remove();
    QMessageBox::information(this, "提示", "已删除文件"+fileInfo.baseName()+"."+fileInfo.suffix());

}

void Widget::on_fileExist_clicked()
{
    showBtnInfo(sender());
    QFile aFile(ui->fileEdit->text());
    QFileInfo fileInfo(aFile);
    if(aFile.exists())
    {
        ui->plainTextEdit->appendPlainText("文件"+fileInfo.baseName()+"."+fileInfo.suffix()+"存在\n");
        return;
    }
    QMessageBox::warning(this, "警告", "文件"+fileInfo.baseName()+"."+fileInfo.suffix()+"不存在\n");
}

void Widget::on_size_clicked()
{
    showBtnInfo(sender());
    QFile aFile(ui->fileEdit->text());
    QFileInfo fileInfo(aFile);
    if(fileExist(aFile))
    {
        qint64 sizeint = aFile.size();
        QString sizestr = QString::number(sizeint);
        ui->plainTextEdit->appendPlainText(sizestr+"字节\n");
    }
}

bool Widget::fileExist(const QFile& aFile)
{
    QFileInfo fileInfo(aFile);
    if(aFile.exists())
        return true;
    QMessageBox::warning(this, "警告", "文件"+fileInfo.baseName()+"."+fileInfo.suffix()+"不存在\n");
    return false;
}

void Widget::on_setFile_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo;
    fileInfo.setFile(ui->fileEdit->text());
    ui->plainTextEdit->appendPlainText(fileInfo.absoluteFilePath()+"\n");
}

void Widget::on_fileName_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->fileEdit->text());
    ui->plainTextEdit->appendPlainText(fileInfo.fileName()+"\n");
}

void Widget::on_filePath_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->fileEdit->text());
    ui->plainTextEdit->appendPlainText(fileInfo.filePath()+"\n");
}

void Widget::on_Path_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->fileEdit->text());
    ui->plainTextEdit->appendPlainText(fileInfo.path()+"\n");
}

void Widget::on_baseName_5_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->fileEdit->text());
    ui->plainTextEdit->appendPlainText(fileInfo.absolutePath()+"\n");
}

void Widget::on_baseName_2_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->fileEdit->text());
    ui->plainTextEdit->appendPlainText(fileInfo.absoluteFilePath()+"\n");
}

void Widget::on_size_2_clicked()
{
    showBtnInfo(sender());
    QFile aFile(ui->fileEdit->text());
    QFileInfo fileInfo(aFile);
    if(fileExist(aFile))
    {
        qint64 sizeint = aFile.size();
        QString sizestr = QString::number(sizeint);
        ui->plainTextEdit->appendPlainText(sizestr+"字节\n");
    }
}

void Widget::on_baseName_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->fileEdit->text());
    ui->plainTextEdit->appendPlainText(fileInfo.baseName()+"\n");
}

void Widget::on_suffix_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->fileEdit->text());
    ui->plainTextEdit->appendPlainText(fileInfo.suffix()+"\n");
}

void Widget::on_isDir_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->fileEdit->text());
    if(fileInfo.isDir())
    {
        ui->plainTextEdit->appendPlainText(fileInfo.fileName()+"是目录\n");
        return;
    }
    ui->plainTextEdit->appendPlainText(fileInfo.fileName()+"不是目录\n");
}

void Widget::on_pushButton_4_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->fileEdit->text());
    if(fileInfo.isFile())
    {
        ui->plainTextEdit->appendPlainText(fileInfo.fileName()+"是文件\n");
        return;
    }
    ui->plainTextEdit->appendPlainText(fileInfo.fileName()+"不是文件\n");
}

void Widget::on_pushButton_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->fileEdit->text());
    if(fileInfo.isExecutable())
    {
        ui->plainTextEdit->appendPlainText(fileInfo.fileName()+"是可执行文件\n");
        return;
    }
    ui->plainTextEdit->appendPlainText(fileInfo.fileName()+"不是可执行文件\n");
}

void Widget::on_createdTime_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->fileEdit->text());
    QDateTime data = fileInfo.created();
    ui->plainTextEdit->appendPlainText(data.toString()+"\n");
}

void Widget::on_pushButton_6_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->fileEdit->text());
    QDateTime data = fileInfo.lastModified();
    ui->plainTextEdit->appendPlainText(data.toString()+"\n");
}

void Widget::on_pushButton_7_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->fileEdit->text());
    QDateTime data = fileInfo.lastRead();
    ui->plainTextEdit->appendPlainText(data.toString()+"\n");
}

void Widget::on_pushButton_8_clicked()
{
    showBtnInfo(sender());
    QFileInfo fileInfo(ui->fileEdit->text());
    if(fileInfo.exists())
    {
        ui->plainTextEdit->appendPlainText(fileInfo.fileName()+"存在\n");
        return;
    }
    ui->plainTextEdit->appendPlainText(fileInfo.fileName()+"不存在\n");
}
