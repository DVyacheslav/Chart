#ifndef CHARTVIEW_H
#define CHARTVIEW_H
#include <QtCharts/QChartView>
#include <QtWidgets/QRubberBand>
#include <QPieSeries>
#include <QValueAxis>
#include <list>
#include <chart.h>
#include <QXYSeries>
#include "lineinchart.h"
#include <QPushButton>
#include <memory>

QT_CHARTS_USE_NAMESPACE

class ChartView : public QGraphicsView
{
public:
   ChartView(QWidget *parent = nullptr);
   void addSeries(QXYSeries *Series);
protected:
   //void mouseMoveEvent(QMouseEvent *event) override;
   void resizeEvent(QResizeEvent *event) override;
private:
   Chart chart_;
   LineInChart *lineInChart_ = nullptr;
   QPushButton button_;
   std::list<std::unique_ptr<QPushButton>> buttonsAxisX_;
   std::list<QPointF> buffAxisXPoint_;
   QValueAxis axisX;
   const int BUTTON_HEIGHT = 30;
   const int BUTTON_WIDTH = 30;
   const int BUTTONS_MARGIN = 10;
   void buttonSetPosition(int x);
   void addButtonAxisX(std::list<QPointF> listPoint);
   void createButtonAxisX(int count);
   void resizeButtonsAxisX();
   void highlightButton(const int positonX);
private slots:
   void seriesClick(const QPointF &point);
   void seriesHover(const QPointF &point, bool state);
};

#endif // CHARTVIEW_H
