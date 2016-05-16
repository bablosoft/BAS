#ifndef IRESOURCEWATCHER_H
#define IRESOURCEWATCHER_H

#include "engine_global.h"

#include <QObject>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IResourceWatcher : public QObject
    {
        Q_OBJECT
    public:
        explicit IResourceWatcher(QObject *parent = 0);
        virtual int GetRenewInSeconds() = 0;
        virtual int GetReadyCount() = 0;
        virtual QString GetName() = 0;
        virtual void Disable() = 0;
        virtual bool IsDisabled() = 0;

    signals:

    public slots:

    };
}

#endif // IRESOURCEWATCHER_H
