#include "signalhub.h"

SignalHub::SignalHub(QObject *parent) : QObject(parent)
{

}

SignalHub &SignalHub::instance()
{
    static SignalHub hub;

    return hub;
}

void SignalHub::postMsg(MySignal::WidgetType fromID, QVariant msg)
{
    emit msgArrived(fromID,msg);
}



