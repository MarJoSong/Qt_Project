#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>

void MainWindow::createChart()
{
    QChart* chart = new QChart();
    chart->setTitle("简单函数曲线");
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);

    QLineSeries* series0 = new QLineSeries();
    QLineSeries* series1 = new QLineSeries();
    series0->setName("Sin 曲线");
    series1->setName("Cos 曲线");

    QPen pen;
    pen.setStyle(Qt::DotLine);
    pen.setWidth(2);
    pen.setColor(Qt::red);
    series0->setPen(pen);
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::blue);
    series1->setPen(pen);
    chart->addSeries(series0);
    chart->addSeries(series1);

    QValueAxis* axisX = new QValueAxis;
    curAxis = axisX;
    axisX->setRange(0, 10);
    axisX->setLabelFormat("%.1f");
    axisX->setTickCount(11);
    axisX->setMinorTickCount(4);
    axisX->setTitleText("time(secs)");
    QValueAxis* axisY = new QValueAxis;
    axisY->setRange(-2, 2);
    axisY->setTitleText("Value");
    axisY->setTickCount(5);
    axisY->setLabelFormat("%.2f");
    axisY->setMinorTickCount(4);

    chart->setAxisX(axisX, series0);
    chart->setAxisY(axisY, series0);
    chart->setAxisX(axisX, series1);
    chart->setAxisY(axisY, series1);
}

void MainWindow::prepareData()
{
    QLineSeries* series0 = (QLineSeries*)ui->chartView->chart()->series().at(0);
    QLineSeries* series1 = (QLineSeries*)ui->chartView->chart()->series().at(1);
    series0->clear();
    series1->clear();
    qsrand(QTime::currentTime().second());
    qreal t=0, y1, y2, intv=0.1;
    qreal rd;
    int cnt = 100;
    for(int i=0; i< cnt; i++)
    {
        rd = (qrand() % 10) -5;
        y1 = qSin(t) + rd/50;
        series0->append(t, y1);
        rd = (qrand() % 10) -5;
        y2 = qCos(t) + rd/50;
        series1->append(t, y2);
        t += intv;
    }
}

void MainWindow::updateFromChart()
{
    QChart* aChart = ui->chartView->chart();
    ui->editTitle->setText(aChart->title());
    QMargins mg = aChart->margins();
    ui->spinMarginLeft->setValue(mg.left());
    ui->spinMarginRight->setValue(mg.right());
    ui->spinMarginTop->setValue(mg.top());
    ui->spinMarginBottom->setValue(mg.bottom());
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createChart();
    prepareData();
    updateFromChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSetTitle_clicked()
{
    ui->chartView->chart()->setTitle(ui->editTitle->text());
}

void MainWindow::on_btnSetTilteFont_clicked()
{
    QFont font = ui->chartView->chart()->legend()->font();
    bool ok = false;
    font = QFontDialog::getFont(&ok, font);
    if(ok)
        ui->chartView->chart()->legend()->setFont(font);
}
