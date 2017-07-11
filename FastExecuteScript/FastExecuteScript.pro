#-------------------------------------------------
#
# Project created by QtCreator 2013-11-13T05:28:16
#
#-------------------------------------------------

QT      += script \
    network \
    xml

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
    DEFINES += HAVE_QT5
}


TARGET = FastExecuteScript
TEMPLATE = app

DEFINES += NONE_X64 NO_BAS_DEBUG

#DEFINES += MEMORY_DEBUG
#SOURCES += debug_memory/debug_new.cpp


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h


FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Engine/release/ -lEngine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Engine/debug/ -lEngine
else:unix: LIBS += -L$$OUT_PWD/../Engine/ -lEngine

win32:RC_FILE = main.rc
INCLUDEPATH += $$PWD/../Engine
DEPENDPATH += $$PWD/../Engine

RESOURCES += \
    execute.qrc

TRANSLATIONS = translate/ru.ts \
    translate/en.ts

OTHER_FILES += \
    translate/ru.qm \
    translate/en.qm \
    translate/ru.ts \
    translate/en.ts

INCLUDEPATH += debug_memory

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

win32:LIBS += -llibcurl

win32:LIBS += -llibeay32 -lssleay32 -lAdvapi32

QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01


contains(DEFINES, ENIGMA_PROTECTED) {
        win32:LIBS += -lenigma
}


INCLUDEPATH += $(BAS_PATH)/include
LIBS += -L$(BAS_PATH)/lib
