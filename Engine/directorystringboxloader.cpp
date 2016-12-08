#include "directorystringboxloader.h"
#include <QDir>
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{

    DirectoryStringBoxLoader::DirectoryStringBoxLoader(QObject *parent) :
        IStringBoxLoader(parent)
    {
    }

    void DirectoryStringBoxLoader::SetDirectoryName(const QString& DirectoryName)
    {
        this->DirectoryName = DirectoryName;

    }

    void DirectoryStringBoxLoader::SetDirectoryMask(const QString& DirectoryMask)
    {
        this->DirectoryMask = DirectoryMask;
    }

    void DirectoryStringBoxLoader::Load()
    {
        QDir dir(DirectoryName);
        QStringList list;
        list = dir.entryList(DirectoryMask.split(";"),QDir::Files | QDir::NoDotAndDotDot);
        int len = list.length();
        for(int i = 0;i<len;i++)
        {
            list[i] = dir.absoluteFilePath(list[i]);
        }

        emit Loaded(list);
        emit DataLoadedCompletely();
    }

    void DirectoryStringBoxLoader::ItemDeleted(const QString& item)
    {
        QFile file(item);
        file.remove();
    }
}
