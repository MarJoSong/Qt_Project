#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QTextStream>


bool MainWindow::openTextByIODevice(const QString& aFileName)
{
    QFile aFile(aFileName);
    if(!aFile.exists())
        return false;
    if(!aFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    ui->plainTextEdit->setPlainText(aFile.readAll());
    aFile.close();
    ui->tabWidget->setCurrentIndex(0);
    return true;
}

bool MainWindow::saveTextByIODevice(const QString& aFileName)
{
    QFile aFile(aFileName);
    if(!aFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QString str = ui->plainTextEdit->toPlainText();
    QByteArray strBytes = str.toUtf8();
    aFile.write(strBytes, strBytes.length());
    aFile.close();
    ui->tabWidget->setCurrentIndex(0);
    return true;
}

bool MainWindow::openTextByStream(const QString &aFileName)
{
    QFile aFile(aFileName);
    if(!aFile.exists())
        return false;
    if(!aFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QTextStream aStream(&aFile);
    aStream.setAutoDetectUnicode(true);
    ui->plainTextEdit_2->setPlainText(aStream.readAll());
    aFile.close();
    ui->tabWidget->setCurrentIndex(1);
    return true;
}

bool MainWindow::saveTextByStream(const QString &aFileName)
{
    QFile aFile(aFileName);
    if(!aFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream aStream(&aFile);
    aStream.setAutoDetectUnicode(true);
    QString str = ui->plainTextEdit_2->toPlainText();
    aStream << str;
    aFile.close();
    return true;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actQFileOpen_triggered()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "打开一个文件";
    QString filter = "程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)";
    QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
    if(aFileName.isEmpty())
        return;
    openTextByIODevice(aFileName);
}

void MainWindow::on_actQFileSave_triggered()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "另存为一个文件";
    QString filter = "h文件(*.h);;c++(*.cpp);;所有文件(*.*)";
    QString aFileName = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);
    if(aFileName.isEmpty())
        return;
    saveTextByIODevice(aFileName);
}

void MainWindow::on_actQTextStreamOpen_triggered()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "打开一个文件";
    QString filter = "程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)";
    QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
    if(aFileName.isEmpty())
        return;
    openTextByStream(aFileName);
}

void MainWindow::on_actQTextStreamSave_triggered()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "另存为一个文件";
    QString filter = "h文件(*.h);;c++(*.cpp);;所有文件(*.*)";
    QString aFileName = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);
    if(aFileName.isEmpty())
        return;
    saveTextByStream(aFileName);
}
