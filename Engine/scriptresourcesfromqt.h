#ifndef SCRIPTRESOURCESFROMQT_H
#define SCRIPTRESOURCESFROMQT_H
#include "engine_global.h"

#include "iscriptresources.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ScriptResourcesFromQt : public IScriptResources
    {
    Q_OBJECT
        QString GetFromRes(const QString & res);
    public:
        explicit ScriptResourcesFromQt(QObject *parent = 0);

    signals:

    public slots:
        virtual QString GetJquery();
        virtual QList<QString> GetJqueryPlugins();
        virtual QList<QString> GetEngineScripts();
        virtual QList<QString> GetMultiEngineScripts();
        virtual QList<QString> GetPageScripts();
    };
}
#endif // SCRIPTRESOURCESFROMQT_H
