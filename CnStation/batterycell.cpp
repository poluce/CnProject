#include "batterycell.h"

#include <QPainter>

//设置电池的显示容量
BatteryCell::BatteryCell(QWidget *parent, QColor batteryColor, QColor textColor, QColor headColor):
    QWidget(parent),m_batteryColor(batteryColor),m_textColor(textColor),m_headColor(headColor)
{
    setValue(99);
}

void BatteryCell::setValue(double val)
{
    if(val >100)
    {
        m_value = 100;

    }else if(val < 0)
    {
        m_value = 0;
    }
    else
    {
        m_value = val;
    }

    update();
}

double BatteryCell::getValue()
{
    return m_value;
}

void BatteryCell::drawBatteryStatic(QPainter *painter, const QRect &rect, double value, const QColor &batteryColor, const QColor &textColor, const QColor &headColor)
{
    // 限制电量值范围
        value = qBound(0.0, value, 100.0);

        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);

        int rmin = qMin(rect.width(), rect.height());
        int r = rmin / 5;

        // 1. 电池主体（圆角矩形边框）
        int radius = rect.height() / 11;
        QRect bodyRect = rect.adjusted(r, r, -2*r, -r);
        painter->setPen(QColor(Qt::lightGray));
        painter->setBrush(QColor(headColor));
        painter->drawRoundedRect(bodyRect, radius, radius);

        // 绘制电池填充
        QRect ValueRect = bodyRect.adjusted(0, 0, -bodyRect.width() * (1 - value / 100.0), 0);
        painter->setBrush(batteryColor);
        painter->setPen(Qt::NoPen);
        painter->drawRoundedRect(ValueRect, radius, radius);

        // 2. 电池头（右侧凸起）
        QRect headRect(bodyRect.right(),
                       bodyRect.center().y() - bodyRect.height() / 6,
                       r,
                       bodyRect.height() / 3);
        painter->setBrush(headColor);
        painter->drawRect(headRect);

        // 3. 电量数值
        painter->setPen(textColor);
        QFont font;
        font.setBold(true);
        font.setPointSizeF(rmin * 0.25); // 委托中字体
        painter->setFont(font);
        QString text = QString::number(value, 'f', 1) ;
        painter->drawText(bodyRect, Qt::AlignCenter, text);

        painter->restore();
}

void BatteryCell::paintEvent(QPaintEvent *event)
{

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    int rmin = qMin(this->width(),this->height());
    int r = rmin/15;

    QRect rect = this->rect(); // 留点边距

    // 1. 电池主体（圆角矩形边框）
    int radius = this->height()/11;
    QRect bodyRect = rect.adjusted(r, r, -r, -r);  // 为右侧“电池头”留空间
    p.setPen(QColor(Qt::gray));
    p.drawRoundedRect(bodyRect,radius,radius);

    //绘制电池
    QRect ValueRect = bodyRect.adjusted(0,0,-bodyRect.width()*(1-m_value/100.0),0);
    p.setBrush(m_batteryColor);
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(ValueRect,radius,radius);

    // 2. 电池头（右侧凸起）
    QRect headRect(bodyRect.right(),
                   bodyRect.center().y() - bodyRect.height() / 6,
                   r,
                   bodyRect.height() / 3);
    p.setBrush(m_headColor);
    p.drawRect(headRect);

    // 3. 电量数值
    p.setPen(m_textColor);
    QFont font = this->font();
    font.setBold(true);

    font.setPointSizeF(rmin * 0.25); // 自适应字号
    p.setFont(font);
    QString text = QString::number(m_value, 'f', 2);
    p.drawText(bodyRect, Qt::AlignCenter, text);


}
