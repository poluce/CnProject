#ifndef PAGINATEDPROXYMODEL_H
#define PAGINATEDPROXYMODEL_H

#include <QWidget>
#include <QSortFilterProxyModel>

//为了处理分页而存在的代理
class PaginatedProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit PaginatedProxyModel(int ID ,QObject *parent = nullptr);

    // 分页控制接口
    void setPage(int page, int pageSize = 10);
    int getCurrentPage() const { return m_currentPage; }
    int getPageSize() const { return m_pageSize; }
    int getInitPage()const { return m_ID; };
    int getTotalPages() const;

    // 获取当前页面行范围
    QPair<int, int> getRowRange() const;

signals:
    void pageChanged(int page);

protected:
    // 【核心】过滤逻辑 - 决定哪些行可以通过
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    int m_currentPage;  // 当前页面（从0开始）
    int m_pageSize;     // 每页大小
    int m_ID;
    int m_isEmpty = false;

};

#endif // PAGINATEDPROXYMODEL_H
