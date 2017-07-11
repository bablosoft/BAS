#ifndef SUBPROCESSBROWSERFACTORY_H
#define SUBPROCESSBROWSERFACTORY_H
#include "engine_global.h"

#include "ibrowserfactory.h"
#include "iprocesscomunicatorfactory.h"
#include "subprocesslistwidget.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT SubprocessBrowserFactory : public IBrowserFactory
    {
        Q_OBJECT
        QList<IBrowser*> BrowserList;
        QList<IBrowser*> BrowserListUnused;

        INetworkAccessManagerFactory *NetworkAccessManagerFactory;
        IProcessComunicatorFactory *ProcessComunicatorFactory;
        SubprocessListWidget *Widget;
        QString Language;
    public:
        void SetLanguage(const QString & Language);
        explicit SubprocessBrowserFactory(QObject *parent = 0);
        virtual void ClearAll();
        virtual void Clear(QList<IBrowser*>* Browsers);
        virtual QList<IBrowser*> Create(int size);
        virtual void SetNetworkAccessManager(INetworkAccessManagerFactory *NetworkAccessManagerFactory);
        virtual INetworkAccessManagerFactory * GetNetworkAccessManager();
        void SetProcessComunicatorFactory(IProcessComunicatorFactory *ProcessComunicatorFactory);
        IProcessComunicatorFactory * GetProcessComunicatorFactory();
        QWidget *GetWidget(bool AutoStart);
    signals:

    private slots:
        void ProcessCreated(IProcessComunicator* Comunicator);

    };
}

#endif // SUBPROCESSBROWSERFACTORY_H
