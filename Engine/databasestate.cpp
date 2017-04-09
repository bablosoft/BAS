#include "databasestate.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    DatabaseState::DatabaseState(QObject *parent) :
        IDatabaseState(parent)
    {
    }

    QString DatabaseState::ToJson()
    {
        QJsonArray ta;
        for(DatabaseTable &t:Tables)
        {
            QJsonObject to;
            to["name"] = t.Name;
            to["description"] = t.Description;
            to["id"] = t.Id;

            QJsonArray ca;

            for(DatabaseColumn &c:GetColumns(t.Id))
            {
                QJsonObject co;
                co["name"] = c.Name;
                co["description"] = c.Description;
                co["id"] = c.Id;
                switch(c.Type)
                {
                    case DatabaseColumn::String: co["type"] = "string"; break;
                    case DatabaseColumn::Int: co["type"] = "int"; break;
                    case DatabaseColumn::Date: co["type"] = "date"; break;
                    case DatabaseColumn::Bool: co["type"] = "bool"; break;
                }
                ca.append(co);
            }
            to["columns"] = ca;


            ta.append(to);

        }

        QJsonDocument doc;
        doc.setArray(ta);
        QString res = doc.toJson();
        return res;
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

