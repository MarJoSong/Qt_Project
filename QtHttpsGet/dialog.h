#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

class Dialog : public QDialog {
  Q_OBJECT
 private slots:
  void replyFinished(QNetworkReply *reply);

 public:
  Dialog(QWidget *parent = nullptr);
  ~Dialog();

 private:
  QNetworkAccessManager *m_pNetAccMgr;
};
#endif  // DIALOG_H
