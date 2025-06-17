#include "tableviewdelegate.h"

#include <QPainter>

TableViewDelegate::TableViewDelegate(QWidget *parent) : QStyledItemDelegate(parent)
{

}

QWidget *TableViewDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    // 根据列或数据类型创建不同的控件
    int column = index.column();
    if(column == 3 )
    {
        BatteryCell *cell = new BatteryCell(parent,QColor("#7af6c0"));
        return  cell;
    }

    else if(column == 4)
    {
        BatteryCell *cell = new BatteryCell(parent);
        return  cell;
    }
    return QStyledItemDelegate::createEditor(parent, option, index);


}

void TableViewDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

    QVariant value = index.data(Qt::EditRole);
    if (BatteryCell *cell = qobject_cast<BatteryCell*>(editor)) {
            cell->setValue(value.toDouble());
            return;
        }

    QStyledItemDelegate::setEditorData(editor, index);
}

void TableViewDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (BatteryCell *cell = qobject_cast<BatteryCell*>(editor))
    {

        model->setData(index, cell->getValue(), Qt::EditRole);

                // 可以同时设置显示数据
        model->setData(index, cell->getValue(), Qt::DisplayRole);
    }
}

void TableViewDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    editor->setGeometry(option.rect);
}

void TableViewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    int column = index.column();

    // SOC和SOH列显示电池
    if (column == 3 || column == 4)
    {
        // 获取数据
        QVariant data = index.data(Qt::DisplayRole);
        bool ok;
        double value = data.toDouble(&ok);

        if (!ok)
        {
            // 如果不是数字，使用默认绘制
            QStyledItemDelegate::paint(painter, option, index);
            return;
        }

        // 如果项目被选中，绘制选中背景
        if (option.state & QStyle::State_Selected)
        {
            painter->fillRect(option.rect, option.palette.highlight());
        }

        // 根据列选择颜色
        QColor batteryColor;
        if (column == 3)
        { // SOC列
            batteryColor = QColor("#7af6c0"); // 绿色
        } else { // SOH列
            batteryColor = QColor("#fcd440"); // 黄色
        }

        // 调用 BatteryCell 的静态绘制函数
        BatteryCell::drawBatteryStatic(painter, option.rect, value, batteryColor);
    }
    else
    {
        // 其他列使用默认绘制
        QStyledItemDelegate::paint(painter, option, index);
    }
}
