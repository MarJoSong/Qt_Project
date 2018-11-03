#ifndef QWDIALOGHEADER_H
#define QWDIALOGHEADER_H

#include <QDialog>
#include <QStringListModel>
#include <QStringList>

namespace Ui {
class QWDialogHeader;
}

class QWDialogHeader : public QDialog
{
    Q_OBJECT

public:
    explicit QWDialogHeader(QWidget *parent = 0);
    ~QWDialogHeader();

    void setHeaders(QStringList& headers);
    QStringList headerList();

private:
    Ui::QWDialogHeader *ui;

    QStringListModel *model;
};

#endif // QWDIALOGHEADER_H
