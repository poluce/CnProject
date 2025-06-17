#ifndef BOTTOMMESSAGEVIEW_H
#define BOTTOMMESSAGEVIEW_H

#include <QWidget>
#include "splineview.h"
#include "batterymessage.h"
#include "chargmessage.h"

namespace Ui {
class BottomMessageView;
}

class BottomMessageView : public QWidget
{
    Q_OBJECT

public:
    explicit BottomMessageView(QWidget *parent = nullptr);
    ~BottomMessageView();

private:
    Ui::BottomMessageView *ui;
    SplineView * m_curveView;
    BatteryMessage * m_widgetMid;
    ChargMessage * m_widgetRight;

};

#endif // BOTTOMMESSAGEVIEW_H
