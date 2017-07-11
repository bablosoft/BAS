#ifndef DATABASESTRINGBOXLOADER_H
#define DATABASESTRINGBOXLOADER_H

#include "engine_global.h"
#include "istringboxloader.h"
#include "idatabaseconnector.h"
#include "icsvhelper.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT DatabaseStringBoxLoader : public IStringBoxLoader
    {
        Q_OBJECT
        IDatabaseConnector * Connector;
        ICsvHelper * CsvHelper;
        QStringList Groups;
        QList<int> Columns;
        int TableId;
        int LoadRetries;
        bool IsWaitingForLoadRetry;
    public:
        explicit DatabaseStringBoxLoader(QObject *parent = 0);
        void SetDatabaseConnector(IDatabaseConnector *DatabaseConnector);
        void SetGroups(const QStringList& Groups);
        void SetTableId(int TableId);
        void SetColumns(const QList<int>& Columns);
        void SetCsvHelper(ICsvHelper *CsvHelper);
    signals:

    public slots:
        virtual void Load();
        void LoadInternal();
        void ItemDeleted(const QString& item);

    };
}

#endif // DATABASESTRINGBOXLOADER_H
