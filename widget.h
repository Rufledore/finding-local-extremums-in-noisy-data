#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <qchart.h>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QChart>
#include <chartview.h>

enum e_extremum {MIN, MAX, NOT};

namespace Ui {
class Widget;
}
class Widget : public QWidget
{
Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QChart *chart;
    QLineSeries *m_pDataSeries;
    QScatterSeries *m_pMaximums;
    QScatterSeries *m_pMinimums;
    ChartView *m_pPlot;
    QList<QPointF> *m_pData;


    void drawLineFunction();
    void setUpInitialChart();
    e_extremum isItExtremum();
    void findLocalExtremums(const QList<QPointF>& data, QList<QPointF>& maximums, QList<QPointF>& minimums);
    void findGlobalExtremums();
    void extremumsFilter();

    QPointF leaveTheExtremum(e_extremum extremumType, QMap<double, double>& points);

private slots:
    void calculateAndPlot();
};

#endif // WIDGET_H
