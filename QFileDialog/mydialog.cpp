#include "mydialog.h"

#include "stdafx.h"
#include "ui_mydialog.h"

MyDialog::MyDialog(QWidget *parent) : QDialog(parent), ui(new Ui::MyDialog) {
  ui->setupUi(this);

  connect(ui->btnOpen, SIGNAL(clicked()), this, SLOT(btnOpen_clicked()));
  connect(ui->btnOpenMulti, SIGNAL(clicked()), this,
          SLOT(btnOpenMulti_clicked()));
  connect(ui->btnSelDir, SIGNAL(clicked()), this, SLOT(btnSelDir_clicked()));
  connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(btnSave_clicked()));
  connect(ui->btnSelColro, SIGNAL(clicked()), this, SLOT(btnColor_clicked()));
  connect(ui->btnSelFont, SIGNAL(clicked()), this, SLOT(btnFont_clicked()));
  connect(ui->btnInputString, SIGNAL(clicked()), this,
          SLOT(btnInputString_clicked()));
  connect(ui->btnInputInt, SIGNAL(clicked()), this,
          SLOT(btnInputInt_clicked()));
  connect(ui->btnInputFloat, SIGNAL(clicked()), this,
          SLOT(btnInputFloat_clicked()));
  connect(ui->btnInputItem, SIGNAL(clicked()), this,
          SLOT(btnInputItem_clicked()));
}

MyDialog::~MyDialog() { delete ui; }

void MyDialog::btnOpen_clicked() {
  QString curPath = QDir::currentPath();
  QString dlgTitle = "选择一个文件";
  QString filter = "文本文件(*.txt);;图片文件(*.jpg *.gif);;所有文件(*.*)";
  QString aFileName =
      QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
  if (!aFileName.isEmpty()) ui->plainTextEdit->appendPlainText(aFileName);
}

void MyDialog::btnOpenMulti_clicked() {
  QString curPath = QDir::currentPath();
  QString dlgTitle = "选择多个文件";
  QString filter = "文本文件(*.txt);;图片文件(*.jpg *.gif);;所有文件(*.*)";
  QStringList fileNameList =
      QFileDialog::getOpenFileNames(this, dlgTitle, curPath, filter);
  for (int i = 0; i < fileNameList.count(); i++)
    ui->plainTextEdit->appendPlainText(fileNameList.at(i));
}

void MyDialog::btnSelDir_clicked() {
  QString curPath = QCoreApplication::applicationDirPath();
  QString dlgTitle = "选择一个目录";
  QString selectedDir = QFileDialog::getExistingDirectory(
      this, dlgTitle, curPath, QFileDialog::ShowDirsOnly);
  if (!selectedDir.isEmpty()) ui->plainTextEdit->appendPlainText(selectedDir);
}

void MyDialog::btnSave_clicked() {
  QString curPath = QDir::currentPath();
  QString dlgTitle = "保存文件";
  QString filter = "头文件(*.h);;源文件(*.cpp);;所有文件(*.*)";
  QString aFileName =
      QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);
  if (!aFileName.isEmpty()) ui->plainTextEdit->appendPlainText(aFileName);
}

void MyDialog::btnColor_clicked() {
  QPalette pal = ui->plainTextEdit->palette();
  QColor iniColor = pal.color(QPalette::Text);
  QColor color = QColorDialog::getColor(iniColor, this, "选择颜色");
  if (color.isValid()) {
    pal.setColor(QPalette::Text, color);
    ui->plainTextEdit->setPalette(pal);
  }
}

void MyDialog::btnFont_clicked() {
  QFont inifont = ui->plainTextEdit->font();
  bool ok = false;
  QFont font = QFontDialog::getFont(&ok, inifont);
  if (ok) ui->plainTextEdit->setFont(font);
}

void MyDialog::btnInputString_clicked() {
  QString dlgTitle = "输入文字对话框";
  QString txtLabel = "请输入文件名";
  QString defaultInput = "新建文件.txt";
  // QLineEdit::EchoMode echo = QLineEdit::Normal;
  QLineEdit::EchoMode echo = QLineEdit::Password;
  bool ok;
  QString text =
      QInputDialog::getText(this, dlgTitle, txtLabel, echo, defaultInput, &ok);
  if (ok && !text.isEmpty()) ui->plainTextEdit->appendPlainText(text);
}

void MyDialog::btnInputInt_clicked() {
  QString dlgTitle = "输入整数对话框";
  QString txtLabel = "设置字体大小";
  int defaultInput = ui->plainTextEdit->font().pointSize();
  int minValue = 6, maxValue = 50, setpValue = 1;
  bool ok;
  int fontSize = QInputDialog::getInt(this, dlgTitle, txtLabel, defaultInput,
                                      minValue, maxValue, setpValue, &ok);
  if (ok) {
    QFont font = ui->plainTextEdit->font();
    font.setPointSize(fontSize);
    ui->plainTextEdit->setFont(font);
  }
}

void MyDialog::btnInputFloat_clicked() {
  QString dlgTitle = "输入整数对话框";
  QString txtLabel = "设置字体大小";
  float defaultValue = 3.13;
  float minValue = 0, maxValue = 10000;
  int decimals = 2;
  bool ok;
  float inputValue =
      QInputDialog::getDouble(this, dlgTitle, txtLabel, defaultValue, minValue,
                              maxValue, decimals, &ok);
  if (ok) {
    QString str = QString::asprintf("输入了一个浮点数:%.2f", inputValue);
    ui->plainTextEdit->setFont(str);
  }
}

void MyDialog::btnInputItem_clicked() {
  QStringList items;
  items << "优秀"
        << "良好"
        << "合格"
        << "不合格";
  QString dlgTitle = "条目选择对话框";
  QString txtLabel = "选择级别";
  int curIndex = 0;
  bool editable = true;
  bool ok = false;
  QString text = QInputDialog::getItem(this, dlgTitle, txtLabel, items,
                                       curIndex, editable, &ok);
  if (ok && !text.isEmpty()) ui->plainTextEdit->appendPlainText(text);
}
