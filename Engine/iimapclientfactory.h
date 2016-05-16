#ifndef IIMAPCLIENTFACTORY_H
#define IIMAPCLIENTFACTORY_H

#include <QObject>
#include "iimapclient.h"
#include "engine_global.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IImapClientFactory : public QObject
    {
        Q_OBJECT
    public:
        explicit IImapClientFactory(QObject *parent = 0);
        virtual IImapClient * GetImapClient() = 0;
    signals:

    public slots:

    };
}

#endif // IIMAPCLIENTFACTORY_H
