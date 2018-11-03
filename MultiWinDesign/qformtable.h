#ifndef QFORMTABLE_H
#define QFORMTABLE_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QModelIndex>
#include "qwdialogsize.h"
#include "qwdialogheader.h"
#include "qwdialoglocate.h"

namespace Ui {
class QFormTable;
}

class QFormTable : public QMainWindow
{
    Q_OBJECT

public:
    explicit QFormTable(QWidget *parent = 0);
    ~QFormTable();

private:
    Ui::QFormTable* ui;
    QStandardItemModel* theModel;
    QItemSelectionModel* theSelection;
    QWDialogHeader* dlgSetHeader = NULL;
    QWDialogLocate* dlgLocate = NULL;

private slots:
    void on_actSetRowCol_triggered();

    void on_actHeader_triggered();
    void on_actLocate_triggered();

    void setCellText(int row, int col, QString& text);
    void setActLocateEnable(bool en);
    void on_tableView_clicked(const QModelIndex &index);

signals:
    void cellIndexChanged(int rowNo, int colNo);
};

#endif // QFORMTABLE_H
