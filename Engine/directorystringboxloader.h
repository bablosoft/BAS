#ifndef DIRECTORYSTRINGBOXLOADER_H
#define DIRECTORYSTRINGBOXLOADER_H
#include "engine_global.h"
#include "istringboxloader.h"
#include <QStringList>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT DirectoryStringBoxLoader : public IStringBoxLoader
    {
        Q_OBJECT
        QString DirectoryName;
        QString DirectoryMask;
    public:
        void SetDirectoryName(const QString& DirectoryName);
        void SetDirectoryMask(const QString& DirectoryMask);
        explicit DirectoryStringBoxLoader(QObject *parent = 0);

    signals:

    public slots:
        void ItemDeleted(const QString& item);
        void Load();
    };
}

#endif // DIRECTORYSTRINGBOXLOADER_H
