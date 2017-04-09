#ifndef IDATABASESTATE_H
#define IDATABASESTATE_H

#include <QObject>

#include "engine_global.h"
#include "DatabaseConnectorHelperClass.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IDatabaseState : public QObject
    {
        Q_OBJECT
    public:
        explicit IDatabaseState(QObject *parent = 0);

        virtual QList<DatabaseTable> GetDatabaseTables() = 0;
        virtual QList<DatabaseColumn> GetColumns(int TableId) = 0;
        virtual QList<DatabaseGroup> GetGroups(int TableId) = 0;
        virtual QString ToJson() = 0;


    signals:
        void GroupsChanged();
    public slots:

    };
}

#endif // IDATABASESTATE_H
