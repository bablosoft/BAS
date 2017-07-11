TEMPLATE = app
CONFIG += windows
CONFIG -= app_bundle
CONFIG -= qt

DEFINES+=CURL_STATICLIB

DEFINES+=NOT_BAS_DEBUG

QMAKE_LFLAGS += /LARGEADDRESSAWARE

SOURCES += main.cpp \
    mainapp.cpp \
    mainhandler.cpp \
    pipesclient.cpp \
    log.cpp \
    commandparser.cpp \
    proxydata.cpp \
    xml_encoder.cpp \
    devtoolshandler.cpp \
    cookievisitor.cpp \
    converter.cpp \
    match.cpp \
    base64.cpp \
    browserdata.cpp \
    v8handler.cpp \
    javascriptextensions.cpp \
    elementcommand.cpp \
    browsereventsemulator.cpp \
    toolboxhandler.cpp \
    mainlayout.cpp \
    scenariohandler.cpp \
    toolboxv8handler.cpp \
    scenariov8handler.cpp \
    inspectresult.cpp \
    variablesextractor.cpp \
    extract_functions.cpp \
    png/lodepng.cpp \
    settings.cpp \
    translate.cpp \
    curlresourcehandler.cpp \
    trim.cpp \
    split.cpp \
    readallfile.cpp \
    multithreading.cpp \
    modulesdata.cpp \
    toolboxpreprocessor.cpp \
    replaceall.cpp \
    convertencoding.cpp \
    extract_resources.cpp \
	handlersmanager.cpp \
    centralhandler.cpp \
    centralv8handler.cpp \
    clipboard.cpp \
    startwith.cpp \
    processlocation.cpp \
    urlnormalize.cpp \
    chromecommandlineparser.cpp \
    randomid.cpp \
    CrashHandler.cpp \
    localstoragedata.cpp \
    fixpagecontent.cpp \
    fontreplace.cpp \
    snappy/snappy.cc \
    snappy/snappy-c.cc \
    snappy/snappy-sinksource.cc \
    snappy/snappy-stubs-internal.cc \
    extract_labels.cpp \
    postmanager.cpp \
    highlightresult.cpp \
    imagefinder.cpp \
    writefile.cpp

INCLUDEPATH += $(BAS_PATH_WORKER)/include


LIBS += -L$(BAS_PATH_WORKER)/lib -llibiconv -llibcef -llibcef_dll_wrapper -lAdvapi32 -luser32 -lPsapi -lshell32 -lDbgHelp -lgdi32 -llibcurl -llibeay32 -lssleay32 -lnetwork-uri
win32:LIBS += -lminhook
win32:LIBS += -lMsimg32


QMAKE_CXXFLAGS_RELEASE += /MT

QMAKE_CXXFLAGS_DEBUG += /MTd

HEADERS += \
    mainapp.h \
    mainhandler.h \
    pipesclient.h \
    log.h \
    commandparser.h \
    processcheck.h \
    proxydata.h \
    xml_encoder.h \
    devtoolshandler.h \
    cookievisitor.h \
    converter.h \
    json/picojson.h \
    match.h \
    base64.h \
    browserdata.h \
    v8handler.h \
    elementcommand.h \
    javascriptextensions.h \
    browsereventsemulator.h \
    resource.h \
    toolboxhandler.h \
    mainlayout.h \
    scenariohandler.h \
    toolboxv8handler.h \
    scenariov8handler.h \
    inspectresult.h \
    variablesextractor.h \
    extract_functions.h \
    png/lodepng.h \
    settings.h \
    translate.h \
    curlresourcehandler.h \
    opensslmultithreaded.h \
    trim.h \
    split.h \
    readallfile.h \
    refcountpublic.h \
    multithreading.h \
    modulesdata.h \
    toolboxpreprocessor.h \
    replaceall.h \
    convertencoding.h \
    extract_resources.h \
	centralhandler.h \
    handlersmanager.h \
    centralv8handler.h \
    clipboard.h \
    startwith.h \
    processlocation.h \
    urlnormalize.h \
    chromecommandlineparser.h \
    randomid.h \
    CrashHandler.h \
    configurableitem.h \
    localstoragedata.h \
    fixpagecontent.h \
    fontreplace.h \
    snappy/snappy.h \
    snappy/snappy-c.h \
    snappy/snappy-internal.h \
    snappy/snappy-sinksource.h \
    snappy/snappy-stubs-internal.h \
    snappy/snappy-stubs-public.h \
    extract_labels.h \
    postmanager.h \
    highlightresult.h \
    imagefinder.h \
    writefile.h

INCLUDEPATH += xml json png snappy

win32:RC_FILE = main.rc

win32:LIBS += -lopencv_core320 -lopencv_imgproc320 -lzlib

DISTFILES += \
    main.rc

QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
