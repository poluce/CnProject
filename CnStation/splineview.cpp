#include "splineview.h"
#include "ui_splineview.h"

#include <QDateTime>
#include <QDebug>
#include <QGraphicsLayout>
#include <QTimer>

SplineView::SplineView(QWidget *parent) :
    QChartView(parent),
    ui(new Ui::SplineView)
{
    ui->setupUi(this);

    //初始化时间
    start = QDateTime::currentDateTime();
    start.setTime(QTime(0,0,0));
    end = start.addDays(1);  // 到第二天00:00，即24:00

    m_initChart();
    m_setZeroSeries();
    m_setAreaSeries();
    m_setTimeAxis();
    m_setValeYxis();
    m_connectAxisAndSeries();
    addCustomTitleSafely();
    setBackColor("#3b7d89");

}

SplineView::~SplineView()
{
    delete ui;
}

void SplineView::setBackColor(QColor color)
{
    //表格背景
    m_chart->setBackgroundBrush(QBrush(color));
    this->setBackgroundBrush(QBrush(color));

}

void SplineView::m_initChart()
{
    m_chart = new QChart;
    m_chart->layout()->setContentsMargins(10,10,10,10);

    this->setChart(m_chart);

    // 设置渲染提示
    this->setRenderHint(QPainter::Antialiasing);           // 抗锯齿
    //    this->setRenderHint(QPainter::TextAntialiasing);       // 文本抗锯齿
    this->setRenderHint(QPainter::SmoothPixmapTransform);  // 平滑像素变换
    this->setRenderHint(QPainter::HighQualityAntialiasing); // 高质量抗锯齿
}



void SplineView::m_setZeroSeries()
{
    m_zeroSeries = new QLineSeries;
    m_zeroSeries->setName("当日实际");

    m_zeroSeries->append(start.toMSecsSinceEpoch(),0);
    m_zeroSeries->append(start.addDays(1).toMSecsSinceEpoch(),0);
    //    m_zeroSeries->append(m_initData());
    m_zeroSeries->setPen(QPen(QColor("#77d0c4"), 4));

}

void SplineView::m_setAreaSeries()
{
    //创建正值区域
    QLineSeries * inUpper = new QLineSeries;
    QLineSeries * inLower = new QLineSeries;

    //创建负值显示曲线
    QLineSeries * outUpper = new QLineSeries;
    QLineSeries * outLower = new QLineSeries;

    //获取数据，对数据进行处理
    QList<QPointF> data = m_initData();
    for(auto & point : data)
    {
        qint64 x = point.x();
        qint64 y = point.y();

        if(y >= 0)
        {
            inUpper->append(x,y);
            inLower->append(x,0);
        }else
        {
            outUpper->append(x,0);
            outLower->append(x,y);
        }
    }

    // 创建正值面积曲线
    m_inArea = new QAreaSeries(inUpper,inLower);
    m_inArea->setName("明日计划");
    m_inArea->setColor(QColor("#f2e081"));
    m_inArea->setBorderColor(QColor("#77d0c4"));

    //创建负值面积曲线
    m_outArea = new QAreaSeries(outUpper,outLower);
    m_outArea->setName("当日计划");
    m_outArea->setColor(QColor("#f2e081"));
    m_outArea->setBorderColor(QColor("#77d0c4"));
}

void SplineView::m_setTimeAxis()
{
    m_dateTimeX = new QDateTimeAxis;
    m_dateTimeX->setGridLineVisible(false);
    m_dateTimeX->setLineVisible(false);
    m_dateTimeX->setFormat("HH");
    m_dateTimeX->setRange(start, end);
    m_dateTimeX->setTickCount(25);
}

void SplineView::m_setValeYxis()
{
    m_valueY = new QValueAxis;
    m_valueY->setGridLineVisible(false);
    m_valueY->setRange(-400,400);
    m_valueY->setLabelFormat("%.0f");
    m_valueY->setTickCount(9);
    m_valueY->setTickInterval(50);
}

void SplineView::m_connectAxisAndSeries()
{

    //添加曲线
    m_chart->addSeries(m_zeroSeries);
    m_chart->addSeries(m_inArea);
    m_chart->addSeries(m_outArea);

    //添加坐标轴
    m_chart->addAxis(m_dateTimeX,Qt::AlignmentFlag::AlignBottom);
    m_chart->addAxis(m_valueY,Qt::AlignmentFlag::AlignLeft);

    //组合曲线和坐标轴
    //[1]
    m_inArea->attachAxis(m_dateTimeX);
    m_inArea->attachAxis(m_valueY);

    m_outArea->attachAxis(m_dateTimeX);
    m_outArea->attachAxis(m_valueY);

    //[2]
    m_zeroSeries->attachAxis(m_dateTimeX);
    m_zeroSeries->attachAxis(m_valueY);
}


//获取数据的例子
QList<QPointF> SplineView::m_initData()
{
    //创建时间数据
    QList<qint64> timeData;
    for(int i = 0; i < 288; ++i)
    {
        //循环创建规定间隔的时间数据
        QDateTime temp = start.addSecs(i*60*5);
        timeData.append(temp.toMSecsSinceEpoch());
    }

    //创建数据
    QList<qint64> data;
    data << 0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0
         << -200<<-200<<-200<<-200<<-200<<-200<<-200<<-200<<-200<<-200<<-200<<-200
         << -200<<-200<<-200<<-200<<-200<<-200<<-200<<-200<<-200<<-200<<-200<<-200
         << -200<<-200<<-199<<-191<<-178<<-160<<-139<<-116<<-92<<-69<<-47<<-28
         << 0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0
         << 0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0
         << 0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0
         << 247<<272<<290<<299<<300<<300<<300<<300<<300<<300<<300<<300
         << 300<<300<<300<<300<<300<<300<<300<<300<<300<<300<<300<<300
         << 300<<300<<300<<300<<300<<297<<285<<264<<237<<205<<170<<134
         << 0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0
         << 0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0
         << 0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0
         << 0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0
         << 0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0
         << 0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0
         << 0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0
         << 0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0
         << 0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0
         << 0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0
         << 0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0
         << 0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0
         << 0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0
         << 0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0<<0;

    //组合数据
    QList<QPointF> series;
    for( int i=0;i< 288 ;++i)
    {
        series.append(QPointF(timeData.at(i),data.at(i)));
    }
    return  series;
}

void SplineView::addCustomTitleSafely()
{
    // 移除默认标题
    m_chart->setTitle("功率曲线");

    // 确保图表场景已经准备好
    if (m_chart->scene())
    {
        QFont font("Microsoft YaHei", 8, QFont::Bold);
        QGraphicsTextItem *titleItem = new QGraphicsTextItem("充放电功率(MW)");
        QGraphicsTextItem *titleItem2 = new QGraphicsTextItem("小时");
        titleItem->setFont(font);
        titleItem->setDefaultTextColor("#77d0c4");
        font.setPointSize(7);
        font.setBold(false);
        titleItem2->setFont(font);
        titleItem2->setDefaultTextColor("#77d0c4");

        // 设置Z值确保在chart上层
        titleItem->setZValue(m_chart->zValue()+1);
        titleItem2->setZValue(m_chart->zValue()+1);

        m_chart->scene()->addItem(titleItem);
        m_chart->scene()->addItem(titleItem2);

        // 获取图表的实际绘图区域
        QRectF plotArea = m_chart->plotArea();

        //
        QPointF rightPos = m_chart->mapToPosition(QPointF(end.toMSecsSinceEpoch(),0), m_zeroSeries);

        QTimer * timer = new QTimer(this);
        connect(timer, &QTimer::timeout, [=]()
        {
            QPointF rightPos = m_chart->mapToPosition(QPointF(end.toMSecsSinceEpoch(),0), m_zeroSeries);
            rightPos.setY(rightPos.y()-15);
            rightPos.setX(rightPos.x()-2);
            titleItem2->setPos(rightPos);
        });
        timer->start(10);

        // 设置在绘图区域的左上角
        titleItem->setPos(plotArea.left()-10, plotArea.top()+20);
        titleItem2->setPos(rightPos);
    }
}
