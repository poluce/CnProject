#include "bottommessageview.h"
#include "ui_bottommessageview.h"

BottomMessageView::BottomMessageView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BottomMessageView)
{
    ui->setupUi(this);
    m_curveView = new SplineView;
    QVBoxLayout * layout = new QVBoxLayout(ui->widget);
    layout->addWidget(m_curveView);
    layout->setMargin(0);
    layout->setSpacing(0);


    m_widgetMid = new BatteryMessage;
    QVBoxLayout * layout1 = new QVBoxLayout(ui->widget_mid);
    layout1->addWidget(m_widgetMid);
    layout1->setMargin(0);
    layout1->setSpacing(0);


    m_widgetRight = new ChargMessage;
    QVBoxLayout * layout3 = new QVBoxLayout(ui->widget_right);
    layout3->addWidget(m_widgetRight);
    layout3->setMargin(0);
    layout3->setSpacing(0);
}

BottomMessageView::~BottomMessageView()
{
    delete ui;
}
