QT       += gui
TARGET = moduledll
TEMPLATE = lib
SOURCES += moduledll.cpp

HEADERS += moduledll.h

INCLUDEPATH += $(BAS_PATH)/include
LIBS += -L$(BAS_PATH)/lib

win32:LIBS += -lopencv_core320 -lopencv_imgproc320 -lzlib

