#ifndef TABLEWIDGE3D_H
#define TABLEWIDGE3D_H

#include <QWidget>
#include <QTableWidget>
#include <QtDataVisualization/q3dbars.h>
using namespace QtDataVisualization;

class TableWidge3D : public QWidget
{
    Q_OBJECT
public:
    explicit TableWidge3D(QWidget *parent = nullptr);

    void setupModel();
    void addRow();
    void setupCleanView();
signals:


private:

    Q3DBars * m_graph;
    QWidget *container;
    QTableWidget *m_tableWidget;

};

#endif // TABLEWIDGE3D_H
