#ifndef QDIALOGLOGIN_H
#define QDIALOGLOGIN_H

#include <QDialog>
#include <QPoint>

namespace Ui {
class QDialogLogin;
}

class QDialogLogin : public QDialog
{
    Q_OBJECT
private:
    bool m_moving = false;
    QPoint m_lastPos;
    QString m_user = "user";
    QString m_pswd = "12345";
    int m_tryCount = 0;
    void readSettings();
    void writeSettings();
    QString encrypt(const QString& str);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMoveEvent *event);

public:
    explicit QDialogLogin(QWidget *parent = 0);
    ~QDialogLogin();

private slots:
    void on_OK_clicked();

private:
    Ui::QDialogLogin *ui;
};

#endif // QDIALOGLOGIN_H
