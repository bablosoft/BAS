#ifndef CURLEXECUTOR_H
#define CURLEXECUTOR_H

#include <QObject>
#include "QtCUrl.h"
#include "curlwrapper.h"
#include <QThread>
#include "engine_global.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT CurlExecutor : public QObject
    {
        Q_OBJECT
        QtCUrl::Options Options;
        CurlWrapper * Curl;

        bool Result;
        QString FileName;
        QByteArray Data;
        QThread* Thread;
        QString Filter;
        QByteArray Log;
        bool UseExternalThread;

    public:
        explicit CurlExecutor(QObject *parent = 0);
        void SetThread(QThread *Thread);
        void SetFilename(const QString& FileName);
        void Execute();
        ~CurlExecutor();
        QtCUrl::Options* GetOptions();
        bool GetResult();
        QByteArray GetDataByteArray();
        QByteArray GetLogByteArray();
        void SetFilter(const QString& Filter);


    signals:
        void Done();
        void StartCurl();
        void StopCurl();

    public slots:
        void Stop();
    private slots:
        void DoneWrapper(bool Result,const QByteArray& Data, const QByteArray& Log);

    };
}

#endif // CURLEXECUTOR_H
