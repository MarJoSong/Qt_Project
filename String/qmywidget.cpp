#include "qmywidget.h"
#include "ui_qmywidget.h"

qMYWidget::qMYWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::qMYWidget)
{
    ui->setupUi(this);
}

qMYWidget::~qMYWidget()
{
    delete ui;
}

void qMYWidget::seeOK(bool l)
{
    if(l == true)
        ui->result->setText("True");
    else
        ui->result->setText("False");
}

void qMYWidget::on_btnAppend_clicked()
{
    QString str1 = ui->str1->text();
    QString str2 = ui->str2->text();
    str1.append(str2);
    ui->result->setText(str1);
}

void qMYWidget::on_btnPrepend_clicked()
{
    QString str1 = ui->str1->text();
    QString str2 = ui->str2->text();
    str1.prepend(str2);
    ui->result->setText(str1);
}

void qMYWidget::on_btnToUpper_clicked()
{
    QString str1 = ui->str1->text();
    QString str2 = ui->str2->text();
    ui->str1->setText(str1.toUpper());
    ui->str2->setText(str2.toUpper());
}

void qMYWidget::on_toLower_clicked()
{
    QString str1 = ui->str1->text();
    QString str2 = ui->str2->text();
    ui->str1->setText(str1.toLower());
    ui->str2->setText(str2.toLower());
}

void qMYWidget::on_btnCount_clicked()
{
    int val = ui->str1->text().count();
    ui->result->setText(QString::number(val));
}

void qMYWidget::on_btnSize_clicked()
{
    int val = ui->str2->text().size();
    ui->result->setText(QString::number(val));
}

void qMYWidget::on_btnTrimmed_clicked()
{
    ui->result->setText(ui->str2->text().trimmed());
}

void qMYWidget::on_btnSimplified_clicked()
{
    ui->result->setText(ui->str1->text().simplified());
}

void qMYWidget::on_btnIndexOf_clicked()
{
    int val = ui->str1->text().indexOf(ui->str2->text());
    ui->result->setText(QString::number(val));
}

void qMYWidget::on_bnLastIndexof_clicked()
{
    int val = ui->str1->text().lastIndexOf(ui->str2->text());
    ui->result->setText(QString::number(val));
}

void qMYWidget::on_btnIsNull_clicked()
{
    bool ok = ui->str1->text().isNull();
    seeOK(ok);
}

void qMYWidget::on_btnIsEmpty_clicked()
{
    bool ok = ui->str2->text().isEmpty();
    seeOK(ok);
}

void qMYWidget::on_btnContains_clicked()
{
    bool ok = ui->str1->text().contains(ui->str2->text(), Qt::CaseInsensitive);
    //CaseInsensitive不区分大小写
    seeOK(ok);
}

void qMYWidget::on_endsWith_clicked()
{
    bool ok = ui->str1->text().endsWith(ui->str2->text(), Qt::CaseInsensitive);
    seeOK(ok);
}

void qMYWidget::on_btnStartsWith_clicked()
{
    bool ok = ui->str1->text().startsWith(ui->str2->text(), Qt::CaseSensitive);
    //CaseSenstitive区分大小写
    seeOK(ok);
}

void qMYWidget::on_btnLeft_clicked()
{
//    QString str = ui->str1->text();
//    int N = ui->result->text().toInt();
//    str = str.left(N);
//    ui->result->setText(str);
    ui->result->setText(ui->str1->text().left(ui->result->text().toInt()));
}

void qMYWidget::on_btnRight_clicked()
{
    QString str = ui->str1->text();
    int N = ui->result->text().toInt() + 1;
    str = str.right(str.size() - N);
    ui->result->setText(str);
}

void qMYWidget::on_btnSection_clicked()
{

}
