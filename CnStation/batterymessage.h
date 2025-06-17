#ifndef BATTERYMESSAGE_H
#define BATTERYMESSAGE_H

#include <QChartView>
#include <QChart>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QBarSet>

using namespace QtCharts;
class BatteryMessage : public QChartView
{
    Q_OBJECT
public:
    explicit BatteryMessage(QWidget *parent = nullptr);

    void m_setChartBackgroundColor(QColor color);
    void m_setTitleColor(QColor color);
    void m_setBarColor(QColor color,QColor plan,QColor lab);

private:
    void m_initChart();
    void m_setBarSeries();
    void m_setCategoryX();
    void m_setValueY();
    void m_connectChartAndSeries();

signals:
private:
    QChart * m_chart;
    QBarSeries * m_series;
    QBarSet * m_actualSet,* m_planSet;
    QBarCategoryAxis * m_categoryX;
    QValueAxis * m_valueY;


};

#endif // BATTERYMESSAGE_H
