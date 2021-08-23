#include "dialog.h"

void Dialog::replyFinished(QNetworkReply *reply) {
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
    qDebug() << "read all:" << QString(reply_data);
  }
  reply->deleteLater();
}

Dialog::Dialog(QWidget *parent) : QDialog(parent) {
  m_pNetAccMgr = new QNetworkAccessManager(this);
  connect(m_pNetAccMgr, &QNetworkAccessManager::finished, this,
          &Dialog::replyFinished);

  QNetworkRequest request;

  QString urlString;
  QUrl url;
  urlString.append("https://v1.hitokoto.cn/?c=f&encode=text");
  url.setUrl(urlString);

  QSslConfiguration conf = request.sslConfiguration();
  conf.setPeerVerifyMode(QSslSocket::VerifyNone);
  conf.setProtocol(QSsl::AnyProtocol);
  request.setSslConfiguration(conf);

  request.setUrl(url);

  m_pNetAccMgr->get(request);
}

Dialog::~Dialog() {}
