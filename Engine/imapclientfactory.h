#ifndef IMAPCLIENTFACTORY_H
#define IMAPCLIENTFACTORY_H

#include "engine_global.h"
#include "iimapclientfactory.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ImapClientFactory : public IImapClientFactory
    {
        Q_OBJECT
    public:
        explicit ImapClientFactory(QObject *parent = 0);
        virtual IImapClient * GetImapClient();
    signals:

    public slots:

    };
}

#endif // IMAPCLIENTFACTORY_H
