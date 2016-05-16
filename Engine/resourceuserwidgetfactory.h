#ifndef RESOURCEUSERWIDGETFACTORY_H
#define RESOURCEUSERWIDGETFACTORY_H
#include "engine_global.h"

#include "iresourcewidgetfactory.h"
#include "userresourcewrapper.h"
#include "istringbuilder.h"
#include "idatabasestate.h"


namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ResourceUserWidgetFactory : public IResourceWidgetFactory
    {
        Q_OBJECT
        IStringBuilder *StringBulder;
        IDatabaseState *DatabaseState;

    public:
        explicit ResourceUserWidgetFactory(QObject *parent = 0);
        virtual IResourceWidget * CreateObject();
        void SetStringBuilder(IStringBuilder * val);
        void SetDatabaseState(IDatabaseState *DatabaseState);
        IStringBuilder * GetStringBuilder();
    signals:

    public slots:

    };
}

#endif // RESOURCEUSERWIDGETFACTORY_H
