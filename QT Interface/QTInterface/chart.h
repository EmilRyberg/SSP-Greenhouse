#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>
#include <QtCore/QTimer>

QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class Chart: public QChart
{
    Q_OBJECT
public:
    Chart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    void Append(double time, double y, double y2);
    virtual ~Chart();

private:
    QSplineSeries *m_series;
    QSplineSeries *n_series;
    QStringList m_titles;
    QValueAxis *m_axis;
    double lastY;
    double lastY2;
};

#endif /* CHART_H */
