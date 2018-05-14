#include "chart.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_series(0),
    m_axis(new QValueAxis),
    m_step(0),
    m_x(10),
    m_y(10)
{
    m_series = new QSplineSeries(this);
    QPen green(Qt::red);
    green.setWidth(3);
    m_series->setPen(green);

    addSeries(m_series);
    createDefaultAxes();
    setAxisX(m_axis, m_series);
    m_axis->setTickCount(5);
    axisX()->setRange(0, 100);
    axisY()->setRange(-20, 60);
}

Chart::~Chart()
{

}

void Chart::Append(double x, double y)
{
    //qreal x = plotArea().width() / y;
    //qreal y = (m_axis->max() - m_axis->min()) / m_axis->tickCount();
    //m_x += y;
    //m_y = QRandomGenerator::global()->bounded(5) - 2.5;
    m_series->append(x, y);
    //scroll(x, 0);
}
