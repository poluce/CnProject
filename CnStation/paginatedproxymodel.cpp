#include "paginatedproxymodel.h"

PaginatedProxyModel::PaginatedProxyModel(int ID ,QObject *parent)
    : QSortFilterProxyModel(parent), m_currentPage(0), m_pageSize(39),m_ID(ID)
{
}

void PaginatedProxyModel::setPage(int page, int pageSize)
{
    // 参数验证
    if (pageSize <= 0) pageSize = 10;

    // 计算有效的页面范围
    int maxPage = getTotalPages() /*- 1*/;
    if (maxPage < 0)
        maxPage = 0;

    //判断是否是空页
    if(page > maxPage)
        m_isEmpty = true;
    else
        m_isEmpty = false;
    page = qBound(0, page, maxPage);


    bool changed = (m_currentPage != page || m_pageSize != pageSize);

    m_currentPage = page;
    m_pageSize = pageSize;

    if (changed) {
        // 触发重新过滤，这会调用 filterAcceptsRow()
        invalidateFilter();
        emit pageChanged(m_currentPage);

        // 调试输出
//        QPair<int, int> range = getRowRange();
//        qDebug() << QString("页面切换: 第%1页 (每页%2行) -> 显示源行 %3-%4")
//                    .arg(m_currentPage + 1)
//                    .arg(m_pageSize)
//                    .arg(range.first + 1)
//                    .arg(range.second + 1);
    }
}

int PaginatedProxyModel::getTotalPages() const
{
    if (!sourceModel() || m_pageSize <= 0) return 0;

    int totalRows = sourceModel()->rowCount();
    return (totalRows + m_pageSize - 1) / m_pageSize; // 数学技巧向上取整
}

QPair<int, int> PaginatedProxyModel::getRowRange() const
{
    int startRow = m_currentPage * m_pageSize;
    int endRow = startRow + m_pageSize - 1;

    // 确保不超出数据范围
    if (sourceModel()) {
        int totalRows = sourceModel()->rowCount();
        endRow = qMin(endRow, totalRows - 1);
    }

    return qMakePair(startRow, endRow);
}

// 【核心函数】决定源模型的哪一行可以在视图中显示
bool PaginatedProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    Q_UNUSED(sourceParent)

    // 获取当前页面应该显示的行范围
    QPair<int, int> range = getRowRange();


    // 如果是空白页面，不显示任何行
        if (m_isEmpty) {
            return false;
        }

    // 判断当前行是否在显示范围内
    bool accept = (sourceRow >= range.first && sourceRow <= range.second);

//    // 调试输出
//    if (sourceRow < 20) {
//        qDebug() << QString("过滤检查: 源行%1, 范围[%2-%3], 结果=%4")
//                    .arg(sourceRow)
//                    .arg(range.first)
//                    .arg(range.second)
//                    .arg(accept ? "显示" : "隐藏");
//    }

    return accept;
}
