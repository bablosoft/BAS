#ifndef ISTRINGBOXPROXY_H
#define ISTRINGBOXPROXY_H
#include "engine_global.h"

#include <QObject>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IStringBoxProxy : public QObject
    {
        Q_OBJECT
    public:
        explicit IStringBoxProxy(QObject *parent = 0);

    signals:
        void DataLoaded(QStringList &list);
        void DataLoadedCompletely();
        void NeedToUpdate();
    public slots:
        virtual void Load() = 0;
        virtual void Reload() = 0;
        virtual void ReloadOnDemad() = 0;
    };
}

#endif // ISTRINGBOXPROXY_H
