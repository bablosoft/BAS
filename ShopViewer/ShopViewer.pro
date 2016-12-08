#-------------------------------------------------
#
# Project created by QtCreator 2016-11-20T23:28:11
#
#-------------------------------------------------

QT       += core gui webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShopViewer
TEMPLATE = app

win32:RC_FILE = main.rc


SOURCES += main.cpp\
        mainwindow.cpp \
    basschemehandler.cpp


HEADERS  += mainwindow.h \
    basschemehandler.h

FORMS    += mainwindow.ui

RESOURCES += \
    main.qrc

win32 {
    QMAKE_LFLAGS += /SUBSYSTEM:CONSOLE,5.01
    QMAKE_CXX += /D_USING_V110_SDK71_
    LIBS *= -L"%ProgramFiles(x86)%/Microsoft SDKs/Windows/7.1A/Lib"
    INCLUDEPATH += "%ProgramFiles(x86)%/Microsoft SDKs/Windows/7.1A/Include"
}
