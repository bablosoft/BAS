#ifndef DATABASESTATE_H
#define DATABASESTATE_H

#include <QObject>

#include "engine_global.h"
#include "idatabasestate.h"
#include <QList>
#include <QHash>
#include "idatabaseconnector.h"
namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT DatabaseState : public IDatabaseState
    {
        Q_OBJECT
        QList<DatabaseTable> Tables;
        QHash<int, QList<DatabaseColumn> > Columns;
        QHash<int, QList<DatabaseGroup> > Groups;
        IDatabaseConnector *DatabaseConnector;
    public:
        explicit DatabaseState(QObject *parent = 0);
        virtual QList<DatabaseTable> GetDatabaseTables();
        virtual QList<DatabaseColumn> GetColumns(int TableId);
        virtual QList<DatabaseGroup> GetGroups(int TableId);
        virtual QString ToJson();
        void SetDatabaseConnector(IDatabaseConnector *DatabaseConnector);
    signals:

    public slots:
        void Reload();
    };
}

#endif // DATABASESTATE_H
