#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitter);

    model =new QStandardItemModel(2, FixedColumnCount, this);//创建数据模型
    selection = new QItemSelectionModel(model);//创建数据选择模型,需要传递数据模型做参数
    connect(selection, SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(on_currentChanged(QModelIndex,QModelIndex)));
    ui->tableView->setModel(model);//设置数据模型
    ui->tableView->setSelectionModel(selection);//设置选择模型
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    labCurFile = new QLabel("当前文件",this);
//    labCurFile->setMinimumWidth(180);
    labCurPos = new QLabel("当前单元格",this);
//    labCurPos->setMinimumWidth(150);
    labCurText = new QLabel("单元格内容",this);
//    labCurText->setMinimumWidth(180);
    ui->statusBar->addWidget(labCurFile,1);
    ui->statusBar->addWidget(labCurPos,1);
    ui->statusBar->addWidget(labCurText,1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iniModelFromStringList(QStringList &aFileContent)
{
    int rowCount = aFileContent.count();
    model->setRowCount(rowCount - 1);
    QString header = aFileContent.at(0);
    QStringList headerList = header.split(QRegExp("\\s+"),QString::SkipEmptyParts);
    model->setHorizontalHeaderLabels(headerList);

    QStandardItem *aItem;
    QStringList tmpList;
    int j;
    for(int i=1; i<rowCount; i++)
    {
        QString aLineText = aFileContent.at(i);
        tmpList = aLineText.split(QRegExp("\\s+"),QString::SkipEmptyParts);
        for(j=0; j<FixedColumnCount-1; j++)
        {
            aItem = new QStandardItem(tmpList.at(j));
            model->setItem(i-1, j, aItem);
        }
        aItem = new QStandardItem(headerList.at(j));
        aItem->setCheckable(true);
        if(tmpList.at(j) == "0")
            aItem->setCheckState(Qt::Unchecked);
        else
            aItem->setCheckState(Qt::Checked);
        model->setItem(i-1, j, aItem);
    }
}

void MainWindow::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous)
    if(current.isValid())
    {
        labCurPos->setText(QString::asprintf("当前单元格: %d行, %d列",current.row(),current.column()));
        QStandardItem *aItem = model->itemFromIndex(current);
        this->labCurText->setText("单元格内容: " + aItem->text());
        QFont font  = aItem->font();
        ui->actFontBold->setChecked(font.bold());
    }
}



void MainWindow::on_actOpen_triggered()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString aFileName = QFileDialog::getOpenFileName(this, "打开一个文件",
            curPath, "井数据文件(*.txt);;所有文件(*.*)");
    if(aFileName.isEmpty())
        return;

    QStringList fFileContent;
    QFile aFile(aFileName);
    if(aFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream aStream(&aFile);
        ui->plainTextEdit->clear();
        while(!aStream.atEnd())
        {
            QString str = aStream.readLine();
            ui->plainTextEdit->appendPlainText(str);
            fFileContent.append(str);
        }
        aFile.close();
        this->labCurFile->setText("当前文件: " + aFileName);
        iniModelFromStringList(fFileContent);
    }

}

void MainWindow::on_actAppend_triggered()
{
    QList<QStandardItem*> aItemList;
    QStandardItem *aItem;
    for(int i=0; i < FixedColumnCount-1; i++)
    {
        aItem = new QStandardItem("0");
        aItemList << aItem;
    }
    QString str = model->headerData(model->columnCount()-1, Qt::Horizontal,
                                    Qt::DisplayRole).toString();
    aItem = new QStandardItem(str);
    aItem->setCheckable(true);
    aItemList << aItem;

    model->insertRow(model->rowCount(), aItemList);
    QModelIndex curIndex = model->index(model->rowCount()-1, 0);
    selection->clearSelection();
    selection->setCurrentIndex(curIndex, QItemSelectionModel::Select);
}

void MainWindow::on_actInsert_triggered()
{
    QList<QStandardItem*> aItemList;
    QStandardItem *aItem;
    for(int i=0; i < FixedColumnCount-1; i++)
    {
        aItem = new QStandardItem("0");
        aItemList << aItem;
    }
    QString str = model->headerData(model->columnCount()-1, Qt::Horizontal,
                                    Qt::DisplayRole).toString();
    aItem = new QStandardItem(str);
    aItem->setCheckable(true);
    aItemList << aItem;

    QModelIndex index = ui->tableView->currentIndex();
    model->insertRow(index.row(), aItemList);
    QModelIndex curIndex = model->index(model->rowCount()-1, 0);
    selection->clearSelection();
    selection->setCurrentIndex(curIndex, QItemSelectionModel::Select);
}

void MainWindow::on_actDelete_triggered()
{
    QModelIndex curIndex = ui->tableView->currentIndex();
    if(curIndex.row()==model->rowCount()-1)
        model->removeRow(curIndex.row());
    else
    {
        model->removeRow(curIndex.row());
        selection->setCurrentIndex(curIndex, QItemSelectionModel::Select);
    }

}

void MainWindow::on_actAlignLeft_triggered()
{
    if(!selection->hasSelection())
        return;
    QModelIndexList selectedIndex = selection->selectedIndexes();
    for(int i=0; i<selectedIndex.count(); i++)
    {
        QModelIndex aIndex = selectedIndex.at(i);
        QStandardItem *aItem = model->itemFromIndex(aIndex);
        aItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    }
}

void MainWindow::on_actAlignCenter_triggered()
{
    if(!selection->hasSelection())
        return;
    QModelIndexList selectedIndex = selection->selectedIndexes();
    for(int i=0; i<selectedIndex.count(); i++)
    {
        QModelIndex aIndex = selectedIndex.at(i);
        QStandardItem *aItem = model->itemFromIndex(aIndex);
        aItem->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::on_actAlignRight_triggered()
{
    if(!selection->hasSelection())
        return;
    QModelIndexList selectedIndex = selection->selectedIndexes();
    for(int i=0; i<selectedIndex.count(); i++)
    {
        QModelIndex aIndex = selectedIndex.at(i);
        QStandardItem *aItem = model->itemFromIndex(aIndex);
        aItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    }
}

void MainWindow::on_actFontBold_triggered(bool checked)
{
    if(!selection->hasSelection())
        return;
    QModelIndexList selectedIndex = selection->selectedIndexes();
    for(int i=0; i<selectedIndex.count(); i++)
    {
        QModelIndex aIndex = selectedIndex.at(i);
        QStandardItem *aItem = model->itemFromIndex(aIndex);
        QFont font = aItem->font();
        font.setBold(checked);
        aItem->setFont(font);
    }
}



void MainWindow::on_actSave_triggered()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString aFileName = QFileDialog::getOpenFileName(this, "打开一个文件",
            curPath, "井数据文件(*.txt);;所有文件(*.*)");
    if(aFileName.isEmpty())
        return;
    QFile aFile(aFileName);
    if(!(aFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate)))
        return;

    QTextStream *aStream(&aFile);
    QStandardItem *aItem;
    int i,j;
    QString str;
    ui->plainTextEdit->clear();

    for(int i=0; i<model->columnCount(); i++)
    {
        aItem = model->horizontalHeaderItem(i);
        str = str + aItem->text() + "\t\t";
    }

    aStream << str << "\n";
    ui->plainTextEdit->appendPlainText(str);

    for(i=0; i<model->rowCount(); i++)
    {
        str = "";
        for(j=0; j<model->columnCount()-1; j++)
        {
            aItem = model->item(i, j);
            str = str + aItem->text() + QString::asprintf("\t\t");
        }
        aItem = model->item(i, j);
        if(aItem->checkState()==Qt::Checked)
            str = str + "1";
        else
            str = str + "0";
        ui->plainTextEdit->appendPlainText(str);
        aStream << str << "\n";
    }
}

void MainWindow::on_actiShow_triggered()
{

}
