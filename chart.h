#ifndef CHART_H
#define CHART_H
#include <QtCharts/QChart>
#include <QObject>
QT_CHARTS_USE_NAMESPACE

class Chart : public QChart
{
public:
   Chart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
};

#endif // CHART_H
