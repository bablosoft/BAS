#include "openlinksfromfilesystem.h"
#include <QTextBrowser>
#include <QFileInfo>
#include <QProcess>
#include <QDir>
#include <QUrlQuery>
#include <QDesktopServices>

#ifdef Q_OS_WIN
    #include <windows.h>
#endif
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    OpenLinksFromFileSystem::OpenLinksFromFileSystem(QObject *parent) :
        QObject(parent)
    {
        QTextBrowser * TextBrowser = qobject_cast<QTextBrowser *>(parent);
        TextBrowser->setOpenExternalLinks(false);
        TextBrowser->setOpenLinks(false);
        connect(TextBrowser,SIGNAL(anchorClicked(QUrl)),this,SLOT(AnchorClicked(QUrl)));
    }
    void OpenLinksFromFileSystem::AnchorClicked(const QUrl & url)
    {
        #ifdef Q_OS_WIN
            if(url.host().contains("shelexecute"))
            {
                QUrlQuery q;
                q.setQuery(url.query());
                QString cmd = q.queryItemValue("cmd",QUrl::FullyDecoded);
                QString arg = q.queryItemValue("arg",QUrl::FullyDecoded);

                LPCWSTR s1 = (LPCWSTR)cmd.utf16();
                LPCWSTR s2 = NULL;
                if(q.hasQueryItem("arg"))
                    s2 = (LPCWSTR)arg.utf16();

                ShellExecute(NULL,NULL,s1,s2,NULL,SW_RESTORE);

            }else
        #endif
        {
            QFileInfo info(url.toString());
            QDesktopServices::openUrl(QUrl::fromLocalFile(info.absoluteFilePath()));

        }

    }
}
