#ifndef IDATABASECONNECTOR_H
#define IDATABASECONNECTOR_H
#include "engine_global.h"
#include <QObject>
#include "DatabaseConnectorHelperClass.h"
#include "icsvhelper.h"
#include "idatabaseconnectionwindow.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT  IDatabaseConnector : public QObject
    {
        Q_OBJECT
    public:


        explicit IDatabaseConnector(QObject *parent = 0);
        virtual bool HasDatabase() = 0;
        virtual QStringList SelectFormatted(DatabaseSelector Selector,QString Format) = 0;
        virtual QList<DatabaseItem> Select(DatabaseSelector Selector) = 0;
        virtual QString Insert(DatabaseGroups Groups,DatabaseItem Item, int TableId) = 0;
        virtual int Count(DatabaseSelector Selector) = 0;
        virtual void Delete(DatabaseMassSelector Selector) = 0;
        virtual void Update(DatabaseItem Item, int TableId) = 0;

        virtual QList<DatabaseGroup> GetGroups(int TableId) = 0;
        virtual void UpdateGroup(const DatabaseGroup& Group, int TableId) = 0;
        virtual QString InsertGroup(const DatabaseGroup& Group, int TableId) = 0;
        virtual void MoveToGroup(DatabaseMassSelector Selector, QString NewGroupId) = 0;
        virtual void CopyToGroup(DatabaseMassSelector Selector, QString NewGroupId) = 0;
        virtual void DeleteFromAllGroups(DatabaseMassSelector Selector) = 0;

        virtual void DeleteGroupNoData(DatabaseGroups GroupIds, int TableId) = 0;
        virtual void DeleteGroupWithData(DatabaseGroups GroupIds, int TableId) = 0;
        virtual void ClearGroup(DatabaseGroups GroupIds, int TableId) = 0;
        virtual void DeleteAll() = 0;

        virtual QString CopyGroup(const DatabaseGroup& NewGroup, int TableId, QString OriginalGroupId) = 0;

        virtual bool WasError() = 0;
        virtual QString GetError() = 0;

        virtual QList<DatabaseTable> GetTables() = 0;
        virtual QList<DatabaseColumn> GetColumns(int TableId) = 0;

        virtual void SetCsvHelper(ICsvHelper * CsvHelper) = 0;
        virtual void ExportCsv(const QString& File, QList<int> ColumnIds, DatabaseMassSelector Selector) = 0;
        virtual void ExportExcel(const QString& File, QList<int> ColumnIds, DatabaseMassSelector Selector) = 0;

        virtual void ImportCsv(const QString& File, QList<int> ColumnIds, QString GroupId, int TableId) = 0;

        virtual bool IsConnected() = 0;

        virtual QStringList ShowBackupList() = 0;
        virtual void Backup() = 0;
        virtual void Restore(const QString& BackupLabel) = 0;

        virtual void SetDatabaseConnectionWindow(IDatabaseConnectionWindow * DatabaseConnectionWindow) = 0;

        virtual DatabaseFilters ParseFilter(const QString& JsonFilters) = 0;

    signals:
        void Started();
        void BackupOrRestoreFinished();
        void GroupManipulated();
    public slots:

    };
}
#endif // IDATABASECONNECTOR_H
