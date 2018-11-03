#include "qformtable.h"
#include "ui_qformtable.h"


QFormTable::QFormTable(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QFormTable)
{
    ui->setupUi(this);
    theModel = new QStandardItemModel(6, 4, this);
    theSelection = new QItemSelectionModel(theModel);
//    connect(theSelection, SIGNAL(currentChanged(QModelIndex,QModelIndex)),
//            this, SLOT(on_currentChanged(QModelIndex,QModelIndex)));
    ui->tableView->setModel(theModel);
    ui->tableView->setSelectionModel(theSelection);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
}

QFormTable::~QFormTable()
{
    delete ui;
    //QMessageBox::information(this, "消息", "QFormTab对象被删除和释放");
}

void QFormTable::on_actSetRowCol_triggered()
{
    QWDialogSize* dlgTableSize = new QWDialogSize(this); //添加了this
    Qt::WindowFlags flags = dlgTableSize->windowFlags();
    dlgTableSize->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    dlgTableSize->setRowColumn(theModel->rowCount(), theModel->columnCount());
    int ret = dlgTableSize->exec();
    if(ret == QDialog::Accepted)
    {
        int cols = dlgTableSize->colCount();
        theModel->setColumnCount(cols);
        int rows = dlgTableSize->rowCount();
        theModel->setRowCount(rows);
    }
    delete dlgTableSize;
}

void QFormTable::on_actHeader_triggered()
{
    if(dlgSetHeader == NULL)
        dlgSetHeader = new QWDialogHeader(this); //不加this,会怎样
    if(dlgSetHeader->headerList().count() != theModel->columnCount())
    {
        QStringList strList;
        for(int i=0; i<theModel->columnCount(); i++)
            strList.append(theModel->headerData(i, Qt::Horizontal,
                        Qt::DisplayRole).toString());
        dlgSetHeader->setHeaders(strList);
    }

    int ret = dlgSetHeader->exec();
    if(ret == QDialog::Accepted)
    {
        QStringList strList = dlgSetHeader->headerList();
        theModel->setHorizontalHeaderLabels(strList);
    }
}

void QFormTable::on_actLocate_triggered()
{
    dlgLocate = new QWDialogLocate(this);
    dlgLocate->setAttribute(Qt::WA_DeleteOnClose);
    Qt::WindowFlags flags = dlgLocate->windowFlags();
    dlgLocate->setWindowFlags(flags | Qt::WindowStaysOnTopHint);

    dlgLocate->setSpinRange(theModel->rowCount(), theModel->columnCount());
    QModelIndex curIndex = theSelection->currentIndex();
    if(curIndex.isValid())
        dlgLocate->setSpinValue(curIndex.row(), curIndex.column());
    connect(dlgLocate, SIGNAL(changeACellText(int,int,QString&)),
            this, SLOT(setCellText(int, int, QString&)));
    connect(dlgLocate, SIGNAL(actLocateEnable(bool)),
            this, SLOT(setActLocateEnable(bool)));
    connect(this, SIGNAL(cellIndexChanged(int,int)),
            dlgLocate, SLOT(setSpinValue(int,int)));
    dlgLocate->show();
}

void QFormTable::setCellText(int row, int col, QString &text)
{
    QModelIndex index = theModel->index(row-1, col-1);
    theSelection->clearSelection();
    theSelection->setCurrentIndex(index, QItemSelectionModel::Select);
    theModel->setData(index, text, Qt::DisplayRole);
}

void QFormTable::setActLocateEnable(bool en)
{
    ui->actLocate->setEnabled(en);
}

void QFormTable::on_tableView_clicked(const QModelIndex &index)
{
    emit cellIndexChanged(index.row(), index.column());
}
