#ifndef REALTIMEDATAVIEW_H
#define REALTIMEDATAVIEW_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QValueAxis>
namespace Ui {
class RealTimeDataView;
}
using namespace QtCharts;

class RealTimeDataView : public QWidget
{
    Q_OBJECT

public:
    explicit RealTimeDataView(QString string,QWidget *parent = nullptr);
    ~RealTimeDataView();
    void addCustomTitleSafely(QChart *m_chart, QString str1, QString str2);
private slots:
    void on_pushButton_4_clicked();

private:
    void m_initChart();
    void m_initSeries();
    void m_initZeroSeries();
    QList<QPointF> m_initData();
    void m_initDateTimeX();
    void m_initValueY();
    void m_connectSeries();
    void m_initLabel();
    void m_initLeftTabel();
    void m_initRightLabel();



private:
    Ui::RealTimeDataView *ui;
    QString m_Title;
    QChartView * m_view;
    QChart * m_chart;
    QLineSeries * m_series , * m_zeroSeries;
    QDateTime m_start;
    QDateTime m_end;

    QDateTimeAxis * m_DateTimeX;
    QValueAxis * m_ValueY;


};

#endif // REALTIMEDATAVIEW_H
