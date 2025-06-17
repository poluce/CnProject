#include "widget.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include "dialwidget.h"
#include "tablewidge3d.h"
#include "splineview.h"
#include "bottommessageview.h"
#include "batterymessage.h"
#include "batterycell.h"
#include "tab2view.h"
#include "myusepage.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

//    TableWidge3D d;
//    d.show();

//    SplineView s;
//    s.show();

//    BottomMessageView v;
//    v.show();

//    BatteryMessage B;
//    B.show();

    //    DialWidget  D;
    //    D.show();


//    //电池单体
//    BatteryCell B;
//    B.show();

    //第二页小组件
//    Tab2View T;
//    T.show();

    //导航栏小组件
//    UsePage U;
//    U.show();

    QFile file(":/new.qss");
    file.open(QFile::ReadOnly);

    a.setStyleSheet(file.readAll());
    file.close();




    return a.exec();
}
