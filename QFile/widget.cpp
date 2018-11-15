#include "widget.h"
#include "ui_widget.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include "qwdialogfilename.h"
#include <QFileInfo>
#include <QDateTime>
#include <QDir>

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

void Widget::on_tempPath_clicked()
{
    showBtnInfo(sender());
    ui->plainTextEdit->appendPlainText(QDir::tempPath()+"\n");
}

void Widget::on_rootPath_clicked()
{
    showBtnInfo(sender());
    ui->plainTextEdit->appendPlainText(QDir::rootPath()+"\n");
}

void Widget::on_homePath_clicked()
{
    showBtnInfo(sender());
    ui->plainTextEdit->appendPlainText(QDir::homePath()+"\n");
}

void Widget::on_currentPath_clicked()
{
    showBtnInfo(sender());
    ui->plainTextEdit->appendPlainText(QDir::currentPath()+"\n");
}

void Widget::on_setCurrentPath_clicked()
{
    showBtnInfo(sender());
    QDir::setCurrent("D:/");
    ui->plainTextEdit->appendPlainText("设置D盘为当前路径\n");
}

void Widget::on_entryList_clicked()
{
    showBtnInfo(sender());
    QDir dir(ui->fileEdit->text());
    QStringList strList = dir.entryList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    ui->plainTextEdit->appendPlainText("当前文件夹下所有目录和文件");
    for(int i=0; i<strList.count(); i++)
        ui->plainTextEdit->appendPlainText(strList.at(i));
}

void Widget::on_pushButton_12_clicked()
{
    showBtnInfo(sender());
    ui->plainTextEdit->appendPlainText("监听目录: "+ui->dirEdit->text()+"\n");
    fileWatcher.addPath(ui->dirEdit->text());
    fileWatcher.addPath(ui->fileEdit->text());
    QObject::connect(&fileWatcher, &QFileSystemWatcher::directoryChanged,
                     this, &Widget::on_directoryChanged);
    QObject::connect(&fileWatcher, &QFileSystemWatcher::fileChanged,
                     this, &Widget::on_fileChanged);
}

void Widget::on_directoryChanged(const QString path)
{
    ui->plainTextEdit->appendPlainText(path);
    ui->plainTextEdit->appendPlainText("目录发生了变化\n");
}

void Widget::on_pushButton_13_clicked()
{
    showBtnInfo(sender());
    ui->plainTextEdit->appendPlainText("停止监听: "+ui->dirEdit->text()+"\n");
    fileWatcher.removePath(ui->dirEdit->text());
    fileWatcher.removePath(ui->fileEdit->text());
    QObject::disconnect(&fileWatcher, &QFileSystemWatcher::directoryChanged,
                     this, &Widget::on_directoryChanged);
    QObject::disconnect(&fileWatcher, &QFileSystemWatcher::fileChanged,
                     this, &Widget::on_fileChanged);
}

void Widget::on_fileChanged(const QString path)
{
    ui->plainTextEdit->appendPlainText(path);
    ui->plainTextEdit->appendPlainText("文件发生了变化\n");
}

void Widget::on_openDir_clicked()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getExistingDirectory(this, "打开一个目录", curPath);
    if(aFileName.isEmpty())
        return;
    ui->dirEdit->setText(aFileName);
    QMessageBox::information(this, "提示", "目录已打开");
}
