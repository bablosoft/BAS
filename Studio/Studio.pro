# -------------------------------------------------
# Project created by QtCreator 2013-10-21T14:43:07
# -------------------------------------------------

QT += script \
    network \
    xml

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
    DEFINES += HAVE_QT5
}

DEFINES += NO_BAS_DEBUG

#DEFINES += MEMORY_DEBUG
#SOURCES += debug_memory/debug_new.cpp
TARGET = BrowserAutomationStudio
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    compilewindow.cpp \
    compiler.cpp \
    recentswidget.cpp \
    singleapplication.cpp \
    databasestatedialog.cpp


INCLUDEPATH += debug_memory


HEADERS += mainwindow.h \
    compilewindow.h \
    compiler.h \
    every_cpp.h \
    recentswidget.h \
    singleapplication.h \
    databasestatedialog.h

FORMS += mainwindow.ui \
    compilewindow.ui \
    recentswidget.ui \
    databasestatedialog.ui

RESOURCES += \
    studio.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Engine/release/ -lEngine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Engine/debug/ -lEngine
else:unix: LIBS += -L$$OUT_PWD/../Engine/ -lEngine

win32:RC_FILE = main.rc
INCLUDEPATH += $$PWD/../Engine
DEPENDPATH += $$PWD/../Engine

TRANSLATIONS = translate/ru.ts \
    translate/en.ts

OTHER_FILES += \
    translate/en.ts \
    translate/ru.ts

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
}

LIBS += -lqscintilla2

win32:LIBS += -llibcurl

win32:LIBS += -lUser32

win32:LIBS += -llibeay32 -lssleay32

QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01

INCLUDEPATH += $(BAS_PATH)/include
LIBS += -L$(BAS_PATH)/lib
