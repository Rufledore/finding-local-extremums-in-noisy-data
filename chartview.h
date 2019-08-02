#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts/QChartView>
#include <QtWidgets/QRubberBand>
#include <QMouseEvent>
#include <QObject>


QT_CHARTS_USE_NAMESPACE


class ChartView: public QChartView
{
    Q_OBJECT
public:
    ChartView(QChart *chart, QWidget *parent = 0);
    ~ChartView();

    QPointF getMouseCoordinates();
    void mousePressEvent(QMouseEvent *event);

signals:
    void clicked();

protected:
//    bool viewportEvent(QEvent *event);

private:
    QMouseEvent *mouseEvent;
    QChart *currentChart;
    bool m_isTouching;


};

#endif // CHARTVIEW_H
