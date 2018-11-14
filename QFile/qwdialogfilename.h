#ifndef QWDIALOGFILENAME_H
#define QWDIALOGFILENAME_H

#include <QDialog>

namespace Ui {
class QWDialogFileName;
}

class QWDialogFileName : public QDialog
{
    Q_OBJECT

public:
    explicit QWDialogFileName(QWidget *parent = 0);
    ~QWDialogFileName();
    void setCopyName(const QString& str);
    QString copyName();

private:
    Ui::QWDialogFileName *ui;
};

#endif // QWDIALOGFILENAME_H
