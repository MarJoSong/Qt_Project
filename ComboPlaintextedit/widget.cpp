#include "widget.h"
#include "ui_widget.h"
#include <QTextBlock>
#include <QMenu>

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

void Widget::on_pushButton_3_clicked()
{
//    QIcon icon;
//    icon.addFile(":/images/icons/city.ico");
//    ui->comboBox->clear();
//    for(int i = 0;i < 20; i++)
//        ui->comboBox->addItem(icon, QString::asprintf("Item %d", i));
    QIcon icon;
    icon.addFile(":/images/icons/city2.ico");
    ui->comboBox->clear();
    QStringList strList;
    strList<<"北京"<<"上海"<<"天津"<<"河北省"<<"山东省"<<"陕西省";
    for(int i = 0; i < 6; i++)
        ui->comboBox->addItem(icon,strList[i]);
}

void Widget::on_pushButton_5_clicked()
{
    QMap<QString, int> City_Zone;
    City_Zone.insert("北京", 10);
    City_Zone.insert("上海", 21);
    City_Zone.insert("天津", 22);
    City_Zone.insert("大连",411);
    City_Zone.insert("锦州",416);
    City_Zone.insert("徐州",516);
    City_Zone.insert("福州",591);
    City_Zone.insert("青岛",532);
    ui->comboBox_2->clear();
    foreach (const QString &str, City_Zone.keys())
        ui->comboBox_2->addItem(str, City_Zone.value(str));
}

void Widget::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->plainTextEdit->appendPlainText(arg1);
}

void Widget::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    QString zone = ui->comboBox_2->currentData().toString();
    ui->plainTextEdit->appendPlainText(arg1+":区号="+zone);
}

void Widget::on_pushButton_clicked()
{
    QTextDocument * doc = ui->plainTextEdit->document();
    int cnt = doc->blockCount();
    QIcon icon(":/images/icon/city.ico");
    ui->comboBox->clear();
    for(int i = 0;i < cnt; i++)
    {
        QTextBlock textline = doc->findBlockByNumber(i);
        QString str = textline.text();
        ui->comboBox->addItem(icon, str);
    }
}

void Widget::on_plainTextEdit_customContextMenuRequested(const QPoint &pos)
{
    QMenu * menu = ui->plainTextEdit->createStandardContextMenu();
    menu->exec(pos);
}

void Widget::on_pushButton_2_clicked()
{
    ui->plainTextEdit->clear();
}
