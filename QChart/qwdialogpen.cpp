#include "qwdialogpen.h"
#include "ui_qwdialogpen.h"
#include <QPen>

QWDialogPen::QWDialogPen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogPen)
{
    ui->setupUi(this);
}

QWDialogPen::~QWDialogPen()
{
    delete ui;
}

void QWDialogPen::setPen(QPen pen)
{
    m_pen = pen;
    ui->spinWidth->setValue(pen.width());
    int i = static_cast<int>(pen.style());
    ui->comboPenStyle->setCurrentIndex(i);
    QColor color = pen.color();
    ui->btnColor->setAutoFillBackground(true);
    QString str = QString::asprintf("background-color: rgb(%d, %d, %d);", color.red(), color.green(), color.blue());
    ui->btnColor->setStyleSheet(str);
}

QPen QWDialogPen::getPen()
{
    m_pen.setStyle(Qt::PenStyle(ui->comboPenStyle->currentIndex()));
    m_pen.setWidth(ui->spinWidth->value());
    QColor color = ui->btnColor->palette().color(QPalette::Button);
    m_pen.setColor(color);
    return m_pen;
}

QPen QWDialogPen::getPen(QPen iniPen, bool &ok)
{
    QWDialogPen *dlg = new QWDialogPen;
    dlg->setPen(iniPen);
    QPen pen;
    int ret = dlg->exec();
    if(ret == QDialog::Accepted)
    {
        pen = dlg->getPen();
        ok = true;
    }
    else
    {
        pen = iniPen;
        ok = false;
    }
    delete dlg;
    return pen;
}

void QWDialogPen::on_btnColor_clicked()
{

}
