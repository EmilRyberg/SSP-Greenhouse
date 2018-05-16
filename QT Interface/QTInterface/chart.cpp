#include "chart.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>
#include <algorithm>

Chart::Chart(int yAxisMin, int yAxisMax, bool twoLines, int xAxisMax, QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_series(0),
    n_series(0),
    m_axis(new QValueAxis),
    yAxisMin(yAxisMin),
    yAxisMax(yAxisMax),
    xAxisMax(xAxisMax),
    useTwoLines(twoLines)
{
    m_series = new QSplineSeries(this);

    QPen green(Qt::green);
    QPen red(Qt::red);
    green.setWidth(3);
    red.setWidth(3);
    m_series->setPen(green);
    addSeries(m_series);

    if(useTwoLines)
    {
        n_series = new QSplineSeries(this);
        n_series->setPen(red);
        addSeries(n_series);
    }

    createDefaultAxes();
    setAxisX(m_axis, m_series);
    if(useTwoLines) n_series->attachAxis(m_axis);
    m_axis->setTickCount(5);
    axisX()->setRange(0, xAxisMax);
    axisY()->setRange(yAxisMin, yAxisMax);
}

Chart::~Chart()
{

}

void Chart::Append(double time, double y, double y2)
{
    qreal scrollX = (plotArea().width() / (double)xAxisMax) * kScrollStep;
    m_series->append(time, y);
    n_series->append(time, y2);

    double maxYValue = std::max(y, y2);
    double minYValue = std::min(y, y2);
    if(maxYValue > yAxisMax)
    {
        yAxisMax = maxYValue + (maxYValue - yAxisMax) * 0.5;
        axisY()->setRange(yAxisMin, yAxisMax);
    }

    if(minYValue < yAxisMin)
    {
        yAxisMin = minYValue - (minYValue - yAxisMin) * 0.5;
        axisY()->setRange(yAxisMin, yAxisMax);
    }

    if(time > (double)xAxisMax)
    {
        scroll(scrollX, 0);
    }
}

void Chart::AppendSingle(double time, double y)
{
    qreal scrollX = (plotArea().width() / (double)xAxisMax) * kScrollStep;
    m_series->append(time, y);

    double maxYValue = y;
    double minYValue = y;
    if(maxYValue > yAxisMax)
    {
        yAxisMax = maxYValue + (maxYValue - yAxisMax) * 0.5;
        axisY()->setRange(yAxisMin, yAxisMax);
    }

    if(minYValue < yAxisMin)
    {
        yAxisMin = minYValue - (minYValue - yAxisMin) * 0.5;
        axisY()->setRange(yAxisMin, yAxisMax);
    }

    if(time > (double)xAxisMax)
    {
        scroll(scrollX, 0);
    }
}

void Chart::SetLabels(QString first, QString second)
{
    m_series->setName(first);
    if(second != "")
    {
        n_series->setName(second);
    }
}
