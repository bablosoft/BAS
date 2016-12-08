QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RemoteExecuteScript
TEMPLATE = app

DEFINES += QUAZIP_STATIC

win32:RC_FILE = main.rc

INCLUDEPATH += $(BAS_PATH)/include
LIBS += -L$(BAS_PATH)/lib

SOURCES += main.cpp\
    httpclient.cpp \
    ihttpclient.cpp \
    ipostpreparestrategy.cpp \
    ipostpreparestrategyfactory.cpp \
    postpreparestrategymultipart.cpp \
    postpreparestrategyurlencode.cpp \
    networkcookiejar.cpp \
    downloadingwidget.cpp \
    zip/JlCompress.cpp \
    zip/qioapi.cpp \
    zip/quaadler32.cpp \
    zip/quacrc32.cpp \
    zip/quagzipfile.cpp \
    zip/quaziodevice.cpp \
    zip/quazip.cpp \
    zip/quazipdir.cpp \
    zip/quazipfile.cpp \
    zip/quazipfileinfo.cpp \
    zip/quazipnewinfo.cpp \
    zip/unzip.c \
    zip/zip.c \
    remote.cpp

HEADERS  += \
    httpclient.h \
    ihttpclient.h \
    ipostpreparestrategy.h \
    ipostpreparestrategyfactory.h \
    postpreparestrategyfactory.h \
    postpreparestrategymultipart.h \
    postpreparestrategyurlencode.h \
    networkcookiejar.h \
    downloadingwidget.h \
    zip/crypt.h \
    zip/ioapi.h \
    zip/JlCompress.h \
    zip/quaadler32.h \
    zip/quachecksum32.h \
    zip/quacrc32.h \
    zip/quagzipfile.h \
    zip/quaziodevice.h \
    zip/quazip.h \
    zip/quazip_global.h \
    zip/quazipdir.h \
    zip/quazipfile.h \
    zip/quazipfileinfo.h \
    zip/quazipnewinfo.h \
    zip/unzip.h \
    zip/zip.h \
    remote.h

FORMS    += \
    downloadingwidget.ui

RESOURCES += \
    main.qrc

INCLUDEPATH += zip

win32:LIBS += -lzlib

win32 {
    QMAKE_LFLAGS += /SUBSYSTEM:CONSOLE,5.01
    QMAKE_CXX += /D_USING_V110_SDK71_
    LIBS *= -L"%ProgramFiles(x86)%/Microsoft SDKs/Windows/7.1A/Lib"
    INCLUDEPATH += "%ProgramFiles(x86)%/Microsoft SDKs/Windows/7.1A/Include"
}
