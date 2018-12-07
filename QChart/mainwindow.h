#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QLineSeries*    curSeries;
    QValueAxis*     curAxis;
    void    createChart();
    void    prepareData();
    void    updateFromChart();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnSetTitle_clicked();

    void on_btnSetTilteFont_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
