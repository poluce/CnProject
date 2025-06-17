#include "dialwidget.h"

#include <QTimer>

DialWidget::DialWidget(QWidget *parent) : QWidget(parent), value(2)
{

    QTimer  * timer  = new QTimer(this);
    timer->setInterval(1000);
    connect(timer,&QTimer::timeout,this,[=]()
    {
        static int i = 0;
        static bool add = true;
        if(i>=100)
            add = false;
        if(i<2)
            add = true;

        setValue((add)? i++:i--);
    });
    timer->start();

}

void DialWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // 画背景（相当于 QFrame）
    p.setBrush(QColor("#3b7d89"));
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(rect(), 0, 0);

    // 1. 计算中心和半径
    int w = width(), h = height();
    int r = qMin(w, h) *2/5;
    QPoint center(w/2, h/2+ (h/14));

    // 2. 画背景弧（分段颜色）
    drawArcSections(p, center, r);

    // 3. 画刻度线与数字
    drawScales(p, center, r);

    // 4. 画指针
    drawPointer(p, center, r-30);

    // 5. 画中心数值和文字
    drawTexts(p, center, r);
}

void DialWidget::drawArcSections(QPainter &p, QPoint c, int r)
{
    // 浅蓝色段
    p.save();
    QPen pen(QColor("#92e3ea"), 15);
    p.setPen(pen);
    p.drawArc(QRect(c.x()-r, c.y()-r, 2*r, 2*r), -43.5*16, 268*16); // 225度
    // 蓝色段
    pen.setColor(QColor("#63a9dc"));
    p.setPen(pen);
    p.drawArc(QRect(c.x()-r, c.y()-r, 2*r, 2*r), -45*16, 188*16); // 45度
    p.restore();
    // 红色段
    pen.setColor(QColor("#fc763e"));
    p.setPen(pen);
    p.drawArc(QRect(c.x()-r, c.y()-r, 2*r, 2*r), -45*16, 80*16); // 45度

}

QPointF DialWidget::calculatePos(QPoint &c, double &angle, int &r, int n)
{
    double x = c.x() + (r+n) * qCos(angle);
    //在坐标系统的方向上。Qt的坐标系统原点位于左上角，y轴向下；
    //而标准三角函数坐标则原点居中，y轴向上。因此，Qt绘图的y轴方向与数学坐标系是相反的。
    //所以需要在执行y坐标的时候用“-”减号(Qt 里 y 轴朝下 → 计算几何时，凡是 “向上” 要写成 y - )
    double y = c.y() - (r+n) * qSin(angle);
    return QPointF(x,y);
}

void DialWidget::drawScales(QPainter &p, QPoint c, int r)
{
    p.save();
    int startAngle = -45, spanAngle = 270, steps = 50;
    for (int i = 0; i <= steps; ++i)
    {
        //获取每步的角度（抓换为弧度制）弧度 = （角度/180）*pai
        double angle = (startAngle + spanAngle * i / steps)* M_PI/180 ;

        QPen pen(Qt::white, (i%5==0)?8:3);
        p.setPen(pen);
        p.drawLine(calculatePos(c,angle,r,12), calculatePos(c,angle,r,18));
        // 刻度数字
        if (i%5==0)
        {
            p.drawLine(calculatePos(c,angle,r,-2), calculatePos(c,angle,r,15));
            double v = 100 - (100) * i/steps;
            QString str = QString::number(v, 'f', 0);
            double xt = c.x() + (r-30) * qCos(angle);
            double yt = c.y() - (r-30) * qSin(angle);
            if(v<30)
                p.setPen("#92e3ea");
            else  if(v<70)
                p.setPen("#63a9dc");
            else
                p.setPen("#fc763e");
            QFont font;
            font.setPointSize(18);         // 设置字号为 18 pt
            p.setFont(font);               // 应用到 QPainter
            p.drawText(QRectF(xt-40, yt-10, font.pointSize()*4, font.pointSize()*2), Qt::AlignCenter, str);
        }
    }
    p.restore();
}

void DialWidget::drawPointer(QPainter &p, QPoint c, int r)
{
    p.save();
    double startAngle = -45, spanAngle = 270;
    double percent = 1- (value ) / 100; // 归一化
    double angle = (startAngle + spanAngle * percent) * M_PI / 180.0;
    QPolygonF poly;
    poly << c;
    poly << QPointF(c.x() + r * qCos(angle - 0.03), c.y() - r * qSin(angle - 0.03));
    poly << QPointF(c.x() + (r-20) * qCos(angle + 0.03), c.y() - (r-20) * qSin(angle + 0.03));
    p.setBrush(QColor("#8fe4ec"));
    p.setPen(Qt::NoPen);
    p.drawPolygon(poly);
    p.restore();
}

void DialWidget::drawTexts(QPainter &p, QPoint c, int r)
{
    p.save();
    QFont f = p.font();
    f.setPointSize(25);
    f.setBold(true);
    p.setFont(f);
    p.setPen("#92e3ea");
    p.drawText(QRectF(c.x()-70, c.y()+r/5, 140, 80), Qt::AlignCenter, QString("%1 %").arg(value));
    // 左下文字
    f.setPointSize(14);
    f.setBold(true);
    p.setFont(f);
    p.drawText(QRectF(c.x()-r*qCos(45)-120, c.y()+r*0.77, 120, 40), Qt::AlignCenter, "SOC下限");
    // 右下文字
    p.drawText(QRectF(c.x()+r*qCos(45), c.y()+r*0.77, 120, 40), Qt::AlignCenter, "SOC上限");
    p.restore();
}
