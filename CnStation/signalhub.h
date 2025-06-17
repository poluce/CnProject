#ifndef SIGNALHUB_H
#define SIGNALHUB_H

#include <QObject>
#include "WidgetType.h"
#include <QVariant>


class SignalHub : public QObject
{
    Q_OBJECT
public:


    explicit SignalHub(QObject *parent = nullptr);
    static SignalHub& instance();

    //添加反射的支持
    Q_INVOKABLE void postMsg(MySignal::WidgetType fromID,QVariant  msg ={});


signals:
   void msgArrived(MySignal::WidgetType fromID,QVariant msg);



};

#endif // SIGNALHUB_H
