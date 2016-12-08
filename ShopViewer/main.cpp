#include "mainwindow.h"
#include <QApplication>
#include <QWebEngineProfile>
#include "basschemehandler.h"
#include <windows.h>

int main(int argc, char *argv[])
{
    SetErrorMode(SetErrorMode(0) | SEM_NOGPFAULTERRORBOX);

    QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL );

    QApplication a(argc, argv);
    QWebEngineProfile* defaultProfile = QWebEngineProfile::defaultProfile();
    defaultProfile->setPersistentCookiesPolicy(QWebEngineProfile::ForcePersistentCookies);
    defaultProfile->setCachePath("profile");
    defaultProfile->setPersistentStoragePath("profile");
    defaultProfile->installUrlSchemeHandler("bas", new BasSchemeHandler());


    MainWindow w;
    w.show();

    return a.exec();
}
