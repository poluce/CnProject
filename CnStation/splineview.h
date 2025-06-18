#ifndef SPLINEVIEW_H
#define SPLINEVIEW_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QSplineSeries>
#include <QLineSeries>
#include <QAreaSeries>
#include <QDateTime>

using namespace QtCharts;

namespace Ui {
class SplineView;
}

class SplineView : public QChartView
{
    Q_OBJECT

public:
    explicit SplineView(QWidget *parent = nullptr);
    ~SplineView();
    void setBackColor(QColor color);


private:
    void m_initChart();
    void m_setZeroSeries();
    void m_setAreaSeries();
    void m_setTimeAxis();
    void m_setValeYxis();
    void m_connectAxisAndSeries();
    QList<QPointF> m_initData();
    void addCustomTitleSafely(QChart * chart,QString str1,QString str2);



private:
    Ui::SplineView *ui;
    QChart * m_chart;
    QValueAxis * m_valueY;
    QDateTimeAxis * m_dateTimeX;
    QAreaSeries * m_inArea;
    QAreaSeries * m_outArea;
    QLineSeries * m_zeroSeries;
    QDateTime start;
    QDateTime end;


};

#endif // SPLINEVIEW_H
