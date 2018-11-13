#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qwcomboboxdelegate.h"
#include "qwintspindelegate.h"
#include "qwfloatspindelegate.h"
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QLabel>
#include "qwdialogheaders.h"

#define     FixedColumnCount    6

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
    QWDialogHeaders* dlgSetHeader = NULL;

    bool saveDataAsStream(QString& aFileName);
    bool openDataAsStream(QString& aFileName);
    bool saveBinaryFile(QString& aFileName);
    bool openBinaryFile(QString& aFileName);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actSave_triggered();

    void on_actOpen_triggered();

    void on_currentChanged(const QModelIndex& current, const QModelIndex& previous);

    void on_actNew_triggered();

    void on_actSetSize_triggered();

    void on_actSetHeader_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
