#ifndef TAB2VIEW_H
#define TAB2VIEW_H

#include <QWidget>
#include <QTableWidget>
#include <QStandardItemModel>
#include "tableviewdelegate.h"
#include "paginatedproxymodel.h"
#include "signalhub.h"

class Tab2View : public QWidget
{
    Q_OBJECT
public:
    explicit Tab2View(QWidget *parent = nullptr);
    void m_setViewCount(int count);

private:
    void m_initModel();
    void m_initProxy();
    void m_initTableView();
    void m_initNavigationConnect();
    void m_updateAllViewPages();

public slots:
    void m_navigationFirst();
    void m_navigationPre();
    void m_navigationNext();
    void m_navigationLast();
    void m_navigationToPage(int pages);


signals:
private:
    QList<QTableView*> m_views;
    QList<PaginatedProxyModel*> m_proxys;
    QTableView * m_v1,* m_v2,*m_v3,*m_v4;
    QStandardItemModel * m_model;
    TableViewDelegate * m_delegate;
    int m_viewCount;
    int m_pageSize =39;
    int m_currentBasePage =0;

};

#endif // TAB2VIEW_H
