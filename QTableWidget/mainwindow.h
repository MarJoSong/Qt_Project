#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnSetHeader_clicked();

    void on_btnIniData_clicked();

    void on_tableInfo_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_btnInsertRow_clicked();

    void on_btnAppendRow_clicked();

    void on_btnDeleteRow_clicked();

    void on_btnAdRowHgt_clicked();

    void on_btnAdColWgh_clicked();

    void on_ckbTabEditable_clicked(bool checked);

    void on_ckbHeadRowHid_clicked(bool checked);

    void on_ckbHeadColHid_clicked(bool checked);

    void on_ckbAlterRowColor_clicked(bool checked);

    void on_rBtnColSelect_clicked();

    void on_rBtnRowSelect_clicked();

private:
    Ui::MainWindow *ui;
    enum CellType{ctName = 1000, ctSex, ctBirth, ctNation, ctPartyM, ctScore};
    enum FieldColNum{colName = 0, colSex, colBirth, colNation, colScore, colPartyM};
    QLabel *labCellIndex;
    QLabel *labCellType;
    QLabel *labStudID;
    void createItemARow(int rowNo, QString Name, QString Sex, QDate birth, QString Nation,bool isPM, int score);


};

#endif // MAINWINDOW_H
