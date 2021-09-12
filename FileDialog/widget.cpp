#include "widget.h"

#include <QColorDialog>
#include <QDir>
#include <QFileDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>

#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
}

Widget::~Widget() { delete ui; }

void Widget::btnOpen_clicked() {
  QString curPath = QDir::currentPath();
  QString dlgTitle = "选择一个文件";
  QString filter = "文本文件(*.txt);;图片文件(*.jpg *.gif);;所有文件(*.*)";
  QString aFileName =
      QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
  if (!aFileName.isEmpty()) ui->plainTextEdit->appendPlainText(aFileName);
}

void Widget::btnOpenMulti_clicked() {
  QString curPath = QDir::currentPath();
  QString dlgTitle = "选择多个文件";
  QString filter = "文本文件(*.txt);;图片文件(*.jpg *.gif);;所有文件(*.*)";
  QStringList fileNameList =
      QFileDialog::getOpenFileNames(this, dlgTitle, curPath, filter);
  for (int i = 0; i < fileNameList.count(); i++)
    ui->plainTextEdit->appendPlainText(fileNameList.at(i));
}

void Widget::btnSelDir_clicked() {
  QString curPath = QCoreApplication::applicationDirPath();
  QString dlgTitle = "选择一个目录";
  QString selectedDir = QFileDialog::getExistingDirectory(
      this, dlgTitle, curPath, QFileDialog::ShowDirsOnly);
  if (!selectedDir.isEmpty()) ui->plainTextEdit->appendPlainText(selectedDir);
}

void Widget::btnSave_clicked() {
  QString curPath = QDir::currentPath();
  QString dlgTitle = "保存文件";
  QString filter = "头文件(*.h);;源文件(*.cpp);;所有文件(*.*)";
  QString aFileName =
      QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);
  if (!aFileName.isEmpty()) ui->plainTextEdit->appendPlainText(aFileName);
}

void Widget::btnColor_clicked() {
  QPalette pal = ui->plainTextEdit->palette();
  QColor iniColor = pal.color(QPalette::Text);
  QColor color = QColorDialog::getColor(iniColor, this, "选择颜色");
  if (color.isValid()) {
    pal.setColor(QPalette::Text, color);
    ui->plainTextEdit->setPalette(pal);
  }
}

void Widget::btnFont_clicked() {
  QFont inifont = ui->plainTextEdit->font();
  bool ok = false;
  QFont font = QFontDialog::getFont(&ok, inifont);
  if (ok) ui->plainTextEdit->setFont(font);
}

void Widget::btnInputString_clicked() {
  QString dlgTitle = "输入文字对话框";
  QString txtLabel = "请输入文件名";
  QString defaultInput = "花花";
  QLineEdit::EchoMode echo = QLineEdit::Normal;
  bool ok;
  QString text =
      QInputDialog::getText(this, dlgTitle, txtLabel, echo, defaultInput, &ok);
  if (ok && !text.isEmpty()) ui->plainTextEdit->appendPlainText(text);
}

void Widget::btnInputInt_clicked() {
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

void Widget::btnInputDouble_clicked() {
  QString dlgTitle = "输入浮点数对话框";
  QString txtLabel = "输入一个浮点数";
  float defaultDouble = 6.96;
  float minValue = 0, maxValue = 10000;
  int decimals = 2;
  bool ok;
  float inputValue =
      QInputDialog::getDouble(this, dlgTitle, txtLabel, defaultDouble, minValue,
                              maxValue, decimals, &ok);
  if (ok) {
    QString str = QString::asprintf("输入了一个浮点数: %.2f", inputValue);
    ui->plainTextEdit->appendPlainText(str);
  }
}

void Widget::btnInputItem_clicked() {
  QStringList items;
  items << "Great"
        << "Good"
        << "Qualified"
        << "Unqualified";
  QString dlgTitle = "条目选择对话框";
  QString txtLabel = "选择级别";
  int curIndex = 0;
  bool editable = true;
  bool ok = false;
  QString text = QInputDialog::getItem(this, dlgTitle, txtLabel, items,
                                       curIndex, editable, &ok);
  if (ok && !text.isEmpty()) ui->plainTextEdit->appendPlainText(text);
}

void Widget::btnClear_clicked() { ui->plainTextEdit->clear(); }

void Widget::btnMsgInformation_clicked() {
  QString dlgTitle = "Information消息框";
  QString strInfo = "字体大小已设置";
  QMessageBox::information(this, dlgTitle, strInfo, QMessageBox::Ok,
                           QMessageBox::NoButton);
}

void Widget::btnMsgWarning_clicked() {
  QString dlgTitle = "Warning消息框";
  QString strInfo = "文件内容被修改";
  QMessageBox::warning(this, dlgTitle, strInfo);
}

void Widget::btnMsgCritical_clicked() {
  QString dlgTitle = "Critical消息框";
  QString strInfo = "不明用户入侵";
  QMessageBox::critical(this, dlgTitle, strInfo, QMessageBox::Ok,
                        QMessageBox::NoButton);
}

void Widget::btnMsgAbout_clicked() {
  QString dlgTitle = "About消息框";
  QString strInfo = "Qt Demo v1.0 \n侵权必究";
  QMessageBox::about(this, dlgTitle, strInfo);
}

void Widget::btnMsgQuestion_clicked() {
  QString dlgTitle = "Question消息框";
  QString strInfo = "病毒已清除，是否保存? ";
  QMessageBox::StandardButton defaultBtn = QMessageBox::NoButton;
  QMessageBox::StandardButton result;
  result = QMessageBox::question(
      this, dlgTitle, strInfo,
      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, defaultBtn);
  if (result == QMessageBox::Yes)
    ui->plainTextEdit->appendPlainText("Yes");
  else if (result == QMessageBox::No)
    ui->plainTextEdit->appendPlainText("NO");
  else if (result == QMessageBox::Cancel)
    ui->plainTextEdit->appendPlainText("Cancel");
  else
    ui->plainTextEdit->appendPlainText("无选择");
}
