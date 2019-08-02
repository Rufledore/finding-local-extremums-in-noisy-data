#include "chartview.h"
#include <QtGui/QMouseEvent>
#include <QDebug>


ChartView::ChartView(QChart *chart, QWidget *parent) :
    QChartView(chart, parent),
    mouseEvent(nullptr),
    currentChart(chart),
    m_isTouching(false)
{
    setRubberBand(QChartView::RectangleRubberBand);
}
/*
bool ChartView::viewportEvent(QEvent *event)
{
    if (event->type() == QEvent::TouchBegin) {
        // By default touch events are converted to mouse events. So
        // after this event we will get a mouse event also but we want
        // to handle touch events as gestures only. So we need this safeguard
        // to block mouse events that are actually generated from touch.
        m_isTouching = true;

        // Turn off animations when handling gestures they
        // will only slow us down.
        chart()->setAnimationOptions(QChart::NoAnimation);
    }
    return QChartView::viewportEvent(event);
}
*/

void ChartView::mousePressEvent(QMouseEvent *event)
{
    mouseEvent = event;

    clicked();

}

QPointF ChartView::getMouseCoordinates ()
{
    QPoint point = mouseEvent->pos();

    //Convert from pixels to coordinates' units
    auto scene = this->mapToScene(point);
//    qDebug() << scene;
    auto item = currentChart->mapFromScene(scene);
//    qDebug() << item;
    auto value = currentChart->mapToValue(item);
    qDebug() << value;
    return value;
}

ChartView::~ChartView()
{

}
