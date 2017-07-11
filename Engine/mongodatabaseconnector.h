#ifndef MONGODATABASECONNECTOR_H
#define MONGODATABASECONNECTOR_H
#include "engine_global.h"
#include <QObject>
#include <QMutex>
#include <QMutexLocker>
#include "idatabaseconnector.h"

#ifdef Q_OS_WIN
    #include <winsock2.h>
    #include <windows.h>
#endif
#include "mongo/client/dbclient.h"
#include <QProcess>

using namespace mongo;

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT  MongoDatabaseConnector : public IDatabaseConnector
    {
        Q_OBJECT
        IDatabaseConnectionWindow *DatabaseConnectionWindow;
        ICsvHelper * CsvHelper;
        QSet<int> EnsureIndexTables;
        bool _WasError;
        QString _ErrorString;
        bool IsDatabasePresent;
        QString MongoOutput;
        int Port;
        QProcess *CurrentMongoProcess;
        QProcess *CurrentNetshProcess;
        DBClientConnection _c;
        bool IsBusy;
        QString ConnectionLog;
        QString DatabaseId;
        bool ConnectionIsRemote;
        QString ConnectionServer;
        QString ConnectionPort;
        QString ConnectionLogin;
        QString ConnectionPassword;


        enum ColumnType{String,Int,Bool,Date};
        struct Column{int Id;QString Name;QString Description;ColumnType Type;};
        struct Table{int Id;QString Name;QString Description;QList<Column>Columns;};
        struct Database{QList<Table> Tables;}Schema;

        QString Lang;
        void LoadSchema(const QString& SchemaText);
        BSONObj GenerateDatabaseGroupsQuery(DatabaseGroups Groups);
        BSONObj GenerateDatabaseItemsQuery(DatabaseItems Items);
        BSONObj GenerateFilterQuery(DatabaseFilters Filters);
        BSONObj GenerateDatabaseGroupsAndItemsQuery(DatabaseGroups Groups,DatabaseItems Items);
        BSONObj CombineQueryAnd(BSONObj q1,BSONObj q2);

        void StartServer();
        bool _HasDatabase;

    public:
        explicit MongoDatabaseConnector(QObject *parent);
        ~MongoDatabaseConnector();
        virtual bool HasDatabase();
        virtual QStringList SelectFormatted(DatabaseSelector Selector,QString Format);

        virtual QList<DatabaseItem> Select(DatabaseSelector Selector);
        virtual QString Insert(DatabaseGroups Groups,DatabaseItem Item, int TableId);
        virtual int Count(DatabaseSelector Selector);

        virtual void Update(DatabaseItem Item, int TableId);

        virtual QList<DatabaseGroup> GetGroups(int TableId);
        virtual void UpdateGroup(const DatabaseGroup& Group, int TableId);
        virtual QString InsertGroup(const DatabaseGroup& Group, int TableId);

        virtual void Delete(DatabaseMassSelector Selector);
        void MoveToGroup(DatabaseMassSelector Selector, QString NewGroupId, bool MoveOrCopy);
        virtual void MoveToGroup(DatabaseMassSelector Selector, QString NewGroupId);
        virtual void CopyToGroup(DatabaseMassSelector Selector, QString NewGroupId);
        virtual void DeleteFromAllGroups(DatabaseMassSelector Selector);

        virtual void DeleteGroupNoData(DatabaseGroups GroupIds, int TableId);
        virtual void DeleteGroupWithData(DatabaseGroups GroupIds, int TableId);

        virtual void ClearGroup(DatabaseGroups GroupIds, int TableId);
        virtual void DeleteAll();

        virtual QString CopyGroup(const DatabaseGroup& NewGroup, int TableId, QString OriginalGroupId);

        virtual bool WasError();
        virtual QString GetError();

        virtual QList<DatabaseTable> GetTables();
        virtual QList<DatabaseColumn> GetColumns(int TableId);
        void Init(const QString &Lang);
        bool Start(const QString& SchemaText,const QString& DatabaseId, bool IsRemote, const QString& ConnectionServer, const QString& ConnectionPort, const QString& ConnectionLogin, const QString& ConnectionPassword);
        QString GetDatabaseBaseLocation();
        QString GetDatabaseLocation();



        virtual void SetCsvHelper(ICsvHelper * CsvHelper);
        virtual void ExportCsv(const QString& File, QList<int> ColumnIds, DatabaseMassSelector Selector);
        virtual void ExportExcel(const QString& File, QList<int> ColumnIds, DatabaseMassSelector Selector);
        virtual void ImportCsv(const QString& File, QList<int> ColumnIds, QString GroupId, int TableId);

        virtual bool IsConnected();
        static bool Init();


        virtual QStringList ShowBackupList();
        virtual void Backup();
        virtual void Restore(const QString& BackupLabel);

        virtual void SetDatabaseConnectionWindow(IDatabaseConnectionWindow * DatabaseConnectionWindow);

        virtual DatabaseFilters ParseFilter(const QString& JsonFilters);

    signals:
        //void TerminateProcess();

    private slots:
        void BackupRestoreFinishedSlot(int res);
        void ProcessRead();
        bool EnsureDataDirCreated();
        /*void WriteFirewallException();
        void WriteFirewallException2();*/
        void StartMongoProcess();
        bool TryConnect();
        void MongoServerClosed();
        void TryConnectFinal();

        void StartAnyway();
        void UserCancel();
        void DatabaseConnectionOk();
        void ShowLog();

        void GetPort();
        void ChangePort();
        void ClosePort();
        void SaveMongoPid();
        void MongoProcessTerminate();

    };
}

#endif // MONGODATABASECONNECTOR_H
