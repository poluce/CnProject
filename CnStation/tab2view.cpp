#include "tab2view.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QHeaderView>

Tab2View::Tab2View(QWidget *parent) : QWidget(parent),m_viewCount(4)
{
    //初始化数据层
    m_initModel();
    //初始化过滤层
    m_initProxy();
    //初始化视图层
    m_initTableView();
    //初始化链接
    m_initNavigationConnect();

}

//初始化数据层
void Tab2View::m_initModel()
{
    m_model = new QStandardItemModel;
    m_model->setColumnCount(5);
    m_model->setRowCount(1000);

    //填充表头的数据
    QStringList labels;
    labels<<"设备"<<"有功功率(MW)"<< "运行状态"<<"SOC(%)"<<"SOH(%)";
    m_model->setHorizontalHeaderLabels(labels);


    // 添加测试数据
    for (int row = 0; row < 1000; ++row)
    {
        m_model->setItem(row, 0, new QStandardItem(QString("储能设备_%1").arg(row + 1, 3, 10, QChar('0'))));
        m_model->setItem(row, 1, new QStandardItem(QString::number(10.5 + row * 0.8, 'f', 1)));
        m_model->setItem(row, 2, new QStandardItem(row % 3 == 0 ? "维护" : "运行"));
        m_model->setItem(row, 3, new QStandardItem(QString::number(35 + row ))); // SOC
        m_model->setItem(row, 4, new QStandardItem(QString::number(12 + row ))); // SOH
    }


    for (int row = 0; row < 1000; ++row)
    {

        if(m_model->item(row, 2)->text() == "运行")
            m_model->item(row, 2)->setForeground(QBrush(Qt::cyan));
        else
            m_model->item(row, 2)->setForeground(QBrush(Qt::GlobalColor::red));
        m_model->item(row, 0)->setForeground(QBrush(Qt::white));
        m_model->item(row, 1)->setForeground(QBrush(Qt::white));

        // 其他列设置居中对齐
        for (int col = 0; col < 3; ++col)
        {
            if (QStandardItem *item = m_model->item(row, col))
            {
                item->setTextAlignment(Qt::AlignCenter);
            }
        }
    }

}
//初始化过滤层
void Tab2View::m_initProxy()
{
    for(int i =0; i<4;i++)
    {
        PaginatedProxyModel*  proxy = new PaginatedProxyModel(i);
        proxy->setSourceModel(m_model);
        m_proxys.append(proxy);
    }
    //更新数据代理
    m_updateAllViewPages();
}
//初始化视图层
void Tab2View::m_initTableView()
{
    m_delegate = new TableViewDelegate(this);

    QHBoxLayout * layout = new QHBoxLayout(this);

    layout->setSpacing(20);
    for(int i =0; i<4;i++)
    {
        QTableView*  view = new QTableView;
        view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        //设置选择模式
        view->setSelectionMode(QAbstractItemView::SelectionMode::NoSelection);
        view->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        view->verticalHeader()->hide();
        view->setModel(m_proxys.at(i));
        view->setItemDelegate(m_delegate);
        view->setShowGrid(false);
        view->setEditTriggers(QAbstractItemView::NoEditTriggers);
        layout->addWidget(view);
        m_views.append(view);
    }
    qDebug()<<"m_views:"<<m_views;

}

void Tab2View::m_initNavigationConnect()
{

    connect(&SignalHub::instance(),&SignalHub::msgArrived,this,[this](MySignal::WidgetType type, QVariant msg)
    {
        if(type == MySignal::WidgetType::Navigation_first)
            m_navigationFirst();
    });

    connect(&SignalHub::instance(),&SignalHub::msgArrived,this,[this](MySignal::WidgetType type, QVariant msg)
    {
        if(type == MySignal::WidgetType::Navigation_pre)
            m_navigationPre();
    });

    connect(&SignalHub::instance(),&SignalHub::msgArrived,this,[this](MySignal::WidgetType type, QVariant msg)
    {
        if(type == MySignal::WidgetType::Navigation_next)
            m_navigationNext();
    });

    connect(&SignalHub::instance(),&SignalHub::msgArrived,this,[this](MySignal::WidgetType type, QVariant msg)
    {
        if(type == MySignal::WidgetType::Navigation_last)
            m_navigationLast();
    });

    connect(&SignalHub::instance(),&SignalHub::msgArrived,this,[this](MySignal::WidgetType type, QVariant msg)
    {
        if(type == MySignal::WidgetType::Navigation_topage)
            m_navigationToPage(msg.toInt());
    });

}

//更新视图代理
void Tab2View::m_updateAllViewPages()
{
    //更换所有视图页面
    for (int i = 0; i < 4; i++)
    {
        int pageForView = m_currentBasePage *4 + i;
        m_proxys.at(i)->setPage(pageForView, m_pageSize);
    }
}

void Tab2View::m_navigationFirst()
{
    qDebug()<<"m_navigationFirst";
    m_currentBasePage = 0;
    m_updateAllViewPages();
}

void Tab2View::m_navigationPre()
{
    qDebug()<<"m_navigationPre";

    //从空页直接到有值
    if(m_currentBasePage*4 > m_proxys.first()->getTotalPages())
    {
        m_navigationLast();
        return;
    }

    if(m_currentBasePage >0)
    {
        m_currentBasePage--;
        m_updateAllViewPages();
    }

}

void Tab2View::m_navigationNext()
{
    qDebug()<<"m_navigationNext";
    if(m_currentBasePage*4 + 4 < m_proxys.first()->getTotalPages())
    {
        m_currentBasePage++;
        qDebug()<<"m_navigationNext:"<<m_currentBasePage<<"m_proxys.first()->getTotalPages():"<<m_proxys.first()->getTotalPages();
        m_updateAllViewPages();
    }
}

void Tab2View::m_navigationLast()
{
    qDebug()<<"m_navigationLast";


    m_currentBasePage = m_proxys.first()->getTotalPages()/4;
    m_updateAllViewPages();

}

void Tab2View::m_navigationToPage(int pages)
{
    qDebug()<<"m_navigationToPage:"<<pages;
    m_currentBasePage = pages;
    m_updateAllViewPages();

}



