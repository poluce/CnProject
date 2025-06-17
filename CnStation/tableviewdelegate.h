#ifndef TABLEVIEWDELEGATE_H
#define TABLEVIEWDELEGATE_H

#include <QWidget>
#include <QStyledItemDelegate>
#include "batterycell.h"

class TableViewDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TableViewDelegate(QWidget *parent = nullptr);
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
signals:

};

#endif // TABLEVIEWDELEGATE_H
