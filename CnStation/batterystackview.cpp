#include "batterystackview.h"
#include "ui_batterystackview.h"

#include <QHBoxLayout>

BatteryStackView::BatteryStackView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BatteryStackView)
{
    ui->setupUi(this);
    m_BatteryStack = new TableWidge3D;
    QHBoxLayout * layout2 = new QHBoxLayout(ui->widget);
    layout2->addWidget(m_BatteryStack);
    layout2->setMargin(0);
    layout2->setSpacing(0);


}

BatteryStackView::~BatteryStackView()
{
    delete ui;
}
