#ifndef QWDIALOGLOCATE_H
#define QWDIALOGLOCATE_H

#include <QDialog>

namespace Ui {
class QWDialogLocate;
}

class QWDialogLocate : public QDialog
{
    Q_OBJECT

public:
    explicit QWDialogLocate(QWidget *parent = 0);
    ~QWDialogLocate();
    void setSpinRange(int row, int col);

public slots:
    void setSpinValue(int row, int col);

private:
    Ui::QWDialogLocate *ui;

    void closeEvent(QCloseEvent* event);
    void showEvent(QShowEvent* event);

signals:
    void changeACellText(int row, int col, QString& text);
    void actLocateEnable(bool en);

private slots:
    void on_btnText_clicked();
};

#endif // QWDIALOGLOCATE_H
