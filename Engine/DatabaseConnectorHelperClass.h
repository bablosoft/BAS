#ifndef DATABASECONNECTORHELPERCLASS_H
#define DATABASECONNECTORHELPERCLASS_H
#include <QList>
#include <QHash>
#include <QDateTime>
#include <QStringList>
#include <QVariant>

#include <QSet>


namespace BrowserAutomationStudioFramework
{

    struct DatabaseGroups
    {
        bool IsNull;
        QStringList GroupIdList;
    };

    struct DatabaseItems
    {
        bool IsNull;
        bool IsInverseSelection;
        QSet<QString> SelectedRows;

    };




    struct DatabaseFilter
    {
        enum {
                StringNotEmpty, StringEmpty, StringContains,
                IntEquals, IntNotEquals, IntGreaterOrEqual,IntGreater,IntLessThan,IntLessThanOrEqual,
                BoolIsTrue,BoolIsFalse,
                DateIsLessThan,DateGreaterThan,DateIsSameYear,DateIsSameMonth,DateIsSameDay,DateIsSameHour
            } Type;
        QVariant Data;
        int ColumnId;
    };

    struct DatabaseFilters
    {
        bool IsNull;
        QList<DatabaseFilter> FilterList;
    };





    struct DatabaseItem
    {
        bool IsNull;
        QString Id;
        QHash<int,QVariant> Data;
    };

    struct DatabasePage
    {
        bool IsNull;
        int PageNumber;
        int PageSize;
    };

    struct DatabaseSort
    {
        bool IsNull;
        int ColumnId;
        bool OrderIsAsc;
    };


    struct DatabaseSelector
    {
        DatabaseGroups Groups;
        DatabaseFilters Filter;
        DatabasePage Page;
        DatabaseSort Sort;
        int TableId;
    };

    struct DatabaseGroup
    {
        bool IsNull;
        QString Id;
        QString Name;
        QString Description;
        QDateTime CreatedAt;
    };

    struct DatabaseTable
    {
        bool IsNull;
        int Id;
        QString Name;
        QString Description;
    };

    struct DatabaseColumn
    {
        enum ColumnType{String,Int,Bool,Date};
        bool IsNull;
        int Id;
        QString Name;
        QString Description;
        ColumnType Type;
    };
    struct DatabaseMassSelector
    {
        DatabaseItems Items;
        DatabaseGroups Groups;
        DatabaseFilters Filters;
        DatabaseSort Sort;
        int TableId;
    };


}
#endif // DATABASECONNECTORHELPERCLASS_H
