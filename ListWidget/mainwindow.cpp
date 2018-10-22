#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitter);
    ui->toolBox_2->setMinimumWidth(150);
    ui->toolBox_2->setMaximumWidth(250);
    ui->toolBox_2->setMinimumHeight(250);
    setActionsForButton();
    createSelectPopupMenu();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actListIni_triggered()
{
    QListWidgetItem *aItem;
    QIcon aIcon;
    aIcon.addFile(":/images/icons/check2.ico");
    bool chk = ui->chkBoxEditable->isChecked();

    ui->listWidget->clear();
    for(int i = 0; i < 10; i++)
    {
        QString str = QString::asprintf("Item %d",i);
        aItem = new QListWidgetItem;
        aItem->setText(str);
        aItem->setIcon(aIcon);
        aItem->setCheckState(Qt::Checked);
        if(chk)
            aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable
            | Qt::ItemIsEditable | Qt::ItemIsEnabled);
        else
            aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable
            | Qt::ItemIsEnabled);
        ui->listWidget->addItem(aItem);
    }
}

void MainWindow::on_actListInsert_triggered()
{
    QListWidgetItem *aItem = new QListWidgetItem("新增项");
    QIcon aIcon;
    aIcon.addFile(":/images/icons/check2.ico");
    aItem->setIcon(aIcon);
    aItem->setCheckState(Qt::Unchecked);
    bool chk = ui->chkBoxEditable->isChecked();
    if(chk)
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable
        | Qt::ItemIsEditable | Qt::ItemIsEnabled);
    else
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable
        | Qt::ItemIsEnabled);
    ui->listWidget->insertItem(ui->listWidget->currentRow(), aItem);
}

void MainWindow::on_actListClear_triggered()
{
    ui->listWidget->clear();
}

void MainWindow::on_actSelAll_triggered()
{
    int cnt = ui->listWidget->count();
    for(int i = 0; i< cnt; i++)
    {
        QListWidgetItem *aItem = ui->listWidget->item(i);
        aItem->setCheckState(Qt::Checked);
    }
}

void MainWindow::on_actSelInvs_triggered()
{
    int cnt = ui->listWidget->count();
    for(int i = 0; i< cnt; i++)
    {
        QListWidgetItem *aItem = ui->listWidget->item(i);
        if(aItem->checkState() == Qt::Checked)
            aItem->setCheckState(Qt::Unchecked);
        else
            aItem->setCheckState(Qt::Checked);
    }
}

void MainWindow::on_actSelNone_triggered()
{
    int cnt = ui->listWidget->count();
    for(int i = 0; i< cnt; i++)
    {
        QListWidgetItem *aItem = ui->listWidget->item(i);
        aItem->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    QString str;
    if(current != NULL)
    {
        if(previous == NULL)
            str = "当前项：" + current->text();
        else
            str = "前一项：" + previous->text() + "; 当前项：" + current->text();
        ui->editCutItemText->setText(str);
    }
}

void MainWindow::on_actListAppend_triggered()
{
    QListWidgetItem *aItem = new QListWidgetItem("新增项");
    QIcon aIcon;
    aIcon.addFile(":/images/icons/check2.ico");
    aItem->setIcon(aIcon);
    ui->listWidget->addItem(aItem);
}

void MainWindow::on_actListDelete_triggered()
{
    int row = ui->listWidget->currentRow();
    QListWidgetItem *aItem = ui->listWidget->takeItem(row);
    delete aItem;
}

void MainWindow::setActionsForButton()
{
    ui->tBtnListIni->setDefaultAction(ui->actListIni);
    ui->tBtnListClear->setDefaultAction(ui->actListClear);
    ui->tBtnListInsert->setDefaultAction(ui->actListInsert);
    ui->tBtnListAppend->setDefaultAction(ui->actListAppend);
    ui->tBtnListDelete->setDefaultAction(ui->actListDelete);

    ui->tBtnSelAll->setDefaultAction(ui->actSelAll);
    ui->tBtnSelNone->setDefaultAction(ui->actSelNone);
    ui->tBtnSelInvs->setDefaultAction(ui->actSelInvs);
}

void MainWindow::createSelectPopupMenu()
{
    QMenu *menuSelect = new QMenu(this);
    menuSelect->addAction(ui->actSelAll);
    menuSelect->addAction(ui->actSelNone);
    menuSelect->addAction(ui->actSelInvs);
    ui->tBtnSelectItem->setPopupMode(QToolButton::MenuButtonPopup);
    ui->tBtnSelectItem->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->tBtnSelectItem->setDefaultAction(ui->actSelPopMenu);
    ui->tBtnSelectItem->setMenu(menuSelect);

    QToolButton *aBtn = new QToolButton(this);
    aBtn->setPopupMode(QToolButton::InstantPopup);
    aBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    aBtn->setDefaultAction(ui->actSelPopMenu);
    aBtn->setMenu(menuSelect);
    ui->mainToolBar->addWidget(aBtn);

    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actExit);
}

void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu *menuList = new QMenu(this);
    menuList->addAction(ui->actListIni);
    menuList->addAction(ui->actListAppend);
    menuList->addAction(ui->actListInsert);
    menuList->addAction(ui->actListDelete);
    menuList->addSeparator();
    menuList->addAction(ui->actSelAll);
    menuList->addAction(ui->actSelInvs);
    menuList->addAction(ui->actSelNone);
    menuList->exec(QCursor::pos());
    delete menuList;
}
