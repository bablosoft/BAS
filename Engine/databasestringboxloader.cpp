#include "databasestringboxloader.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    DatabaseStringBoxLoader::DatabaseStringBoxLoader(QObject *parent) :
        IStringBoxLoader(parent)
    {
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
            emit DataLoadedCompletely();
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
