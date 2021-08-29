#include "mainwindow.h"

#include "ui_mainwindow.h"

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
  urlString.append("https://v1.hitokoto.cn/?c=d&c=h&encode=text");
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
  ui->tabWidget->tabsClosable();

  m_pNetAccMgr = new QNetworkAccessManager(this);
  connect(m_pNetAccMgr, &QNetworkAccessManager::finished, this,
          &MainWindow::replyFinished);
  connect(&m_timer, SIGNAL(timeout()), this, SLOT(ontimeOut()));
  connect(ui->fileImp, SIGNAL(triggered()), this, SLOT(fileImp_triggered()));

  m_oneWords = new QLabel("想得到的都拥有，得不到的都释怀。", this);
  // statusBar()->addWidget(m_oneWords); //靠左
  statusBar()->addPermanentWidget(m_oneWords);  //靠右
  m_timer.start(10000);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::fileImp_triggered() {
  QFormTable *formTable = new QFormTable(this);
  formTable->setAttribute(Qt::WA_DeleteOnClose);
  int cur = ui->tabWidget->addTab(
      formTable, QString::asprintf("FAQ %d", ui->tabWidget->count()));
  ui->tabWidget->setCurrentIndex(cur);
  ui->tabWidget->setVisible(true);
}
