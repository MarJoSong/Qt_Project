﻿#include "qformtable.h"

#include "ui_qformtable.h"

bool QFormTable::openDatabase() {
  QString aFile = QFileDialog::getOpenFileName(this, "选择数据库文件", "",
                                               "SQLite数据库(*.db *.db3)");
  if (aFile.isEmpty()) return false;

  DB = QSqlDatabase::addDatabase("QSQLITE");
  DB.setDatabaseName(aFile);
  if (!DB.open()) {
    QMessageBox::warning(this, "错误", "打开数据库失败", QMessageBox::Ok,
                         QMessageBox::NoButton);
    return false;
  }

  return true;
}

void QFormTable::openTable() {
  tabModel = new QSqlTableModel(this, DB);
  tabModel->setTable("FAQ");
  tabModel->setSort(tabModel->fieldIndex("Id"), Qt::AscendingOrder);
  tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

  if (!(tabModel->select())) {
    QMessageBox::critical(
        this, "错误信息",
        "打开数据表错误,错误信息\n" + (tabModel->lastError().text()),
        QMessageBox::Ok, QMessageBox::NoButton);
    return;
  }

  tabModel->setHeaderData(tabModel->fieldIndex("FAQId"), Qt::Horizontal,
                          "编号");
  tabModel->setHeaderData(tabModel->fieldIndex("FAQName"), Qt::Horizontal,
                          "题目");
  tabModel->setHeaderData(tabModel->fieldIndex("QuestionTypeId"),
                          Qt::Horizontal, "类别");
  tabModel->setHeaderData(tabModel->fieldIndex("CreateTime"), Qt::Horizontal,
                          "创建时间");
  tabModel->setHeaderData(tabModel->fieldIndex("Answer"), Qt::Horizontal,
                          "答案");

  theSelection = new QItemSelectionModel(tabModel);

  ui->tableView->setModel(tabModel);
  ui->tableView->setSelectionModel(theSelection);
  ui->tableView->setColumnHidden(tabModel->fieldIndex("Answer"), true);

  ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
  ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->tableView->setAlternatingRowColors(true);
  ui->tableView->resizeColumnsToContents();
}

QFormTable::QFormTable(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::QFormTable) {
  ui->setupUi(this);
  ui->preview->setContextMenuPolicy(Qt::NoContextMenu);

  connect(ui->rbAll, SIGNAL(clicked()), this, SLOT(rbAll_clicked()));
  connect(ui->rbBasic, SIGNAL(clicked()), this, SLOT(rbBasic_clicked()));
  connect(ui->rbAdvance, SIGNAL(clicked()), this, SLOT(rbAdvance_clicked()));
  connect(ui->rbSystem, SIGNAL(clicked()), this, SLOT(rbSystem_clicked()));
  connect(ui->rbNetwork, SIGNAL(clicked()), this, SLOT(rbNetwork_clicked()));
  connect(ui->rbDataStru, SIGNAL(clicked()), this, SLOT(rbDataStru_clicked()));
  connect(ui->rbAlgorithm, SIGNAL(clicked()), this,
          SLOT(rbAlgorithm_clicked()));
  connect(ui->rbDatabase, SIGNAL(clicked()), this, SLOT(rbDatabase_clicked()));
  connect(ui->rbDesignmode, SIGNAL(clicked()), this,
          SLOT(rbDesignmode_clicked()));
  connect(ui->rbOS, SIGNAL(clicked()), this, SLOT(rbOS_clicked()));
  connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex &index)), this,
          SLOT(tableView_doubleClicked(const QModelIndex &index)));

  if (false == openDatabase()) return;

  openTable();
}

void QFormTable::rbAll_clicked() { tabModel->setFilter(""); }

void QFormTable::rbBasic_clicked() { tabModel->setFilter("QuestionTypeId=1"); }

void QFormTable::rbAdvance_clicked() {
  tabModel->setFilter("QuestionTypeId=2");
}

void QFormTable::rbSystem_clicked() { tabModel->setFilter("QuestionTypeId=3"); }

void QFormTable::rbNetwork_clicked() {
  tabModel->setFilter("QuestionTypeId=4");
}

void QFormTable::rbDataStru_clicked() {
  tabModel->setFilter("QuestionTypeId=5");
}

void QFormTable::rbAlgorithm_clicked() {
  tabModel->setFilter("QuestionTypeId=6");
}

void QFormTable::rbDatabase_clicked() {
  tabModel->setFilter("QuestionTypeId=7");
}

void QFormTable::rbDesignmode_clicked() {
  tabModel->setFilter("QuestionTypeId=8");
}

void QFormTable::rbOS_clicked() { tabModel->setFilter("QuestionTypeId=9"); }

QFormTable::~QFormTable() { delete ui; }

void QFormTable::on_tableView_clicked(const QModelIndex &index) {
  int curRecNo = index.row();
  QSqlRecord curRec = tabModel->record(curRecNo);
  if (curRec.isNull("Answer")) {
    QMessageBox::information(this, "信息", "尚未为此问题放置答案",
                             QMessageBox::Ok, QMessageBox::NoButton);
  } else {
    ui->preview->setContextMenuPolicy(Qt::NoContextMenu);

    QString str = curRec.value("Answer").toString();
    m_content.setText(str);

    PreviewPage *page = new PreviewPage(this);
    ui->preview->setPage(page);

    QWebChannel *channel = new QWebChannel(this);
    channel->registerObject(QStringLiteral("content"), &m_content);
    page->setWebChannel(channel);

    ui->preview->setUrl(QUrl("qrc:/index.html"));
    m_content.setText(curRec.value("Answer").toString());
  }
}
