#ifndef ISCRIPTRESOURCES_H
#define ISCRIPTRESOURCES_H
#include "engine_global.h"

#include <QObject>
#include <QList>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IScriptResources : public QObject
    {
    Q_OBJECT
    public:
        explicit IScriptResources(QObject *parent = 0);

    signals:

    public slots:
        virtual QString GetJquery() = 0;
        virtual QList<QString> GetJqueryPlugins() = 0;
        virtual QList<QString> GetEngineScripts() = 0;
        virtual QList<QString> GetMultiEngineScripts() = 0;
        virtual QList<QString> GetPageScripts() = 0;
    };
}
#endif // ISCRIPTRESOURCES_H
