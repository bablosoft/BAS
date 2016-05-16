#ifndef FILESTRINGBOXLOADER_H
#define FILESTRINGBOXLOADER_H
#include "engine_global.h"
#include "istringboxloader.h"
#include <QStringList>
#include <QFile>
#include <QTextStream>


namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT FileStringBoxLoader : public IStringBoxLoader
    {
        Q_OBJECT
        QString FileName;
        QStringList list;
        QStringList ToRemove;

        QFile *CurrentFile;
        qint64 CurrentStreamPosition;
        QStringList CurrentFileList;
        int CurrentFileListIterator;
        bool WaitingForNewPortionReuqest;

        bool LoadFile(const QString& file);
        void CleanFile(const QString& file);
    public:

        explicit FileStringBoxLoader(QObject *parent = 0);
        ~FileStringBoxLoader();

    signals:

    public slots:
        void SetFileName(const QString& FileName);
        virtual void Load();
        void ItemDeleted(const QString& item);
    private slots:
        void CleanUp();
    };
}

#endif // FILESTRINGBOXLOADER_H
