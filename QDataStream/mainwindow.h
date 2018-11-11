#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qwcomboboxdelegate.h"
#include "qwintspindelegate.h"
#include "qwfloatspindelegate.h"
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QLabel* LabCellPos;
    QLabel* LabCellText;
    QWIntSpinDelegate intSpinDelegate;
    QWFloatSpinDelegate floatSpinDelegate;
    QWComboBoxDelegate comboBoxDetegate;
    QStandardItemModel* theModel;
    QItemSelectionModel* theSelection;
    void resetTable(int aRowCount);
    bool saveDataAsStream(QString& aFileName);
    bool openDataAsStream(QString& aFileName);
    bool saveBinaryFile(QString& aFileName);
    bool openBinaryFile(QString& aFileName);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actSave_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
