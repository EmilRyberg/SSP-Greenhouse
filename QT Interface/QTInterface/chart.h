#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>
#include <QtCore/QTimer>
#include <QDateTimeAxis>
#include <QString>
#include <QDateTime>

QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class Chart: public QChart
{
    Q_OBJECT
public:
    Chart(int yAxisMin, int yAxisMax, bool twoLines = true, QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    void Append(QDateTime time, double y, double y2);
    void AppendSingle(QDateTime time, double y);
    void SetLabels(QString first, QString second = "");
    virtual ~Chart();

private:
    QSplineSeries *m_series;
    QSplineSeries *n_series;
    QDateTimeAxis *m_axis;
    const double kScrollStep = 10.0;
    int yAxisMin;
    int yAxisMax;
    int iterations = 0;
    bool useTwoLines;
};

#endif /* CHART_H */
