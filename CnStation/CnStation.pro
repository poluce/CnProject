QT       += core gui datavisualization charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    batterycell.cpp \
    batterymessage.cpp \
    batterystackview.cpp \
    bottommessageview.cpp \
    chargmessage.cpp \
    dialwidget.cpp \
    main.cpp \
    myusepage.cpp \
    paginatedproxymodel.cpp \
    realtimedataview.cpp \
    runingmessage.cpp \
    signalhub.cpp \
    splineview.cpp \
    tab2view.cpp \
    tab3view.cpp \
    tableviewdelegate.cpp \
    tablewidge3d.cpp \
    tabmessage.cpp \
    widget.cpp

HEADERS += \
    WidgetType.h \
    batterycell.h \
    batterymessage.h \
    batterystackview.h \
    bottommessageview.h \
    chargmessage.h \
    dialwidget.h \
    myusepage.h \
    paginatedproxymodel.h \
    realtimedataview.h \
    runingmessage.h \
    signalhub.h \
    splineview.h \
    tab2view.h \
    tab3view.h \
    tableviewdelegate.h \
    tablewidge3d.h \
    tabmessage.h \
    widget.h

FORMS += \
    batterystackview.ui \
    bottommessageview.ui \
    chargmessage.ui \
    myusepage.ui \
    realtimedataview.ui \
    runingmessage.ui \
    splineview.ui \
    tabmessage.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qss.qrc
