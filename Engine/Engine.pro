#-------------------------------------------------
#
# Project created by QtCreator 2013-11-12T15:00:28
#
#-------------------------------------------------

QT       += script \
    network \
    xml \
    svg

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
    DEFINES += HAVE_QT5
}


TARGET = Engine
TEMPLATE = lib

DEFINES += ENGINE_LIBRARY QSCINTILLA_DLL QUAZIP_BUILD NO_BAS_DEBUG
DEFINES += IS_X64


#DEFINES += MEMORY_DEBUG
#SOURCES += debug_memory/debug_new.cpp

SOURCES += engine.cpp \
    xmlresourcecontroller.cpp \
    vocabularytest.cpp \
    userresourcewrapper.cpp \
    userresourcewidget.cpp \
    timeoutwaiterfactory.cpp \
    timeoutwaiter.cpp \
    stringresourcehandler.cpp \
    stringbuilder.cpp \
    stringboxproxy.cpp \
    stringboxperiodicalloader.cpp \
    stringbox.cpp \
    solverfactory.cpp \
    skincontroller.cpp \
    singlecaptchawidget.cpp \
    scriptworkerfactory.cpp \
    scriptworker.cpp \
    scriptresourcesfromqt.cpp \
    scriptmultiworker.cpp \
    resourceuserwidgetfactory.cpp \
    resources.cpp \
    resourcemodelurl.cpp \
    resourcemodelselect.cpp \
    resourcemodelrandomstring.cpp \
    resourcemodelrandominteger.cpp \
    resourcemodelfixedstring.cpp \
    resourcemodelfixedinteger.cpp \
    resourcemodelfile.cpp \
    resourcemodeldirectory.cpp \
    resourcemodelabstract.cpp \
    resourcehandlersfactory.cpp \
    resourcehandlers.cpp \
    resourcehandlerabstract.cpp \
    resourcedesignwidgetfactory.cpp \
    qtresourcecontroller.cpp \
    posttoantigate.cpp \
    plaintextlogger.cpp \
    manualcaptchasolver.cpp \
    iworkerfactory.cpp \
    iworker.cpp \
    iwebelement.cpp \
    iwaiterfactory.cpp \
    iwaiter.cpp \
    istringbuilder.cpp \
    istringboxproxy.cpp \
    istringboxloader.cpp \
    istringbox.cpp \
    isolverfactory.cpp \
    isolver.cpp \
    iskincontroller.cpp \
    iscriptresources.cpp \
    iresourcewidgetfactory.cpp \
    iresourcewidget.cpp \
    iresources.cpp \
    iresourcemodel.cpp \
    iresourcehandlersfactory.cpp \
    iresourcehandlers.cpp \
    iresourcehandler.cpp \
    iresourcecontroller.cpp \
    integerresourcehandler.cpp \
    imultiworker.cpp \
    ilogger.cpp \
    ihttpclientfactory.cpp \
    ihttpclient.cpp \
    iengineresources.cpp \
    iengineresource.cpp \
    ibrowserfactory.cpp \
    ibrowser.cpp \
    httpclientfactory.cpp \
    httpclient.cpp \
    flowlayout.cpp \
    filestringboxloader.cpp \
    engineresourcestringbox.cpp \
    engineresources.cpp \
    engineresourcerandomstring.cpp \
    engineresourcerandominteger.cpp \
    engineresourcefixedstring.cpp \
    engineresourcefixedinteger.cpp \
    engineresourcecontroller.cpp \
    designresourcewrapper.cpp \
    designresourcewidget.cpp \
    designchooserresourcewidget.cpp \
    chooserresourcewidget.cpp \
    askuserforresourcesdialog.cpp \
    antigatecaptchasolver.cpp \
    iprocesscomunicator.cpp \
    sharedmemoryprocesscomunicator.cpp \
    waiterconnector.cpp \
    ipreprocessor.cpp \
    preprocessor.cpp \
    inetworkaccessmanager.cpp \
    networkaccessmanager.cpp \
    inetworkaccessmanagerfactory.cpp \
    networkaccessmanagerfactory.cpp \
    networkaccessmanagercapture.cpp \
    subprocessbrowser.cpp \
    subprocessbrowserfactory.cpp \
    subprocessnetworkaccessmanager.cpp \
    subprocessnetworkaccessmanagerfactory.cpp \
    iprocesscomunicatorfactory.cpp \
    processcomunicatorfactory.cpp \
    subprocesswebelement.cpp \
    subprocesslistwidget.cpp \
    pipesprocesscomunicator.cpp \
    additionalsettingswidgets.cpp \
    urlstringboxloader.cpp \
    directorystringboxloader.cpp \
    emptystringboxloader.cpp \
    resourcemodelscript.cpp \
    copyresourcecontroller.cpp \
    outputsection.cpp \
    outputwidget.cpp \
    filelogger.cpp \
    complexlogger.cpp \
    ExtendedTabWidget.cpp \
    multiselect.cpp \
    dragsection.cpp \
    dragwidget.cpp \
    isystemtraynotifier.cpp \
    systemtraynotifier.cpp \
    toprightpositioner.cpp \
    iversioninfo.cpp \
    versioninfo.cpp \
    aboutbrowserstudio.cpp \
    iscriptsuspender.cpp \
    scriptsuspender.cpp \
    networkcookiejar.cpp \
    enterlicensedialog.cpp \
    outputwidgetconfigurator.cpp \
    iscriptmultiworkerreportdata.cpp \
    scriptmultiworkerreportdata.cpp \
    ireportdatavisualizer.cpp \
    reportdatavisualizer.cpp \
    reportdatavisualizerdialog.cpp \
    ihelper.cpp \
    helper.cpp \
    languagechooserdevelopmentwidget.cpp \
    ilanguagemodel.cpp \
    languagemodel.cpp \
    multilanguagetextbox.cpp \
    multilanguagestring.cpp \
    scriptlanguagechooserdialog.cpp \
    itranslator.cpp \
    translator.cpp \
    periodicalhttprequest.cpp \
    ipop3client.cpp \
    pop3client.cpp \
    mail/mailattachment.cpp \
    mail/mailhmac.cpp \
    mail/mailmessage.cpp \
    mail/mailpop3.cpp \
    mail/mailpop3reply.cpp \
    mail/mailsmtp.cpp \
    ipop3clientfactory.cpp \
    pop3clientfactory.cpp \
    engineresourceabstract.cpp \
    browserpluginpath.cpp \
    ipostpreparestrategy.cpp \
    postpreparestrategymultipart.cpp \
    ipostpreparestrategyfactory.cpp \
    postpreparestrategyfactory.cpp \
    postpreparestrategyurlencode.cpp \
    htmlparser.cpp \
    curlwrapper.cpp \
    curlexecutor.cpp \
    iimapclient.cpp \
    imapclient.cpp \
    QtCUrl.cpp \
    iimapclientfactory.cpp \
    imapclientfactory.cpp \
    classcomboboxfillpictures.cpp \
    extendedtabwidgetvalidator.cpp \
    generalvalidator.cpp \
    ivalidator.cpp \
    advancedhider.cpp \
    basscintilla.cpp \
    textfinderwidget.cpp \
    ihelperfactory.cpp \
    helperfactory.cpp \
    ihtmlparser.cpp \
    ihtmlparserfactory.cpp \
    htmlparserfactory.cpp \
    imemoryinfo.cpp \
    memoryinfo.cpp \
    uprng.cpp \
    debugterminate.cpp \
    safeapplication.cpp \
    loglocationchooser.cpp \
    iresourcewatcher.cpp \
    stringboxwatcher.cpp \
    iresourcesvisualizer.cpp \
    resourcesvisualizer.cpp \
    iencryptor.cpp \
    noneencryptor.cpp \
    iproperties.cpp \
    properties.cpp \
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
    curlhttpclient.cpp \
    openlinksfromfilesystem.cpp \
    itimerproxy.cpp \
    qtimerproxy.cpp \
    multitimer.cpp \
    multitimerproxy.cpp \
    idatabaseconnector.cpp \
    databaseadmin.cpp \
    databasegroupwidget.cpp \
    databaseadmindeletegroup.cpp \
    databaseadmineditgroup.cpp \
    databaseadmintable.cpp \
    databaseadminitemedit.cpp \
    databaseadminitemmodificationdialog.cpp \
    databaseadminmovetogroup.cpp \
    databaseadminrowtoolbox.cpp \
    mongodatabaseconnector.cpp \
    databaseadminfilterwidget.cpp \
    databaseadminfilteritem.cpp \
    databaseadminfiltercreate.cpp \
    icsvhelper.cpp \
    csvhelper.cpp \
    databaseadmincsvformat.cpp \
    qxtcheckcombobox.cpp \
    idatabasestate.cpp \
    databasestate.cpp \
    resourcemodeldatabase.cpp \
    databasestringboxloader.cpp \
    csvhelperwrapper.cpp \
    irecordprocesscommunication.cpp \
    recordprocesscommunication.cpp \
    icodeeditor.cpp \
    scintillacodeeditor.cpp \
    plaincodeeditor.cpp \
    splifyheaders.cpp \
    imodulemanager.cpp \
    modulemanager.cpp \
    modulemanagerwindow.cpp \
    accordion/clickableframe.cpp \
    accordion/contentpane.cpp \
    accordion/qaccordion.cpp \
    projectbackup.cpp \
    addavexclusion.cpp \
    postpreparestrategyjsonencode.cpp \
    postpreparestrategycustomencode.cpp \
    diff/diff_match_patch.cpp \
    idiffpatcher.cpp \
    diffpatcher.cpp \
    snappy/snappy.cc \
    snappy/snappy-c.cc \
    snappy/snappy-sinksource.cc \
    snappy/snappy-stubs-internal.cc \
    istringcompress.cpp \
    snappystringcompress.cpp \
    idatabaseconnectionwindow.cpp \
    databaseconnectionwindow.cpp \
    databaseconnectiondialog.cpp \
    databaseschemaeditordialog.cpp \
    idatabaseschemaeditor.cpp \
    databaseschemaeditor.cpp \
    databaseschemaeditorcolumndialog.cpp \
    itabblink.cpp \
    mainwindowtabblink.cpp \
    substagemanager.cpp \
    iconstructresource.cpp \
    constructresourcewizard.cpp \
    resourcewizard.cpp \
    uiconstructor.cpp \
    tabinputdialog.cpp \
    iworkersettings.cpp \
    workersettings.cpp

win32:SOURCES += CrashHandler.cpp

HEADERS += engine.h\
        engine_global.h \
    xmlresourcecontroller.h \
    vocabularytest.h \
    userresourcewrapper.h \
    userresourcewidget.h \
    timeoutwaiterfactory.h \
    timeoutwaiter.h \
    stringresourcehandler.h \
    stringbuilder.h \
    stringboxproxy.h \
    stringboxperiodicalloader.h \
    stringbox.h \
    solverfactory.h \
    skincontroller.h \
    singlecaptchawidget.h \
    scriptworkerfactory.h \
    scriptworker.h \
    scriptresourcesfromqt.h \
    scriptmultiworker.h \
    resourceuserwidgetfactory.h \
    resources.h \
    resourcemodelurl.h \
    resourcemodelselect.h \
    resourcemodelrandomstring.h \
    resourcemodelrandominteger.h \
    resourcemodelfixedstring.h \
    resourcemodelfixedinteger.h \
    resourcemodelfile.h \
    resourcemodeldirectory.h \
    resourcemodelabstract.h \
    resourcehandlersfactory.h \
    resourcehandlers.h \
    resourcehandlerabstract.h \
    resourcedesignwidgetfactory.h \
    qtresourcecontroller.h \
    posttoantigate.h \
    plaintextlogger.h \
    manualcaptchasolver.h \
    iworkerfactory.h \
    iworker.h \
    iwebelement.h \
    iwaiterfactory.h \
    iwaiter.h \
    istringbuilder.h \
    istringboxproxy.h \
    istringboxloader.h \
    istringbox.h \
    isolverfactory.h \
    isolver.h \
    iskincontroller.h \
    iscriptresources.h \
    iresourcewidgetfactory.h \
    iresourcewidget.h \
    iresources.h \
    iresourcemodel.h \
    iresourcehandlersfactory.h \
    iresourcehandlers.h \
    iresourcehandler.h \
    iresourcecontroller.h \
    integerresourcehandler.h \
    imultiworker.h \
    ilogger.h \
    ihttpclientfactory.h \
    ihttpclient.h \
    iengineresources.h \
    iengineresource.h \
    ibrowserfactory.h \
    ibrowser.h \
    httpclientfactory.h \
    httpclient.h \
    flowlayout.h \
    filestringboxloader.h \
    engineresourcestringbox.h \
    engineresources.h \
    engineresourcerandomstring.h \
    engineresourcerandominteger.h \
    engineresourcefixedstring.h \
    engineresourcefixedinteger.h \
    engineresourcecontroller.h \
    designresourcewrapper.h \
    designresourcewidget.h \
    designchooserresourcewidget.h \
    chooserresourcewidget.h \
    askuserforresourcesdialog.h \
    antigatecaptchasolver.h \
    iprocesscomunicator.h \
    sharedmemoryprocesscomunicator.h \
    waiterconnector.h \
    ipreprocessor.h \
    preprocessor.h \
    inetworkaccessmanager.h \
    networkaccessmanager.h \
    inetworkaccessmanagerfactory.h \
    networkaccessmanagerfactory.h \
    networkaccessmanagercapture.h \
    subprocessbrowser.h \
    subprocessbrowserfactory.h \
    subprocessnetworkaccessmanager.h \
    subprocessnetworkaccessmanagerfactory.h \
    iprocesscomunicatorfactory.h \
    processcomunicatorfactory.h \
    subprocesswebelement.h \
    subprocesslistwidget.h \
    pipesprocesscomunicator.h \
    additionalsettingswidgets.h \
    urlstringboxloader.h \
    directorystringboxloader.h \
    emptystringboxloader.h \
    resourcemodelscript.h \
    copyresourcecontroller.h \
    outputsection.h \
    outputwidget.h \
    filelogger.h \
    complexlogger.h \
    ExtendedTabWidget.h \
    multiselect.h \
    dragsection.h \
    dragwidget.h \
    isystemtraynotifier.h \
    systemtraynotifier.h \
    toprightpositioner.h \
    iversioninfo.h \
    versioninfo.h \
    aboutbrowserstudio.h \
    iscriptsuspender.h \
    scriptsuspender.h \
    networkcookiejar.h \
    enterlicensedialog.h \
    outputwidgetconfigurator.h \
    iscriptmultiworkerreportdata.h \
    scriptmultiworkerreportdata.h \
    ireportdatavisualizer.h \
    reportdatavisualizer.h \
    reportdatavisualizerdialog.h \
    ihelper.h \
    helper.h \
    languagechooserdevelopmentwidget.h \
    ilanguagemodel.h \
    languagemodel.h \
    multilanguagetextbox.h \
    multilanguagestring.h \
    scriptlanguagechooserdialog.h \
    itranslator.h \
    translator.h \
    periodicalhttprequest.h \
    ipop3client.h \
    pop3client.h \
    mail/mailattachment.h \
    mail/mailglobal.h \
    mail/mailhmac.h \
    mail/mailmessage.h \
    mail/mailpop3_p.h \
    mail/mailpop3.h \
    mail/mailpop3listreply.h \
    mail/mailpop3reply_p.h \
    mail/mailpop3reply.h \
    mail/mailpop3retrreply.h \
    mail/mailpop3statreply.h \
    mail/mailsmtp_p.h \
    mail/mailsmtp.h \
    mail/mailutility_p.h \
    ipop3clientfactory.h \
    pop3clientfactory.h \
    engineresourceabstract.h \
    browserpluginpath.h \
    ipostpreparestrategy.h \
    postpreparestrategymultipart.h \
    ipostpreparestrategyfactory.h \
    postpreparestrategyfactory.h \
    postpreparestrategyurlencode.h \
    htmlparser.h \
    curlwrapper.h \
    curlexecutor.h \
    iimapclient.h \
    imapclient.h \
    QtCUrl.h \
    iimapclientfactory.h \
    imapclientfactory.h \
    classcomboboxfillpictures.h \
    extendedtabwidgetvalidator.h \
    generalvalidator.h \
    ivalidator.h \
    advancedhider.h \
    basscintilla.h \
    textfinderwidget.h \
    ihelperfactory.h \
    helperfactory.h \
    ihtmlparser.h \
    ihtmlparserfactory.h \
    htmlparserfactory.h \
    imemoryinfo.h \
    memoryinfo.h \
    uprng.h \
    debugterminate.h \
    safeapplication.h \
    loglocationchooser.h \
    iresourcewatcher.h \
    stringboxwatcher.h \
    iresourcesvisualizer.h \
    resourcesvisualizer.h \
    iencryptor.h \
    noneencryptor.h \
    iproperties.h \
    properties.h \
    zip/crypt.h \
    zip/ioapi.h \
    zip/JlCompress.h \
    zip/quaadler32.h \
    zip/quachecksum32.h \
    zip/quacrc32.h \
    zip/quagzipfile.h \
    zip/quaziodevice.h \
    zip/quazip_global.h \
    zip/quazip.h \
    zip/quazipdir.h \
    zip/quazipfile.h \
    zip/quazipfileinfo.h \
    zip/quazipnewinfo.h \
    zip/unzip.h \
    zip/zip.h \
    curlhttpclient.h \
    openlinksfromfilesystem.h \
    every_cpp.h \
    itimerproxy.h \
    qtimerproxy.h \
    multitimer.h \
    multitimerproxy.h \
    idatabaseconnector.h \
    DatabaseConnectorHelperClass.h \
    databaseadmin.h \
    databasegroupwidget.h \
    databaseadmindeletegroup.h \
    databaseadmineditgroup.h \
    databaseadmintable.h \
    databaseadminitemedit.h \
    databaseadminitemmodificationdialog.h \
    databaseadminmovetogroup.h \
    databaseadminrowtoolbox.h \
    mongodatabaseconnector.h \
    databaseadminfilterwidget.h \
    databaseadminfilteritem.h \
    databaseadminfiltercreate.h \
    icsvhelper.h \
    csvhelper.h \
    databaseadmincsvformat.h \
    qxtcheckcombobox.h \
    idatabasestate.h \
    databasestate.h \
    resourcemodeldatabase.h \
    databasestringboxloader.h \
    csvhelperwrapper.h \
    irecordprocesscommunication.h \
    recordprocesscommunication.h \
    icodeeditor.h \
    scintillacodeeditor.h \
    plaincodeeditor.h \
    splifyheaders.h \
    imodulemanager.h \
    modulemanager.h \
    modulemanagerwindow.h \
    accordion/qAccordion/clickableframe.h \
    accordion/qAccordion/contentpane.h \
    accordion/qAccordion/qaccordion.h \
    projectbackup.h \
    addavexclusion.h \
    postpreparestrategyjsonencode.h \
    postpreparestrategycustomencode.h \
    diff/diff_match_patch.h \
    idiffpatcher.h \
    diffpatcher.h \
    snappy/snappy.h \
    snappy/snappy-c.h \
    snappy/snappy-internal.h \
    snappy/snappy-sinksource.h \
    snappy/snappy-stubs-internal.h \
    snappy/snappy-stubs-public.h \
    istringcompress.h \
    snappystringcompress.h \
    idatabaseconnectionwindow.h \
    databaseconnectionwindow.h \
    databaseconnectiondialog.h \
    databaseschemaeditordialog.h \
    idatabaseschemaeditor.h \
    databaseschemaeditor.h \
    databaseschemaeditorcolumndialog.h \
    itabblink.h \
    mainwindowtabblink.h \
    substagemanager.h \
    iconstructresource.h \
    constructresourcewizard.h \
    resourcewizard.h \
    uiconstructor.h \
    tabinputdialog.h \
    iworkersettings.h \
    workersettings.h

win32:HEADERS += CrashHandler.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

RESOURCES += \
    engine.qrc

FORMS += \
    vocabularytest.ui \
    userresourcewidget.ui \
    singlecaptchawidget.ui \
    designresourcewidget.ui \
    designchooserresourcewidget.ui \
    chooserresourcewidget.ui \
    browserlistwidget.ui \
    askuserforresourcesdialog.ui \
    subprocesslistwidget.ui \
    outputwidget.ui \
    aboutbrowserstudio.ui \
    enterlicensedialog.ui \
    outputwidgetconfigurator.ui \
    reportdatavisualizerdialog.ui \
    languagechooserdevelopmentwidget.ui \
    multilanguagetextbox.ui \
    scriptlanguagechooserdialog.ui \
    textfinderwidget.ui \
    loglocationchooser.ui \
    databaseadmin.ui \
    databasegroupwidget.ui \
    databaseadmindeletegroup.ui \
    databaseadmineditgroup.ui \
    databaseadmintable.ui \
    databaseadminitemedit.ui \
    databaseadminitemmodificationdialog.ui \
    databaseadminmovetogroup.ui \
    databaseadminrowtoolbox.ui \
    databaseadminfilterwidget.ui \
    databaseadminfilteritem.ui \
    databaseadminfiltercreate.ui \
    databaseadmincsvformat.ui \
    modulemanagerwindow.ui \
    databaseconnectiondialog.ui \
    databaseschemaeditordialog.ui \
    databaseschemaeditorcolumndialog.ui \
    resourcewizard.ui \
    uiconstructor.ui \
    tabinputdialog.ui

OTHER_FILES += \
    scripts/pages.js \
    scripts/multi.js \
    scripts/jquery.js \
    scripts/engine.js \
    images/stop.png \
    images/stop_small.png \
    images/enter.png \
    images/edit.png \
    images/at_sign.png \
    scripts/browser/jquery.plugins.js \
    scripts/browser/jquery.js \
    scripts/browser/helpers.js \
    scripts/engine/common/translit.js \
    scripts/engine/common/helpers.js \
    scripts/engine/common/cycles.js \
    scripts/engine/multiworker/resources.js \
    scripts/engine/multiworker/multi.js \
    scripts/engine/multiworker/flow.js \
    scripts/engine/worker/worker.js \
    scripts/engine/worker/waiters.js \
    scripts/engine/worker/resources.js \
    scripts/engine/worker/flow.js \
    scripts/engine/worker/cache.js \
    scripts/browser/extend.js \
    scripts/engine/worker/httpclient.js \
    translate/ru.ts \
    translate/en.ts \
    scripts/engine/worker/pop3client.js \
    scripts/engine/common/html_parser.js \
    scripts/engine/common/rss_parser.js \
    scripts/engine/worker/imapclient.js \
    text/apilist.txt \
    scripts/engine/common/memory.js \
    scripts/engine/multiworker/properties.js \
    scripts/engine/worker/properties.js \
    scripts/engine/worker/record.js \
    scripts/engine/worker/images.js


INCLUDEPATH += zip debug_memory accordion diff snappy

TRANSLATIONS = translate/ru.ts \
    translate/en.ts

unix{
    INCLUDEPATH += /usr/include/libxml2
    LIBS += -lcurl
    INCLUDEPATH += $$_PRO_FILE_PWD_/../../../dep/include
    LIBS += -L$$_PRO_FILE_PWD_/../../../dep/lib
}

win32:LIBS += -llibxml2
LIBS += -lqscintilla2

LIBS += -llibmimetic

win32:LIBS += -lws2_32 -liconv -llibcurl -lzlib -lShell32

QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01

INCLUDEPATH += $(BAS_PATH)/include
LIBS += -L$(BAS_PATH)/lib
