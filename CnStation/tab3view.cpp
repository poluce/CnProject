#include "tab3view.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QItemSelectionModel>

Tab3View::Tab3View(QWidget *parent) : QWidget(parent)
{
    m_initModel();
    m_initProxy();
    m_initTableView();
    m_initNavigationConnect();
}

//初始化模型 （模拟数据）
void Tab3View::m_initModel()
{
    m_model = new QStandardItemModel;

    //设置行列
    m_model->setColumnCount(2);
    m_model->setRowCount(1000);

    //填充给表头的数据
    QStringList labelist;
    labelist <<"数据名称"<<"值";
    m_model->setHorizontalHeaderLabels(labelist);

    //填充数据
    for(int i = 0;i <1000;i++)
    {
        QStandardItem * item = new QStandardItem(QString("模拟数据%1").arg(i));
        item->setForeground(QBrush(Qt::cyan));
        m_model->setItem(i,0,item);

        item = new QStandardItem();
        item->setForeground(QBrush(Qt::cyan));
        item->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
        item->setText(QString("%1").arg( (i/3)==0 ? i/4:i/5 ));
        m_model->setItem(i,1,item);
    }

}

//初始化自定义数据代理
void Tab3View::m_initProxy()
{
    for( int i= 0; i<4 ;i++)
    {
        PaginatedProxyModel * proxy = new PaginatedProxyModel(i);
        proxy->setSourceModel(m_model);
        m_proxys.append(proxy);
    }
    //更新视图
    m_updateAllViewPages();

}

//
void Tab3View::m_updateAllViewPages()
{
    for( int i = 0; i < 4;i++)
    {
        //根据初始页面计算页面范围
        int page = m_currentBasePage *4 +i;
        m_proxys.at(i)->setPage(page,m_pageSize);
    }
}

void Tab3View::m_initTableView()
{
    QHBoxLayout * layout = new QHBoxLayout(this);
    for(int i = 0;i < 4;i++)
    {
        QTableView * view = new QTableView;
        view->setModel(m_proxys.at(i));

        //设置表头拉伸
        view->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
        //view->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeMode::ResizeToContents);

        //设置选择行为
        view->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        //隐藏垂直表头
        view->verticalHeader()->hide();

        //view->setShowGrid(false);
        view->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

        // 连接双击信号 - 核心代码
         connect(view, &QTableView::doubleClicked,
                   this, &Tab3View::m_onTableDoubleClicked);

        //清除选中的状态
        connect(view->selectionModel(), &QItemSelectionModel::selectionChanged,
                this, &Tab3View::m_onSelectionChanged);
        layout->addWidget(view);
        m_views.append(view);
    }
}

void Tab3View::m_initNavigationConnect()
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

//双击出现新的窗口
void Tab3View::m_showSeparateWidget(QString string)
{
    if(m_separateWidget )
    {
        m_separateWidget->close();        // 先关闭窗口
        m_separateWidget->deleteLater();  // 延迟删除
        m_separateWidget = nullptr;       // 避免悬空指针
    }


    m_separateWidget = new RealTimeDataView(string);
    m_separateWidget->show();



}

void Tab3View::m_navigationFirst()
{

}

void Tab3View::m_navigationPre()
{

}

void Tab3View::m_navigationNext()
{

}

void Tab3View::m_navigationLast()
{

}

void Tab3View::m_navigationToPage(int pages)
{


}

//同步选中的信息
void Tab3View::m_onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    // 获取发送信号的视图
        QItemSelectionModel* senderModel = qobject_cast<QItemSelectionModel*>(sender());
        if (!senderModel) return;

        // 清除其他视图的选择
        for(QTableView* view : m_views)
        {
            if(view->selectionModel() != senderModel)
            {
                // 临时断开信号，避免递归调用
                view->selectionModel()->blockSignals(true);
                view->clearSelection();
                view->selectionModel()->blockSignals(false);
            }
        }
}

void Tab3View::m_onTableDoubleClicked(const QModelIndex &index)
{

        // 检查索引是否有效
        if (!index.isValid())
        return;

        // 获取发送信号的视图，确定信号来源
        QTableView* senderView = qobject_cast<QTableView*>(sender());

        if (!senderView)
        {
            return;
        }

        // 获取各自代理中选中行的数据()
        int row = index.row();
        QAbstractItemModel* model = senderView->model();
        qDebug()<<"index.row():"<<row;

        // 提取该行的所有数据
        QStringList rowData;
        for (int col = 0; col < model->columnCount(); ++col)
        {
            QModelIndex cellIndex = model->index(row, col);
            rowData << model->data(cellIndex).toString();

        }
        qDebug()<<"QStringList:"<<rowData;

        m_showSeparateWidget(rowData.first());

}


