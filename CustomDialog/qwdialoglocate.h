#ifndef QWDIALOGLOCATE_H
#define QWDIALOGLOCATE_H

#include <QDialog>
#include <QStringListModel>

namespace Ui {
class QWDialogLocate;
}

class QWDialogLocate : public QDialog
{
    Q_OBJECT

public:
    explicit QWDialogLocate(QWidget *parent = 0);
    ~QWDialogLocate();

    void setSpinRange(int rowCount, int ColCount);
    void setSpinValue(int rowNo, int colNo);

private slots:

    void on_btnSetText_clicked();

private:
    Ui::QWDialogLocate *ui;

    void closeEvent(QCloseEvent *event);
};

#endif // QWDIALOGLOCATE_H
