#include "readfilecontent.h"
#include <QFile>
#include <QTextStream>


QStringList readFileContent(QString aFileName)
{
    QStringList fFileContent;
    QFile aFile(aFileName);
    if(aFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream aStream(&aFile);
//        ui->plainTextEdit->clear();
        while(!aStream.atEnd())
        {
            QString str = aStream.readLine();
//            ui->plainTextEdit->appendPlainText(str);
            fFileContent.append(str);
        }
        aFile.close();
        return fFileContent;
//        this->labCurFile->setText("当前文件: " + aFileName);
//        iniModelFromStringList(fFileContent);
    }
}
