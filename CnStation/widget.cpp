#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("CnStation V1.0");
    setWindowIcon(QIcon(":/png/CnStation.ico"));

    ui->tabWidget->tabBar()->hide();


    m_initDailWidget();
    m_initHistoryWidget();
    //第二页面
    m_initTab2View();
    m_initNavigationBar();

    //第三页面
    m_initTab3View();
    m_initNavigationBar3();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::m_initDailWidget()
{
    m_Dial = new DialWidget;
    QHBoxLayout * layout = new QHBoxLayout(ui->widgetDial);
    layout->addWidget(m_Dial);

    m_BatteryStack = new TableWidge3D;
    QHBoxLayout * layout2 = new QHBoxLayout(ui->widget_4);
    layout2->addWidget(m_BatteryStack);
}

void Widget::m_initHistoryWidget()
{
    m_history = new BottomMessageView;

    QHBoxLayout * layout = new QHBoxLayout(ui->widgetHistory);
    layout->addWidget(m_history);
    layout->setMargin(0);
    layout->setSpacing(0);
}

void Widget::m_initTab2View()
{
    m_tab2View = new Tab2View;
    QHBoxLayout * layout = new QHBoxLayout(ui->widget_midView);
    layout->addWidget(m_tab2View);
    layout->setMargin(0);
    layout->setSpacing(0);

}

void Widget::m_initNavigationBar()
{
    m_navigationBar = new UsePage;
    QHBoxLayout * layout = new QHBoxLayout(ui->widget_navigation);
    layout->addWidget(m_navigationBar);
    layout->setMargin(0);
    layout->setSpacing(0);
}

void Widget::m_initTab3View()
{
    m_tab3View = new Tab3View;

    QHBoxLayout * layout = new QHBoxLayout(ui->widget_sysmidView);
    layout->addWidget(m_tab3View);
    layout->setMargin(0);
    layout->setSpacing(0);
}

void Widget::m_initNavigationBar3()
{
    m_navigationBar3 = new UsePage;
    QHBoxLayout * layout = new QHBoxLayout(ui->widget_sysbottom);
    layout->addWidget(m_navigationBar3);
    layout->setMargin(0);
    layout->setSpacing(0);
}

void Widget::on_pushButton_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
}

void Widget::on_pushButton_2_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}

void Widget::on_pushButton_3_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}

void Widget::on_comboBox_activated(int index)
{
    ui->tabWidget->setCurrentIndex(3);
}
