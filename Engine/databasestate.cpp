#include "databasestate.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    DatabaseState::DatabaseState(QObject *parent) :
        IDatabaseState(parent)
    {
    }


    QList<DatabaseTable> DatabaseState::GetDatabaseTables()
    {
        return Tables;
    }
    QList<DatabaseColumn> DatabaseState::GetColumns(int TableId)
    {
        if(!Columns.contains(TableId))
            return QList<DatabaseColumn>();
        return Columns.value(TableId);
    }
    QList<DatabaseGroup> DatabaseState::GetGroups(int TableId)
    {
        if(!Groups.contains(TableId))
            return QList<DatabaseGroup>();
        return Groups.value(TableId);
    }

    void DatabaseState::SetDatabaseConnector(IDatabaseConnector *DatabaseConnector)
    {
        this->DatabaseConnector = DatabaseConnector;
    }

    void DatabaseState::Reload()
    {
        Tables = DatabaseConnector->GetTables();
        Columns.clear();
        Groups.clear();
        foreach(DatabaseTable Table, Tables)
        {
            Columns[Table.Id] = DatabaseConnector->GetColumns(Table.Id);
            Groups[Table.Id] = DatabaseConnector->GetGroups(Table.Id);
        }
        emit GroupsChanged();
    }
}
