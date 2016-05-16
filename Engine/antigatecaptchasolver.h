#ifndef ANTIGATECAPTCHASOLVER_H
#define ANTIGATECAPTCHASOLVER_H
#include "engine_global.h"


#include "isolver.h"
#include "ihttpclientfactory.h"
#include "posttoantigate.h"
#include <QTimer>

namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT AntigateCaptchaSolver : public ISolver
    {
        Q_OBJECT
        QString key;
        IHttpClientFactory * HttpClientFactory;
        IHttpClient * HttpClient;
        QHash<QString,QString> IdToAntigateIdList;
        bool StartedMonitor;
        int Iterator;
        QTimer timer;
        int timeout;
        QString Server;
        void StartMonitor();
        bool is_russian;

    public:
        explicit AntigateCaptchaSolver(QObject *parent = 0);

    signals:
        void Done(const QString& val, const QString& id, bool res);
    public slots:
        void SetServer(const QString& Server);
        virtual QString Solve(const QString& base64);
        virtual bool TimeLimited();
        virtual void SetProperty(const QString& name,const QString& value);
        void SetHttpClientFactory(IHttpClientFactory * HttpClientFactory);
        IHttpClientFactory * GetHttpClientFactory();

    private slots:
        void StartIteration();
        void DoneIteration();
        void PostedToAntigate(const QString& antigate_id, const QString& id, bool res);
    };
}
#endif // ANTIGATECAPTCHASOLVER_H
