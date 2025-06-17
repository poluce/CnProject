#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "dialwidget.h"
#include "tablewidge3d.h"
#include "bottommessageview.h"
#include "tab2view.h"
#include "myusepage.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_activated(int index);

private:
    void m_initDailWidget();
    void m_initHistoryWidget();
    void m_initTab2View();
    void m_initNavigationBar();

private:
    Ui::Widget *ui;
    DialWidget * m_Dial;
    TableWidge3D * m_BatteryStack;
    BottomMessageView * m_history;
    Tab2View * m_tab2View;
    UsePage * m_navigationBar;
};
#endif // WIDGET_H
