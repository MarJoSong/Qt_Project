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
