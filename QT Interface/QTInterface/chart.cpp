#include "chart.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>
#include <iostream>

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_series(0),
    n_series(0),
    lastY(0),
    lastY2(0),
    m_axis(new QValueAxis)
{
    m_series = new QSplineSeries(this);
    n_series = new QSplineSeries(this);
    QPen green(Qt::green);
    QPen red(Qt::red);
    green.setWidth(3);
    red.setWidth(3);
    m_series->setPen(green);
    m_series->setName("Inside");
    n_series->setPen(red);
    n_series->setName("Outside");

    addSeries(m_series);
    addSeries(n_series);
    createDefaultAxes();
    setAxisX(m_axis, m_series);
    n_series->attachAxis(m_axis);
    m_axis->setTickCount(5);
    axisX()->setRange(0, 40);
    axisY()->setRange(0, 40);
}

Chart::~Chart()
{

}

void Chart::Append(double time, double y, double y2)
{
    //qreal x = plotArea().width() / y;
    //qreal y = (m_axis->max() - m_axis->min()) / m_axis->tickCount();
    //m_x += y;
    //m_y = QRandomGenerator::global()->bounded(5) - 2.5;
    qreal scrollX = (plotArea().width() / 40.0) * 10.0; //50 * 10
    qreal scrollY = 0;
    if(y2 > 40.0 && y2 >= y)
    {
        scrollY = (plotArea().height() / 40.0) * (y2 - lastY2);
    }
    else if(y > 40.0)
    {
        scrollY = (plotArea().height() / 40.0) * (y - lastY);
    }
    std::cout << "Max: " << m_axis->max() << ", scrollX: " << scrollX << std::endl;
    m_series->append(time, y);
    n_series->append(time, y2);
    if(time > 40.0)
    {
        scroll(scrollX, scrollY);
    }
    else if(scrollY != 0)
    {
        scroll(0, scrollY);
    }
    lastY = y;
    lastY2 = y2;
}
