#include "qdialoglogin.h"
#include "ui_qdialoglogin.h"
#include <QSettings>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QMouseEvent>

void QDialogLogin::readSettings()
{
    QString organization = "WWB-Qt";
    QString appName = "samp6_5";
    QSettings settings(organization, appName);
    bool saved = settings.value("saved", false).toBool();
    m_user = settings.value("UserName", "user").toString();
    QString defaultPSWD = encrypt("12345");
    m_pswd = settings.value("PSWD", defaultPSWD).toString();
    if(saved)
        ui->editName->setText(m_user);
    ui->chkSaveName->setChecked(saved);
}

void QDialogLogin::writeSettings()
{
    QSettings settings("WWB-Qt", "samp6_5");
    settings.value("UserName", m_user);
    settings.value("PSWD", m_pswd);
    settings.value("saved", ui->chkSaveName->isChecked());
}

QString QDialogLogin::encrypt(const QString &str)
{
    QByteArray btArray;
    btArray.append(str);
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(btArray);
    QByteArray resultArray = hash.result();
    QString md5 = resultArray.toHex();
    return md5;
}

void QDialogLogin::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_moving = true;
        m_lastPos = event->globalPos() - pos();
    }
    return QDialog::mousePressEvent(event);
}

void QDialogLogin::mouseMoveEvent(QMouseEvent *event)
{
    if(m_moving && (event->buttons() && Qt::LeftButton) && (event->globalPos()-m_lastPos).manhattanLength()>QApplication::startDragDistance())
    {
        move(event->globalPos()-m_lastPos);
        m_lastPos = event->globalPos() - pos();
    }
    return QDialog::mouseMoveEvent(event);
}

void QDialogLogin::mouseReleaseEvent(QMoveEvent *event)
{
    m_moving = false;
}

QDialogLogin::QDialogLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDialogLogin)
{
    ui->setupUi(this);
    ui->editPSWD->setEchoMode(QLineEdit::Password);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::SplashScreen);
    readSettings();
}

QDialogLogin::~QDialogLogin()
{
    delete ui;
}

void QDialogLogin::on_OK_clicked()
{
    QString user = ui->editName->text();
    QString pswd = ui->editPSWD->text();
    QString encryptPSWD = encrypt(pswd);
    if((user == m_user) && (encryptPSWD == m_pswd))
    {
        writeSettings();
        this->accept();
    }
    else
    {
        m_tryCount++;
        if(m_tryCount > 3)
        {
            QMessageBox::critical(this, "错误", "输入次数过多，强制退出!");
            this->reject();
        }
        else
            QMessageBox::warning(this, "错误提示", "用户名或密码错误!");
    }
}
