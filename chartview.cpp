#include "chartview.h"
#include <QDebug>
ChartView::ChartView(QWidget *parent) :
   QGraphicsView(new QGraphicsScene, parent)
{
   scene()->addItem(&chart_);
   chart_.setAcceptHoverEvents(true);
   chart_.setMargins(QMargins(30, 30, 30, 30));
   button_.resize(BUTTON_WIDTH, BUTTON_HEIGHT);
   button_.hide();
   scene()->addWidget(&button_);
   axisX.setMin(0);
   axisX.setMax(10);
}

void ChartView::resizeEvent(QResizeEvent *event)
{

   if (scene())
   {
      scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
      chart_.resize(event->size());
      resizeButtonsAxisX();
   }
   QGraphicsView::resizeEvent(event);
}

void ChartView::buttonSetPosition(int x)
{
   // QRect g = button_.geometry();
}

void ChartView::addButtonAxisX(std::list<QPointF> listPoint)
{

}

void ChartView::resizeButtonsAxisX()
{
   if (buttonsAxisX_.size() > 0){
      std::list<std::unique_ptr<QPushButton>>::iterator begin = buttonsAxisX_.begin();
      for (const auto &p : buffAxisXPoint_)
      {
         QPoint positionFromPoint = chart_.mapToPosition(p).toPoint();
         QSize sizeButton = begin->get()->size();
         qDebug() << positionFromPoint << "pos";
         int buttonWidth = (chart_.size().width() / (buffAxisXPoint_.size()));
         sizeButton.setWidth(buttonWidth - BUTTONS_MARGIN);
         begin->get()->setText(QString::number(p.x()));
         begin->get()->resize(sizeButton);
         int positionX = positionFromPoint.x() - begin->get()->size().width() / 2;
         int positionY = chart_.size().height() - begin->get()->height();
         begin->get()->move(QPoint(positionX, positionY));
         begin++;
      }
   }
}

void ChartView::highlightButton(const int positonX)
{
   for (const auto &p : buttonsAxisX_)
   {
      int positonButton = p.get()->pos().x() + p.get()->width() / 2;
      if ( positonButton == positonX )
      {
         QPalette pal = p->palette();
         pal.setColor(QPalette::Button, QColor(Qt::blue));
         p->setAutoFillBackground(true);
         p->setPalette(pal);
         p->update();
      }
   }
}

void ChartView::createButtonAxisX(int count)
{
   for (int i = 0; i < count; i++)
   {
      auto buf = new QPushButton;
      buttonsAxisX_.push_back(std::unique_ptr<QPushButton>(buf));
      buf->resize(BUTTON_WIDTH, BUTTON_HEIGHT);
      scene()->addWidget(buf);
   }
   resizeButtonsAxisX();
   //qDebug() << pos << "pos";
   //QPoint pos = chart_.mapToPosition(QPointF(position,1)).toPoint();
   //buttonAxisX_->move(QPoint(pos.x() - button_.size().width() / 2,chart_.size().height() - BUTTON_HEIGHT));
}

void ChartView::addSeries(QXYSeries *Series)
{
   chart_.addSeries(Series);
   connect(Series, &QXYSeries::clicked, this, &ChartView::seriesClick);
   connect(Series, &QXYSeries::hovered, this, &ChartView::seriesHover);
   //chart_.createDefaultAxes();
   chart_.setAxisX(&axisX);
//   chart_.axisY()->setMin( - 1);
//   chart_.axisY()->hide();
//   chart_.axisY()->hide();
//   chart_.axisX()->setMin( - 1);
//   chart_.axisX()->hide();
   buffAxisXPoint_ = Series->points().toStdList();
   createButtonAxisX(buffAxisXPoint_.size());

}

//void ChartView::mouseMoveEvent(QMouseEvent *event)
//{
//   QGraphicsView::mouseMoveEvent(event);
//}

void ChartView::seriesClick(const QPointF &point)
{
   qDebug() << "click";

}

void ChartView::seriesHover(const QPointF &point, bool state)
{
   qDebug() << "Hover";
   if (!lineInChart_)
   {
      lineInChart_ = new LineInChart(&chart_);
   }
   if (state)
   {
      QPoint mouserPosition, buttonPosition;
      mouserPosition = chart_.mapToPosition(point).toPoint();
      qDebug() << chart_.margins() << "marg";
      lineInChart_->setPosMouse(mouserPosition);
      button_.setText(QString::number(point.x()));
      buttonPosition.setY(chart_.size().height() - BUTTON_HEIGHT);
      buttonPosition.setX(mouserPosition.x() - button_.size().width() / 2);
      button_.move(buttonPosition);

      lineInChart_->setZValue(10);
      lineInChart_->updateGeometry();
      lineInChart_->show();
      button_.show();
      highlightButton(mouserPosition.x());
   }
   else
   {
      lineInChart_->hide();
      button_.hide();
      delete lineInChart_;
      lineInChart_ = nullptr;
   }
}
