#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFile>
#include <QFileSystemWatcher>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void showBtnInfo(QObject*);

private slots:
    void on_openFile_clicked();

    void on_clearInfo_clicked();

    void on_applicationDirPath_clicked();

    void on_applicationFilePath_clicked();

    void on_applicationName_clicked();

    void on_setOrganizationName_clicked();

    void on_organizationName_clicked();

    void on_exit_clicked();

    void on_Copy_clicked();

    void on_Rename_clicked();

    void on_Exist_clicked();

    void on_Remove_clicked();

    void on_fileCopy_clicked();

    void on_fileRename_clicked();

    void on_fileRemove_clicked();

    void on_fileExist_clicked();

    void on_size_clicked();
    bool fileExist(const QFile& aFile);

    void on_setFile_clicked();

    void on_fileName_clicked();

    void on_filePath_clicked();

    void on_Path_clicked();

    void on_baseName_5_clicked();

    void on_baseName_2_clicked();

    void on_size_2_clicked();

    void on_baseName_clicked();

    void on_suffix_clicked();

    void on_isDir_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_createdTime_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_tempPath_clicked();

    void on_rootPath_clicked();

    void on_homePath_clicked();

    void on_currentPath_clicked();

    void on_setCurrentPath_clicked();

    void on_entryList_clicked();

    void on_pushButton_12_clicked();

    void on_directoryChanged(const QString path);

    void on_pushButton_13_clicked();

    void on_fileChanged(const QString path);
    void on_openDir_clicked();

private:
    Ui::Widget *ui;

    QFileSystemWatcher fileWatcher;
};

#endif // WIDGET_H
