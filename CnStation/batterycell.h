#ifndef BATTERYCELL_H
#define BATTERYCELL_H

#include <QWidget>

class BatteryCell : public QWidget
{
    Q_OBJECT
public:
    explicit BatteryCell(QWidget *parent = nullptr,QColor batteryColor = QColor("#fcd440"),
                         QColor textColor = QColor(Qt::black),
                         QColor headColor = QColor("#eeeeee"));

    void setValue(double val);
    double getValue();

    // 添加静态绘制函数供委托使用
    static void drawBatteryStatic(QPainter *painter, const QRect &rect, double value,
                                  const QColor &batteryColor = QColor("#fcd440"),
                                  const QColor &textColor = QColor(Qt::black),
                                  const QColor &headColor = QColor("#eeeeee"));

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
private:
    int m_value;
    QColor m_batteryColor;
    QColor m_textColor;
    QColor m_headColor;

};

#endif // BATTERYCELL_H
