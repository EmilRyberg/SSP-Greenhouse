#include "chart.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>
#include <QDateTime>
#include <algorithm>

Chart::Chart(int yAxisMin, int yAxisMax, bool twoLines, QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_series(0),
    n_series(0),
    m_axis(new QDateTimeAxis),
    yAxisMin(yAxisMin),
    yAxisMax(yAxisMax),
    useTwoLines(twoLines)
{
    m_series = new QSplineSeries(this);

    QPen green(Qt::green);
    QPen red(Qt::red);
    green.setWidth(3);
    red.setWidth(3);
    m_series->setPen(green);

    if(useTwoLines)
    {
        n_series = new QSplineSeries(this);
        n_series->setPen(red);
        addSeries(n_series);
    }
    addSeries(m_series);
    createDefaultAxes();
    m_axis->setTickCount(5);
    m_axis->setFormat("dd/MM hh:mm:ss");
    setAxisX(m_axis, m_series);
    if(useTwoLines) n_series->attachAxis(m_axis);
    axisX()->setRange(QDateTime::currentDateTime(), QDateTime::currentDateTime().addSecs(50));
    axisY()->setRange(yAxisMin, yAxisMax);
}

Chart::~Chart()
{

}

void Chart::Append(QDateTime time, double y, double y2)
{
    iterations++;
    qreal scrollX = (plotArea().width() / m_axis->tickCount());
    m_series->append(time.toMSecsSinceEpoch(), y);
    n_series->append(time.toMSecsSinceEpoch(), y2);

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

    if(iterations > m_axis->tickCount())
    {
        scroll(scrollX, 0);
    }
}

void Chart::AppendSingle(QDateTime time, double y)
{
    iterations++;
    qreal scrollX = (plotArea().width() / m_axis->tickCount());
    m_series->append(time.toMSecsSinceEpoch(), y);

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

    if(iterations > m_axis->tickCount())
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
