QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    QCustomPlot/qcustomplot.cpp \
    QGraphScroll.cpp \
    main.cpp

HEADERS += \
    QCustomPlot/qcustomplot.h \
    QGraphScroll.h

FORMS += \
    QGraphScroll.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Image.qrc
