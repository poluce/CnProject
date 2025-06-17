#ifndef BATTERYSTACKVIEW_H
#define BATTERYSTACKVIEW_H

#include <QWidget>
#include "tablewidge3d.h"


namespace Ui {
class BatteryStackView;
}

//数据可视化组件
class BatteryStackView : public QWidget
{
    Q_OBJECT

public:
    explicit BatteryStackView(QWidget *parent = nullptr);
    ~BatteryStackView();

private:
    Ui::BatteryStackView *ui;
    TableWidge3D * m_BatteryStack;

};

#endif // BATTERYSTACKVIEW_H
