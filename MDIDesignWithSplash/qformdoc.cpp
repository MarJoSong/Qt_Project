#include "qformdoc.h"
#include "ui_qformdoc.h"

#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QFontDialog>

QFormDoc::QFormDoc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QFormDoc)
{
    ui->setupUi(this);
    this->setWindowTitle("新文档");
    this->setAttribute(Qt::WA_DeleteOnClose);
}

QFormDoc::~QFormDoc()
{
    delete ui;
}

void QFormDoc::loadFromFile(QString& aFileName)
{
    QFile aFile(aFileName);
    if(aFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream aStream(&aFile);
        ui->plainTextEdit->clear();
        ui->plainTextEdit->setPlainText(aStream.readAll());
        aFile.close();
        mCurrentFile = aFileName;
        QFileInfo   fileInfo(aFileName);
        QString     str = fileInfo.fileName();
        this->setWindowTitle(str);
        mFileOpened = true;
    }
}

QString QFormDoc::currentFileName()
{
    return mCurrentFile;
}

bool QFormDoc::isFileOpened()
{
    return mFileOpened;
}

void QFormDoc::setEditFont()
{
    QFont font = ui->plainTextEdit->font();
    bool ok;
    font = QFontDialog::getFont(&ok, font);
    ui->plainTextEdit->setFont(font);
}

void QFormDoc::textCut()
{
    ui->plainTextEdit->cut();
}

void QFormDoc::textCopy()
{
    ui->plainTextEdit->copy();
}

void QFormDoc::textPaste()
{
    ui->plainTextEdit->paste();
}

void QFormDoc::fileSave(QString aFileName)
{
    QString str = ui->plainTextEdit->toPlainText();
    QFile aFile(aFileName);
    if(!aFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate))
        return;
    QTextStream aStream(&aFile);
    aStream << str;
    aFile.close();
}


