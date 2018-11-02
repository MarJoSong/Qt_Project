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

private slots:
    void on_btnSetText_clicked();

public slots:
    void setSpinValue(int rowNo, int colNo);

private:
    Ui::QWDialogLocate *ui;

    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);

signals:
    void changeCellText(int, int, QString&);
    void changeActionEnable(bool);
};

#endif // QWDIALOGLOCATE_H
