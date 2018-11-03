#ifndef QWDIALOGSIZE_H
#define QWDIALOGSIZE_H

#include <QDialog>

namespace Ui {
class QWDialogSize;
}

class QWDialogSize : public QDialog
{
    Q_OBJECT

public:
    explicit QWDialogSize(QWidget *parent = 0);
    ~QWDialogSize();
    int rowCount();
    int colCount();
    void setRowColumn(int row, int col);

private:
    Ui::QWDialogSize *ui;
};

#endif // QWDIALOGSIZE_H
