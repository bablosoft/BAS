#ifndef IRESOURCEHANDLERS_H
#define IRESOURCEHANDLERS_H
#include "engine_global.h"

#include <QObject>
#include "iresourcehandler.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IResourceHandlers : public QObject
    {
        Q_OBJECT

    public:
        explicit IResourceHandlers(QObject *parent = 0);

    signals:

    public slots:
        virtual void AddHandler(IResourceHandler *handler) = 0;
        virtual void Die() = 0;
        virtual void Success() = 0;
        virtual void Fail() = 0;
    private slots:

    };
}

#endif // IRESOURCEHANDLERS_H
