﻿#include "batterymessage.h"

#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QBarSet>
#include <QValueAxis>

BatteryMessage::BatteryMessage(QWidget *parent) : QChartView(parent)
{

    m_initChart();
    m_setBarSeries();
    m_setCategoryX();
    m_setValueY();
    m_connectChartAndSeries();
    setRenderHint(QPainter::Antialiasing);

    //设置背景颜色
    m_setChartBackgroundColor(QColor("#3b7d89"));
    m_setTitleColor(Qt::white);
    m_setBarColor(QColor("#f3de7f"),QColor("#afe399"),Qt::black);
}

void BatteryMessage::m_setChartBackgroundColor(QColor color)
{
    m_chart->setBackgroundBrush(QBrush(color));
    this->setBackgroundBrush(QBrush(color));

}

void BatteryMessage::m_setTitleColor(QColor color)
{
    m_chart->setTitleBrush(QBrush(color));
    m_chart->legend()->setLabelColor(color);
    m_categoryX->setLabelsBrush(QBrush(color));
}

void BatteryMessage::m_setBarColor(QColor color,QColor plan,QColor lab)
{
    m_actualSet->setColor(color);
    m_actualSet->setLabelBrush(lab);
    m_planSet->setColor(plan);
    m_planSet->setLabelBrush(lab);


}

void BatteryMessage::m_initChart()
{
    m_chart = new  QChart;
    m_chart->setTitle("电量信息");

    //开启系列动画
    m_chart->setAnimationOptions(QChart::AnimationOption::SeriesAnimations);
    this->setChart(m_chart);
}

void BatteryMessage::m_setBarSeries()
{
    m_series = new QBarSeries;
    // 创建数据集
    m_actualSet = new QBarSet("实际");
    m_actualSet->setLabelFont(QFont("黑体",11));

    m_planSet = new QBarSet("计划");
    m_planSet->setLabelFont(QFont("黑体",11));

    *m_actualSet << 504.07 << 462.24; // 实际数据
    *m_planSet << 12 << 0;             // 计划数据为0

    m_series->append(m_actualSet);
    m_series->append(m_planSet);
    m_series->setLabelsVisible(true);
}

void BatteryMessage::m_setCategoryX()
{
    QStringList categories;
    categories << "当日总充电量" << "当日总放电量";
    m_categoryX = new QBarCategoryAxis();
    m_categoryX->append(categories);
    m_categoryX->setGridLineVisible(false);
}

void BatteryMessage::m_setValueY()
{
    m_valueY = new QValueAxis();
    m_valueY->setGridLineVisible(false);
    m_valueY->setVisible(false);

}

void BatteryMessage::m_connectChartAndSeries()
{
    m_chart->addSeries(m_series);

    m_chart->addAxis(m_categoryX,Qt::AlignmentFlag::AlignBottom);
    m_chart->addAxis(m_valueY, Qt::AlignLeft);


    m_series->attachAxis(m_categoryX);
    m_series->attachAxis(m_valueY);
}
