#ifndef IRESOURCEHANDLER_H
#define IRESOURCEHANDLER_H
#include "engine_global.h"

#include <QObject>
#include <QScriptValue>
#include <QHash>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IResourceHandler : public QObject
    {
        Q_OBJECT
    public:
        explicit IResourceHandler(QObject *parent = 0);
        enum HandlerStatus{Ready = 0,Wait = 1,NotAvailable = 2, Refused = 3};

    signals:
        void SuccessSignal();
        void FailSignal();
        void DieSignal();
        void UpdateSignal(const QStringList& data);
        void PurgeSignal();

    public slots:
        virtual QScriptValue get() = 0;



        virtual void success() = 0;
        virtual void fail() = 0;
        virtual void die() = 0;
        virtual void purge() = 0;
        virtual void update(const QStringList& data) = 0;

        virtual HandlerStatus GetHandlerStatus() = 0;
        virtual void SetHandlerStatus(HandlerStatus status) = 0;
    };
}

#endif // IRESOURCEHANDLER_H
