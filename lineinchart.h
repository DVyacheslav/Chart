#ifndef LINEINCHART_H
#define LINEINCHART_H
#include <QtCharts/QChartGlobal>
#include <QtWidgets/QGraphicsItem>
#include <QtGui/QFont>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE
QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE
QT_CHARTS_USE_NAMESPACE

class LineInChart : public QGraphicsItem
{
public:
   LineInChart(QChart *chart);
   void updateGeometry();
   QRectF boundingRect() const;
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
   void setPosMouse(QPoint point);
protected:
   void mousePressEvent(QGraphicsSceneMouseEvent *event);
   void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
private:
   QChart *chart_;
   QPoint mousePosition_;
};

#endif // LINEINCHART_H
