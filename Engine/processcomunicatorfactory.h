#ifndef PROCESSCOMUNICATORFACTORY_H
#define PROCESSCOMUNICATORFACTORY_H
#include "engine_global.h"

#include "iprocesscomunicatorfactory.h"
#include <QStringList>
#include <QLocalServer>
#include <QHash>
#include "snappystringcompress.h"
#include <memory>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ProcessComunicatorFactory : public IProcessComunicatorFactory
    {
        Q_OBJECT
        QStringList Params;
        QLocalServer *Server;
        SnappyStringCompress *Compress;

        struct LocalServerDataClass
        {
            QString key;
            QByteArray data;
        };
        using LocalServerData = std::shared_ptr<LocalServerDataClass>;
        QHash<QLocalSocket *,LocalServerData> Sockets;
        QHash<QString,QString>ToSend;
        QLocalSocket * FindLocalServerByKey(const QString& Key);

    public:
        explicit ProcessComunicatorFactory(QObject *parent = 0);
        //Should contain %keyin% %keyout% %pid%
        void SetCommandLineParams(const QStringList& Params);
        virtual IProcessComunicator * CreateProcessComunicator();
    signals:
        void ProcessComunicatorCreated(IProcessComunicator *);
        void Received(const QString& key, const QString& data);
        void KeyStart(const QString& key);
        void SocketStoped(const QString& key);
    private slots:
        void NewConnection();
        void Send(const QString& key, const QString& data);
        void Income();
        void Finished();


    };
}

#endif // PROCESSCOMUNICATORFACTORY_H
