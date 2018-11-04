#ifndef QFORMDOC_H
#define QFORMDOC_H

#include <QWidget>

namespace Ui {
class QFormDoc;
}

class QFormDoc : public QWidget
{
    Q_OBJECT

private:
    QString mCurrentFile;
    bool    mFileOpened = false;

public:
    explicit QFormDoc(QWidget *parent = 0);
    ~QFormDoc();
    void    loadFromFile(QString& aFileName);
    QString currentFileName();
    bool    isFileOpened();
    void    setEditFont();
    void    textCut();
    void    textCopy();
    void    textPaste();
    void    fileSave(QString aFileName);
private:
    Ui::QFormDoc *ui;
};

#endif // QFORMDOC_H
