#include "widget.h"
#include "ui_widget.h"
#include <QDir>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QLineEdit>
#include <QInputDialog>

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

void Widget::on_btnOpen_clicked()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "选择一个文件";
    QString filter = "文本文件(*.txt);;图片文件(*.jpg *.gif);;所有文件(*.*)";
    QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
    if(!aFileName.isEmpty())
        ui->plainTextEdit->appendPlainText(aFileName);
}

void Widget::on_btnOpenMulti_clicked()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "选择多个文件";
    QString filter = "文本文件(*.txt);;图片文件(*.jpg *.gif);;所有文件(*.*)";
    QStringList fileNameList = QFileDialog::getOpenFileNames(this, dlgTitle, curPath, filter);
    for(int i=0; i<fileNameList.count(); i++)
        ui->plainTextEdit->appendPlainText(fileNameList.at(i));
}

void Widget::on_btnSelDir_clicked()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString dlgTitle = "选择一个目录";
    QString selectedDir = QFileDialog::getExistingDirectory(this, dlgTitle, curPath,
                            QFileDialog::ShowDirsOnly);
    if(!selectedDir.isEmpty())
        ui->plainTextEdit->appendPlainText(selectedDir);
}



void Widget::on_btnSave_clicked()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "保存文件";
    QString filter = "头文件(*.h);;源文件(*.cpp);;所有文件(*.*)";
    QString aFileName = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);
    if(!aFileName.isEmpty())
        ui->plainTextEdit->appendPlainText(aFileName);
}

void Widget::on_btnColor_clicked()
{
    QPalette pal = ui->plainTextEdit->palette();
    QColor iniColor = pal.color(QPalette::Text);
    QColor color = QColorDialog::getColor(iniColor, this, "选择颜色");
    if(color.isValid())
    {
        pal.setColor(QPalette::Text, color);
        ui->plainTextEdit->setPalette(pal);
    }
}



void Widget::on_btnFont_clicked()
{
    QFont inifont = ui->plainTextEdit->font();
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, inifont);
    if(ok)
        ui->plainTextEdit->setFont(font);
}

void Widget::on_btnInputString_clicked()
{
    QString dlgTitle = "输入文字对话框";
    QString txtLabel = "请输入文件名";
    QString defaultInput = "花花";
    QLineEdit::EchoMode echo = QLineEdit::Normal;
    bool ok;
    QString text = QInputDialog::getText(this, dlgTitle, txtLabel,
            echo, defaultInput, &ok);
    if(ok && !text.isEmpty())
        ui->plainTextEdit->appendPlainText(text);
}

void Widget::on_btnInputInt_clicked()
{
    QString dlgTitle = "输入整数对话框";
    QString txtLabel = "设置字体大小";
    int defaultInput = ui->plainTextEdit->font().pointSize();
    int minValue =6, maxValue = 50, setpValue = 1;
    bool ok;
    int fontSize = QInputDialog::getInt(this, dlgTitle, txtLabel,
            defaultInput, minValue, maxValue, setpValue, &ok);
    if(ok)
    {
        QFont font = ui->plainTextEdit->font();
        font.setPointSize(fontSize);
        ui->plainTextEdit->setFont(font);
    }
}

void Widget::on_btnInputDouble_clicked()
{
    QString dlgTitle = "输入浮点数对话框";
    QString txtLabel = "输入一个浮点数";
    float defaultDouble = 6.96;
    float minValue = 0, maxValue = 10000;
    int decimals = 2;
    bool ok;
    float inputValue = QInputDialog::getDouble(this, dlgTitle, txtLabel,
            defaultDouble, minValue, maxValue, decimals, &ok);
    if(ok)
    {
        QString str = QString::asprintf("输入了一个浮点数: %.2f", inputValue);
        ui->plainTextEdit->appendPlainText(str);
    }
}

void Widget::on_btnInputItem_clicked()
{
    QStringList items;
    items << "Great" << "Good" << "Qualified" <<"Unqualified";
    QString dlgTitle = "条目选择对话框";
    QString txtLabel = "选择级别";
    int curIndex = 0;
    bool editable = true;
    bool ok = false;
    QString text = QInputDialog::getItem(this, dlgTitle, txtLabel,
            items, curIndex, editable, &ok);
    if(ok && !text.isEmpty())
        ui->plainTextEdit->appendPlainText(text);
}

void Widget::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}
