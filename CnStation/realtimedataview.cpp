#include "realtimedataview.h"
#include "ui_realtimedataview.h"

#include <QStandardItemModel>
#include <QTimer>

RealTimeDataView::RealTimeDataView(QString string,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RealTimeDataView),m_Title(string)
{
    ui->setupUi(this);

    m_start = QDateTime::currentDateTime();
    m_start.setTime(QTime(0,0,0));
    m_end = m_start.addDays(1);

    this->setMinimumSize(1600,800);

    //设置无标题栏
   this->setWindowFlags(Qt::FramelessWindowHint |Qt::WindowType::SubWindow);

    m_initChart();
    m_initSeries();
    m_initZeroSeries();
    m_initData();
    m_initDateTimeX();
    m_initValueY();
    m_connectSeries();

    m_initLabel();
    m_initLeftTabel();
    m_initRightLabel();

    addCustomTitleSafely(m_chart,"","小时");



}

RealTimeDataView::~RealTimeDataView()
{
    delete ui;
}

void RealTimeDataView::m_initChart()
{
    m_chart = new QChart;
    m_chart->setBackgroundBrush(QBrush(QColor("#3b7d89")));
    m_view = new QChartView;
    m_view->setChart(m_chart);


    // 设置渲染提示
    m_view->setRenderHint(QPainter::Antialiasing);           // 抗锯齿
    //    m_view->setRenderHint(QPainter::TextAntialiasing);       // 文本抗锯齿
    m_view->setRenderHint(QPainter::SmoothPixmapTransform);  // 平滑像素变换
    m_view->setRenderHint(QPainter::HighQualityAntialiasing); // 高质量抗锯齿

    QHBoxLayout * layout = new QHBoxLayout(ui->widget_chart);
    layout->addWidget(m_view);
    layout->setMargin(0);
    layout->setSpacing(0);

}

void RealTimeDataView::m_initSeries()
{
    m_series = new QLineSeries;
    m_series->append(m_initData());
    m_series->setPen(QPen(QColor("#dee4a6"),3));
    m_series->setName("数据值");

}

void RealTimeDataView::m_initZeroSeries()
{
    m_zeroSeries = new QLineSeries;
    m_zeroSeries->append(m_start.toMSecsSinceEpoch(),0);
    m_zeroSeries->append(m_start.addDays(1).toMSecsSinceEpoch(),0);
    m_zeroSeries->setPen(QPen(QColor("#77d0c4"),1));

}


//获取数据的例子
QList<QPointF> RealTimeDataView::m_initData()
{
    //创建时间数据
    QList<qint64> timeData;
    for(int i = 0; i < 288; ++i)
    {
        //循环创建规定间隔的时间数据
        QDateTime temp = m_start.addSecs(i*60*5);
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

void RealTimeDataView::m_initDateTimeX()
{
    m_DateTimeX = new QDateTimeAxis;
    m_DateTimeX->setRange(m_start,m_end);
    m_DateTimeX->setFormat("hh");
    m_DateTimeX->setTickCount(25);
    m_DateTimeX->setGridLineVisible(false);
    m_DateTimeX->setLineVisible(false);

}

void RealTimeDataView::m_initValueY()
{
    m_ValueY = new QValueAxis;
    m_ValueY->setRange(-300,300);
    m_ValueY->setGridLineVisible(false);
}

void RealTimeDataView::m_connectSeries()
{
    m_chart->addSeries(m_series);
    m_chart->addSeries(m_zeroSeries);

    m_chart->addAxis(m_DateTimeX,Qt::AlignmentFlag::AlignBottom);
    m_chart->addAxis(m_ValueY,Qt::AlignmentFlag::AlignLeft);

    m_series->attachAxis(m_DateTimeX);
    m_series->attachAxis(m_ValueY);

    m_zeroSeries->attachAxis(m_DateTimeX);
    m_zeroSeries->attachAxis(m_ValueY);


}

void RealTimeDataView::m_initRightLabel()
{
    QString time = QDate::currentDate().toString("yyyy年MM月dd日");
    ui->label_right->setText("XXX储能电站"+time);
}

void RealTimeDataView::m_initLabel()
{
    ui->label_title->setText(m_Title);
}

void RealTimeDataView::m_initLeftTabel()
{
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(288);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeMode::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeMode::ResizeToContents);
    ui->tableWidget->verticalHeader()->hide();

    QStringList list;
    list<<"时间"<<"数据";
    ui->tableWidget->setHorizontalHeaderLabels(list);
    QList<QPointF>  pointList =  m_initData();
    for(int row = 0;row <288;row++)
    {
        QTableWidgetItem * item  = new QTableWidgetItem;
        item->setText(m_start.addSecs(60*5*row).toString("yyyy-mm-dd hh:mm:ss"));
        item->setTextAlignment(Qt::AlignHCenter);
        item->setForeground(QBrush(QColor(Qt::cyan)));
        ui->tableWidget->setItem(row,0,item);


        item  = new QTableWidgetItem;
        item->setText(QString::number(pointList.at(row).y()));
        item->setTextAlignment(Qt::AlignHCenter);
        item->setForeground(QBrush(QColor(Qt::cyan)));
        ui->tableWidget->setItem(row,1,item);
    }


}



void RealTimeDataView::on_pushButton_4_clicked()
{
    this->close();
}

void RealTimeDataView::addCustomTitleSafely(QChart * m_chart,QString str1,QString str2)
{
    // 默认标题
    m_chart->setTitle("");

    // 确保图表场景已经准备好
    if (m_chart->scene())
    {
        QFont font("Microsoft YaHei", 8, QFont::Bold);
        QGraphicsTextItem *titleItem = new QGraphicsTextItem(str1);
        QGraphicsTextItem *titleItem2 = new QGraphicsTextItem(str2);
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
        QPointF rightPos = m_chart->mapToPosition(QPointF(m_end.toMSecsSinceEpoch(),0), m_zeroSeries);

        QTimer * timer = new QTimer(this);
        connect(timer, &QTimer::timeout, [=]()
        {
            QPointF rightPos = m_chart->mapToPosition(QPointF(m_end.toMSecsSinceEpoch(),0), m_zeroSeries);
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

