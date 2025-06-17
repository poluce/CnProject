#ifndef WIDGETTYPE_H
#define WIDGETTYPE_H

#include <QObject>

namespace MySignal {
Q_NAMESPACE                 // 为整个命名空间生成元对象

enum class WidgetType : uint8_t {
    Navigation_first,
    Navigation_pre,
    Navigation_next,
    Navigation_last,
    Navigation_topage,


};
Q_ENUM_NS(WidgetType)       // 在命名空间级别登记
}


#endif // WIDGETTYPE_H
