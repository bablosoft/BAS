#ifndef ANTIGATECAPTCHASOLVER_H
#define ANTIGATECAPTCHASOLVER_H
#include "engine_global.h"


#include "isolver.h"
#include "ihttpclientfactory.h"
#include "posttoantigate.h"
#include <QTimer>
#include <QMap>

namespace BrowserAutomationStudioFramework
{

    class SingleIdWorker : public QObject
    {
      Q_OBJECT
      public:
          QString id;
          QString antigate_id;
          IHttpClient * client;
          QTimer* timer;
    };

    class ENGINESHARED_EXPORT AntigateCaptchaSolver : public ISolver
    {
        Q_OBJECT
        QString key;
        IHttpClientFactory * HttpClientFactory;
        IHttpClient * HttpClient;
        QHash<QString,QString> IdToAntigateIdList;
        QList<SingleIdWorker*> Workers;
        bool StartedMonitor;
        int Iterator;
        QTimer timer;
        int timeout;
        QString Server;
        QString SoftId;
        void StartMonitor();
        bool MultipleIds;
    public:
        explicit AntigateCaptchaSolver(QObject *parent = 0);

    signals:
    public slots:
        void SetServer(const QString& Server);
        void SetSoftId(const QString& SoftId);
        virtual QString Solve(const QString& base64,const QStringList& props);
        virtual void ReportBad(const QString& id);
        virtual bool TimeLimited();
        void SetHttpClientFactory(IHttpClientFactory * HttpClientFactory);
        void SetMultipleIds(bool MultipleIds);
        IHttpClientFactory * GetHttpClientFactory();

    private slots:
        void DeleteSender();
        void StartIteration();
        void StartSingleIteration();
        void DoneIteration();
        void DoneSignleIteration();
        void PostedToAntigate(const QString& antigate_id, const QString& id, bool res);
    };
}
#endif // ANTIGATECAPTCHASOLVER_H
