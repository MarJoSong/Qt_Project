#include "qformdoc.h"
#include "ui_qformdoc.h"
#include <QMessageBox>
#include <QToolBar>
#include <QVBoxLayout>

QFormDoc::QFormDoc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QFormDoc)
{
    ui->setupUi(this);
    QToolBar* locToolBar = new QToolBar("文档", this);
    locToolBar->addAction(ui->actOpen);
    locToolBar->addAction(ui->actFont);
    locToolBar->addSeparator();
    locToolBar->addAction(ui->actCut);
    locToolBar->addAction(ui->actCopy);
    locToolBar->addAction(ui->actPaste);
    locToolBar->addAction(ui->actUndo);
    locToolBar->addAction(ui->actRedo);
    locToolBar->addSeparator();
    locToolBar->addAction(ui->actClose);
    locToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QVBoxLayout* LayOut = new QVBoxLayout();
    LayOut->addWidget(locToolBar);
    LayOut->addWidget(ui->plainTextEdit);
    LayOut->setContentsMargins(2, 2, 2, 2);
    LayOut->setSpacing(2);
    this->setLayout(LayOut);
}

QFormDoc::~QFormDoc()
{
    delete ui;
    //QMessageBox::information(this, "消息", "QFormDoc对象被删除和释放");
}
