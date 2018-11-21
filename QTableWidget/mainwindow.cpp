#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitterMain);
    labCellIndex = new QLabel("当前单元格坐标: ", this);
    labCellIndex->setMinimumWidth(200);
    labCellType = new QLabel("当前单元格类型: ", this);
    labCellType->setMinimumWidth(200);
    labStudID = new QLabel("学生ID: ", this);
    labStudID->setMinimumWidth(200);
    ui->statusBar->addWidget(labCellIndex);
    ui->statusBar->addWidget(labCellType);
    ui->statusBar->addWidget(labStudID);
    ui->radioButton->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSetHeader_clicked()
{
    QTableWidgetItem *headerItem;
    QStringList headerText;
    headerText << "姓 名" << "性 别" << "出生日期" << "民 族" << "分数" << "是否党员";
    //ui->tableInfo->setHorizontalHeaderLabels(headerText);
    ui->tableInfo->setColumnCount(headerText.count());
    for(int i = 0; i < ui->tableInfo->columnCount(); i++)
    {
        headerItem = new QTableWidgetItem(headerText.at(i));
        QFont font = headerItem->text();
        //font.setBold(true);
        font.setPointSize(10);
        headerItem->setFont(font);
        //headerItem->setTextColor(Qt::red);
        ui->tableInfo->setHorizontalHeaderItem(i, headerItem);
    }
}

void MainWindow::on_btnIniData_clicked()
{
    QString strName, strSex;
    bool isParty = false;
    QDate birth;
    birth.setDate(1980, 4, 7);
    ui->tableInfo->clearContents();
    int Rows = ui->tableInfo->rowCount();
    for(int i = 0; i < Rows; i++)
    {
        strName = QString::asprintf("学生%d", i);
        if((i % 2) == 0)
            strSex = "男";
        else
            strSex = "女";
        createItemARow(i, strName, strSex, birth, "汉族", isParty, 70);
        birth = birth.addDays(20);
        isParty = !isParty;
    }
    ui->tableInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::createItemARow(int rowNo, QString Name, QString Sex, QDate birth, QString Nation, bool isPM, int score)
{
    QTableWidgetItem *item;
    QString str;
    uint StudID = 201605000;

    item = new QTableWidgetItem(Name, MainWindow::ctName);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    StudID += rowNo;
    item->setData(Qt::UserRole, QVariant(StudID));
    item->setCheckState(Qt::Checked);
    ui->tableInfo->setItem(rowNo, MainWindow::colName, item);


    QIcon icon;
    if(Sex == "男")
        icon.addFile(":/images/icons/boy.ico");
    else
        icon.addFile(":/images/icons/girl.ico");
    item = new QTableWidgetItem(Sex, MainWindow::ctSex);
    item->setIcon(icon);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableInfo->setItem(rowNo, MainWindow::colSex, item);

    str = birth.toString("yyyy-MM-dd");
    item = new QTableWidgetItem(str, MainWindow::ctBirth);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableInfo->setItem(rowNo, MainWindow::colBirth, item);

    item = new QTableWidgetItem(Nation, MainWindow::ctNation);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableInfo->setItem(rowNo, MainWindow::colNation, item);

    item = new QTableWidgetItem("党员", MainWindow::ctPartyM);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    if(isPM)
        item->setCheckState(Qt::Checked);
    else
        item->setCheckState(Qt::Unchecked);
    item->setBackgroundColor(Qt::yellow);
    ui->tableInfo->setItem(rowNo, MainWindow::colPartyM, item);

    str.setNum(score);
    item = new QTableWidgetItem(str, MainWindow::ctScore);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableInfo->setItem(rowNo, MainWindow::colScore, item);
}

void MainWindow::on_tableInfo_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    QTableWidgetItem * item = ui->tableInfo->item(currentRow, currentColumn);
    if(item == NULL)
        return;
    labCellIndex->setText(QString::asprintf("当前单元格坐标: %d 行, %d 列", currentRow, currentColumn));
    int cellType = item->type();
    labCellType->setText(QString::asprintf("当前单元格类型: %d", cellType));
    item = ui->tableInfo->item(currentRow, MainWindow::colName);
    int ID = item->data(Qt::UserRole).toInt();
    labStudID->setText(QString::asprintf("学生ID: %d", ID));
}

void MainWindow::on_btnInsertRow_clicked()
{
    int curRow = ui->tableInfo->currentRow();
    ui->tableInfo->insertRow(curRow);
    createItemARow(curRow, "新学生", "男",
          QDate::fromString("1990-1-1","yyyy-M-d"), "苗族", true, 70);
}

void MainWindow::on_btnAppendRow_clicked()
{
    int curRow = ui->tableInfo->rowCount();
    ui->tableInfo->insertRow(curRow);
    createItemARow(curRow, "新学生", "女"
                                  "",
          QDate::fromString("2000-12-25","yyyy-M-d"), "汉族", true, 70);
}

void MainWindow::on_btnDeleteRow_clicked()
{
    int curRow = ui->tableInfo->currentRow();
    ui->tableInfo->removeRow(curRow);

}

void MainWindow::on_btnAdRowHgt_clicked()
{
    ui->tableInfo->resizeRowsToContents();
}

void MainWindow::on_btnAdColWgh_clicked()
{
    ui->tableInfo->resizeColumnsToContents();
}

void MainWindow::on_ckbTabEditable_clicked(bool checked)
{
    if(checked)
        ui->tableInfo->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    else
        ui->tableInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_ckbHeadRowHid_clicked(bool checked)
{
    ui->tableInfo->horizontalHeader()->setVisible(!checked);
}

void MainWindow::on_ckbHeadColHid_clicked(bool checked)
{
    ui->tableInfo->verticalHeader()->setVisible(!checked);
}

void MainWindow::on_ckbAlterRowColor_clicked(bool checked)
{
    ui->tableInfo->setAlternatingRowColors(checked);
}

void MainWindow::on_rBtnColSelect_clicked()
{
    if(ui->rBtnColSelect->isChecked())
        ui->radioButton->setChecked(true);
    else
        ui->tableInfo->setSelectionBehavior(QAbstractItemView::SelectColumns);
}

void MainWindow::on_rBtnRowSelect_clicked()
{
    if(ui->rBtnRowSelect->isChecked())
        ui->radioButton->setChecked(true);
    else
        ui->tableInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
}
