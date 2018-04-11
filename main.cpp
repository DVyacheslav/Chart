#include <QApplication>
#include <QQmlApplicationEngine>
#include <QMainWindow>
#include "chartview.h"

#include <QtCore/QtMath>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QScatterSeries>

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
   QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

   auto *scatterSeries = new QScatterSeries();
   auto *series = new QLineSeries();
   for (int i = 0; i < 20; i++) {
       QPointF p((qreal) i,QRandomGenerator::global()->bounded(20) ); //qSin(M_PI / 50 * i) * 100
     //  p.ry() += QRandomGenerator::global()->bounded(20);
       *scatterSeries << p;
       *series << p;

   }


   QApplication app(argc, argv);
   QMainWindow *myWindow = new QMainWindow;
   ChartView *myChartView = new ChartView();
   //myChartView->addSeries(series);
   myChartView->addSeries(scatterSeries);
   myChartView->setRenderHint(QPainter::Antialiasing);
   myWindow->setCentralWidget(myChartView);
   myWindow->resize(500, 500);

   myWindow->show();
//   QQmlApplicationEngine engine;
//   engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//   if (engine.rootObjects().isEmpty())
//      return -1;

   return app.exec();
}
