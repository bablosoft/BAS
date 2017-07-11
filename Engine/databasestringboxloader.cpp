#include "databasestringboxloader.h"
#include <QTimer>
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    DatabaseStringBoxLoader::DatabaseStringBoxLoader(QObject *parent) :
        IStringBoxLoader(parent)
    {
        IsWaitingForLoadRetry = false;
    }

    void DatabaseStringBoxLoader::SetDatabaseConnector(IDatabaseConnector *DatabaseConnector)
    {
        this->Connector = DatabaseConnector;
    }

    void DatabaseStringBoxLoader::SetCsvHelper(ICsvHelper *CsvHelper)
    {
        this->CsvHelper = CsvHelper;
    }

    void DatabaseStringBoxLoader::Load()
    {
        if(IsWaitingForLoadRetry)
            return;
        LoadRetries = 5;
        LoadInternal();
    }

    void DatabaseStringBoxLoader::LoadInternal()
    {
        IsWaitingForLoadRetry = false;
        DatabaseSelector Selector;
        Selector.TableId = TableId;
        DatabaseGroups DbGroups;
        DbGroups.IsNull = false;
        DbGroups.GroupIdList = Groups;
        Selector.Groups = DbGroups;
        QList<DatabaseItem> ResData = Connector->Select(Selector);
        QStringList res;
        if(Connector->WasError())
        {
            if(LoadRetries<0)
            {
                emit DataLoadedCompletely();
                return;
            }else
            {
                LoadRetries--;
                QTimer::singleShot(50,this,SLOT(LoadInternal()));
                IsWaitingForLoadRetry = true;
                return;
            }
        }

        foreach(DatabaseItem item, ResData)
        {
            QStringList line;

            if(Columns.empty() || Columns.size() == 1 && Columns[0] == 0)
            {
                Columns.clear();
                for(DatabaseColumn &c: Connector->GetColumns(TableId))
                {
                    Columns.append(c.Id);
                }
            }

            foreach(int ColumnId, Columns)
            {
                line.append(item.Data[ColumnId].toString());
            }
            line.append(item.Id);

            QString Line = CsvHelper->Generate(line,':');
            res.append(Line);
        }

        if(!res.isEmpty())
            emit Loaded(res);
        emit DataLoadedCompletely();
    }

    void DatabaseStringBoxLoader::ItemDeleted(const QString& item)
    {
        QStringList items = CsvHelper->Parse(item);
        if(!items.isEmpty())
        {
            QString id = items.last();

            DatabaseItems Items;
            Items.IsNull = false;
            Items.IsInverseSelection = false;
            QSet<QString> sr = QSet<QString>()<<id;
            Items.SelectedRows = sr;


            DatabaseGroups GroupIds;
            GroupIds.IsNull = true;

            DatabaseFilters Filters;
            Filters.IsNull = true;

            DatabaseMassSelector Selector;
            Selector.Filters = Filters;
            Selector.TableId = TableId;
            Selector.Items = Items;
            Selector.Groups = GroupIds;


            Connector->Delete(Selector);
        }

    }

    void DatabaseStringBoxLoader::SetGroups(const QStringList& Groups)
    {
        this->Groups = Groups;
    }

    void DatabaseStringBoxLoader::SetTableId(int TableId)
    {
        this->TableId = TableId;
    }
    void DatabaseStringBoxLoader::SetColumns(const QList<int>& Columns)
    {
        this->Columns = Columns;
    }
}
