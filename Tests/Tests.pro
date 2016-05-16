#-------------------------------------------------
#
# Project created by QtCreator 2014-10-15T07:28:07
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_copyresourcestests.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Engine/release/ -lEngine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Engine/debug/ -lEngine
else:unix: LIBS += -L$$OUT_PWD/../Engine/ -lEngine

INCLUDEPATH += $$PWD/../Engine
DEPENDPATH += $$PWD/../Engine

unix{
    INCLUDEPATH += /usr/include/libxml2
    LIBS += -lcurl
    LIBS += -lssl -lcrypto
    INCLUDEPATH += $$_PRO_FILE_PWD_/../../../dep/include
    LIBS += -L$$_PRO_FILE_PWD_/../../../dep/lib
    LIBS += -lmongoclient
    LIBS += -lboost_system
    LIBS += -lboost_thread
    LIBS += -lboost_filesystem
    LIBS += -lqscintilla2
}

INCLUDEPATH += $(BAS_PATH)/include
LIBS += -L$(BAS_PATH)/lib
