#ifndef RESOURCEDESIGNWIDGETFACTORY_H
#define RESOURCEDESIGNWIDGETFACTORY_H
#include "engine_global.h"

#include "iresourcewidgetfactory.h"
#include "designresourcewrapper.h"
#include "istringbuilder.h"
#include "idatabasestate.h"

namespace BrowserAutomationStudioFramework
{
class ENGINESHARED_EXPORT ResourceDesignWidgetFactory : public IResourceWidgetFactory
{
    Q_OBJECT
    IStringBuilder *StringBulder;
    IDatabaseState *DatabaseState;
public:
    explicit ResourceDesignWidgetFactory(QObject *parent = 0);
    IStringBuilder * GetStringBuilder();
    void SetStringBuilder(IStringBuilder * val);
    void SetDatabaseState(IDatabaseState *DatabaseState);
    virtual IResourceWidget * CreateObject();
signals:

public slots:

};
}
#endif // RESOURCEDESIGNWIDGETFACTORY_H
