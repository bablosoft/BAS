QT       -= gui
TARGET = moduledll
TEMPLATE = lib
SOURCES += moduledll.cpp \
    GeoIP.c \
    GeoIP_deprecated.c \
    GeoIPCity.c \
    pread.c \
    regionName.c \
    timeZone.c \
    timezoneoffset.c \
    tmap.cpp
HEADERS += moduledll.h \
    GeoIP.h \
    GeoIP_internal.h \
    GeoIPCity.h \
    pread.h \
    tmap.h
LIBS += -lWs2_32

