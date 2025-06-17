#ifndef DIAWIDGET_H
#define DIAWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QtMath>

//SOC表图
class DialWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DialWidget(QWidget *parent = nullptr);

    void setValue(double v) { value = v; update(); }
protected:
    void paintEvent(QPaintEvent *) override;

    void drawArcSections(QPainter& p, QPoint c, int r);

    //计算每个刻度线段的端点位置
    QPointF calculatePos(QPoint &c ,double &angle,int &r,int n);
    void drawScales(QPainter& p, QPoint c, int r);
    void drawPointer(QPainter& p, QPoint c, int r);
    void drawTexts(QPainter& p, QPoint c, int r);

private:
    double value; // 当前值
};


#endif // DIAWIDGET_H
