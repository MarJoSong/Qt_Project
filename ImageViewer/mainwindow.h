#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QTreeWidgetItem>

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
    void on_actAddFolder_triggered();

    void on_actAddFiles_triggered();

private:
    Ui::MainWindow *ui;
    enum treeItemType{itTopItem = 1001, itGroupItem, itImageItem};
    enum treeColNum{colItem = 0, colItemType = 1};//定义枚举，colItem表示第一列，colItemType表示第二页

    QLabel *LabFileName;
    QPixmap curPixmap;
    float pixRatio;

    void iniTree();
    void addFolderItem(QTreeWidgetItem *parItem, QString dirName);
    QString getFinalFolderName(const QString &fullPathName);
    void addImageItem(QTreeWidgetItem *parItem, QString aFileName);
    void displayImage(QTreeWidgetItem *item);
    void changeItemCaption(QTreeWidgetItem *item);
};

#endif // MAINWINDOW_H
