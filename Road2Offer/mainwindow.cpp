#include "mainwindow.h"

#include "ui_mainwindow.h"

void MainWindow::openTable() {
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
#if 0
  connect(theSelection, SIGNAL(currentChanged(QModelIndex, QModelIndex)), this,
          SLOT(on_currentChanged(QModelIndex, QModelIndex)));
  connect(theSelection, SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
          this, SLOT(on_currentRowChanged(QModelIndex, QModelIndex)));
#endif
  ui->tableView->setModel(tabModel);
  ui->tableView->setSelectionModel(theSelection);
  ui->tableView->setColumnHidden(tabModel->fieldIndex("Answer"), true);
}

void MainWindow::replyFinished(QNetworkReply *reply) {
  if (reply->error() != QNetworkReply::NoError) {
    //处理中的错误信息
    qDebug() << "reply error:" << reply->errorString();
  } else {
    //请求方式
    qDebug() << "operation:" << reply->operation();
    //状态码
    qDebug()
        << "status code:"
        << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << "url:" << reply->url();
    // qDebug()<<"raw header:"<<reply->rawHeaderList();

    //获取响应信息
    const QByteArray reply_data = reply->readAll();
    QString str(reply_data);
    qDebug() << "read all:" << str;
    m_oneWords->setText(str);
  }
  reply->deleteLater();
}

void MainWindow::ontimeOut() { GetOneWords(); }

void MainWindow::GetOneWords() {
  QNetworkRequest request;

  QString urlString;
  QUrl url;
  urlString.append("https://v1.hitokoto.cn/?c=d&c=h&c=i&encode=text");
  url.setUrl(urlString);

  QSslConfiguration conf = request.sslConfiguration();
  conf.setPeerVerifyMode(QSslSocket::VerifyNone);
  conf.setProtocol(QSsl::AnyProtocol);
  request.setSslConfiguration(conf);

  request.setUrl(url);

  m_pNetAccMgr->get(request);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  m_pNetAccMgr = new QNetworkAccessManager(this);
  connect(m_pNetAccMgr, &QNetworkAccessManager::finished, this,
          &MainWindow::replyFinished);
  connect(&m_timer, SIGNAL(timeout()), this, SLOT(ontimeOut()));

  m_oneWords = new QLabel("想得到的都拥有，得不到的都释怀。", this);
  // statusBar()->addWidget(m_oneWords); //靠左
  statusBar()->addPermanentWidget(m_oneWords);  //靠右
  m_timer.start(10000);

  // tableview
  ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
  ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->tableView->setAlternatingRowColors(true);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_fileNew_triggered() {}

void MainWindow::on_fileImp_triggered() {
  QString aFile = QFileDialog::getOpenFileName(this, "选择数据库文件", "",
                                               "SQLite数据库(*.db *.db3)");
  if (aFile.isEmpty()) return;

  DB = QSqlDatabase::addDatabase("QSQLITE");
  DB.setDatabaseName(aFile);
  if (!DB.open()) {
    QMessageBox::warning(this, "错误", "打开数据库失败", QMessageBox::Ok,
                         QMessageBox::NoButton);
  }
  openTable();
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index) {
  int curRecNo = index.row();
  QSqlRecord curRec = tabModel->record(curRecNo);
  if (curRec.isNull("Answer")) {
    QMessageBox::information(this, "信息", "尚未为此问题放置答案",
                             QMessageBox::Ok, QMessageBox::NoButton);
  } else {
    QString str = curRec.value("Answer").toString();
    QMessageBox::information(this, "信息", str, QMessageBox::Ok,
                             QMessageBox::NoButton);
  }
}

void MainWindow::on_rbBasic_clicked() {
  tabModel->setFilter("QuestionTypeId=1");
}

void MainWindow::on_rbAdvance_clicked() {
  tabModel->setFilter("QuestionTypeId=2");
}

void MainWindow::on_rbSystem_clicked() {
  tabModel->setFilter("QuestionTypeId=3");
}

void MainWindow::on_rbNetwork_clicked() {
  tabModel->setFilter("QuestionTypeId=4");
}

void MainWindow::on_rbAll_clicked() { tabModel->setFilter(""); }
