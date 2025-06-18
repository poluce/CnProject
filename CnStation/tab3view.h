#ifndef TAB3VIEW_H
#define TAB3VIEW_H

#include <QWidget>
#include <QTableWidget>
#include <QStandardItemModel>
#include "tableviewdelegate.h"
#include "paginatedproxymodel.h"
#include "signalhub.h"
#include "realtimedataview.h"

class Tab3View : public QWidget
{
    Q_OBJECT
public:
    explicit Tab3View(QWidget *parent = nullptr);
    void m_setViewCount(int count);

private:
    void m_initModel();
    void m_initProxy();
    void m_updateAllViewPages();
    void m_initTableView();
    void m_initNavigationConnect();
    void m_showSeparateWidget(QString string);


public slots:
    void m_navigationFirst();
    void m_navigationPre();
    void m_navigationNext();
    void m_navigationLast();
    void m_navigationToPage(int pages);
    void m_onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void m_onTableDoubleClicked(const QModelIndex &index);




signals:
private:
    QList<QTableView*> m_views;         //视图
    QList<PaginatedProxyModel*> m_proxys;  //代理
    QStandardItemModel * m_model;
//    TableViewDelegate * m_delegate;
    int m_viewCount;
    int m_pageSize =39;
    int m_currentBasePage =0;
    RealTimeDataView * m_separateWidget =nullptr;

};

#endif // TAB3VIEW_H
