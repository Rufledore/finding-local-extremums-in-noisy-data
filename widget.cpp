#include "widget.h"
#include "ui_widget.h"
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include "chartview.h"
#include <QDebug>
#include <QValueAxis>
#include <math.h>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    chart(new QChart),
    m_pDataSeries(new QLineSeries),
    m_pMaximums(new QScatterSeries),
    m_pMinimums(new QScatterSeries),
    m_pPlot(new ChartView(chart)),
    m_pData(new QList<QPointF>())
{
    ui->setupUi(this);

    setUpInitialChart();
    drawLineFunction();

    findGlobalExtremums();

//    connect(plot, &ChartView::clicked, this, &Widget::calculateAndPlot);
}

Widget::~Widget()
{
    delete ui;
    delete chart;
    delete m_pDataSeries;
    delete m_pPlot;
    delete m_pMaximums;
    delete m_pMinimums;
}

/*
    Drawing line line function with set bias an gain.
*/
void Widget::drawLineFunction()
{
    QVector<double> xAxis;
    for (double step = 1; step < 7; step += 0.02) {
        xAxis.push_back(step);
    }

    //Creating sin signal with noise
    for (int i = 0; i < xAxis.length(); i++) {
        double random = ((static_cast<double>(rand())/RAND_MAX) - 0.5);
//        double random = rand();
        qDebug() << random;
        double multiplier = xAxis.length() - i;
        double currenValue = (sin(xAxis[i] * 4) * multiplier) + ((random - 0.5) * 30);
        m_pData->push_back(QPointF(xAxis[i], currenValue));
    }


    m_pDataSeries->append(*m_pData);     //Appending the List of points in the series
    m_pDataSeries->setVisible(true);

    chart->addSeries(m_pDataSeries);   //Adding series to the chart
    m_pDataSeries->attachAxis(chart->axisX());
    m_pDataSeries->attachAxis(chart->axisY());
}

void Widget::setUpInitialChart()
{


    QValueAxis *axisX = new QValueAxis;
    axisX->setTickCount(11);
    axisX->setRange(0, 10);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTickCount(11);
    axisY->setRange(-300, 300);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    ui->chartLayout->addWidget(m_pPlot);
}

e_extremum Widget::isItExtremum()
{
    QList<QPointF> data = m_pDataSeries->points();
    for (int i = 1; i < data.length() - 1; ++i) {
        QPointF prev_point = data[i-1];
        QPointF curr_point = data[i];
        QPointF next_point = data[i+1];


    return MAX;
    }
}

void Widget::findLocalExtremums(const QList<QPointF>& data, QList<QPointF> &maximums, QList<QPointF> &minimums)
{
    for (int i = 1; i < data.length() - 1; ++i) {
        QPointF prev_point = data[i-1];
        QPointF curr_point = data[i];
        QPointF next_point = data[i+1];

        if (curr_point.y() > prev_point.y() && curr_point.y() > next_point.y()) {
            maximums.append(curr_point);
        } else if (curr_point.y() < prev_point.y() && curr_point.y() < next_point.y()) {
//            minimums.append(curr_point);
            minimums.append(curr_point);
        }
    }
}

void Widget::findGlobalExtremums()
{
    QList<QPointF> maximums{};
    QList<QPointF> minimums{};
    QList<QPointF> maxMaximums{};
    QList<QPointF> maxMinimums{};
    QList<QPointF> minMaximums{};
    QList<QPointF> minMinimums{};
    QList<QPointF> data = m_pDataSeries->points();

    findLocalExtremums(data, maximums, minimums);

    findLocalExtremums(maximums, maxMaximums, maxMinimums);
    findLocalExtremums(minimums, minMaximums, minMinimums);

    m_pMaximums->append(maxMaximums);
    m_pMinimums->append(minMinimums);

    QScatterSeries *max = new QScatterSeries();
    QScatterSeries *min = new QScatterSeries();

//    max->append(maximums);
//    min->append(minimums);

//    chart->addSeries(max);
//    max->attachAxis(chart->axisX());
//    max->attachAxis(chart->axisY());
//    chart->addSeries(min);
//    min->attachAxis(chart->axisX());
//    min->attachAxis(chart->axisY());

    chart->addSeries(m_pMaximums);
    m_pMaximums->attachAxis(chart->axisX());
    m_pMaximums->attachAxis(chart->axisY());
    chart->addSeries(m_pMinimums);
    m_pMinimums->attachAxis(chart->axisX());
    m_pMinimums->attachAxis(chart->axisY());
    m_pMaximums->setMarkerSize(7);
    m_pMinimums->setMarkerSize(7);

}

void Widget::extremumsFilter()
{
    QList<QPointF> maxData = m_pMaximums->points();
    QList<QPointF> minData = m_pMinimums->points();
    QList<QPointF>::iterator currentMax = maxData.begin();
    QList<QPointF>::iterator currentMin = minData.begin();

    while (currentMax != maxData.end() && currentMin != minData.end()) {

    }




}

QPointF Widget::leaveTheExtremum(e_extremum extremumType, QMap<double, double> &points)
{
//    This function returns the point with biggest Y if we have MAXes given or smallest Y if we have MINs given

//    Using QHash(y, x) i automatically sorts with respect to Y.

    if (extremumType == MAX) {
        return QPointF(points.end().value(), points.end().key());
    } else {
        return QPointF(points.begin().value(), points.begin().key());
    }

}

void Widget::calculateAndPlot()
{

    drawLineFunction();

}
