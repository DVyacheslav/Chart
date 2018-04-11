#include "lineinchart.h"
#include <QtGui/QPainter>
#include <QtGui/QFontMetrics>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QtGui/QMouseEvent>
#include <QtCharts/QChart>
#include <QDebug>
LineInChart::LineInChart(QChart *chart) :
   QGraphicsItem(chart),
   chart_(chart)
{

}


QRectF LineInChart::boundingRect() const
{
   QRectF rect;
   rect.setLeft(0);
   rect.setRight(mousePosition_.x()+10);
   rect.setTop(mousePosition_.y()-10);
   rect.setBottom(chart_->size().toSize().height());
   return rect;
}

void LineInChart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   Q_UNUSED(option)
   Q_UNUSED(widget)
   QPainterPath path;
   QPointF point1, point2;
   point1.setX(0+45);
   point1.setY(mousePosition_.y());
   point2.setX(mousePosition_.x());
   point2.setY(chart_->size().height()-32);
   qDebug () << point2 << "point";
   path.moveTo(point1);
   path.lineTo(mousePosition_);
   path.moveTo(mousePosition_);
   path.lineTo(point2);
   painter->setPen(QPen(Qt::red, 3, Qt::SolidLine));
   painter->drawPath(path);
   path = path.simplified();
}

void LineInChart::setPosMouse(QPoint point)
{
   mousePosition_ = point;
}

void LineInChart::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   event->setAccepted(true);
}

void LineInChart::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
   if (event->buttons() & Qt::LeftButton){
      setPos(mapToParent(event->pos() - event->buttonDownPos(Qt::LeftButton)));
      event->setAccepted(true);
   }
   else
   {
      event->setAccepted(false);
   }
}


void LineInChart::updateGeometry()
{
   prepareGeometryChange();
}
