#ifndef REMOTE_H
#define REMOTE_H

#include <QObject>
#include <QTimer>
#include "httpclient.h"
#include "downloadingwidget.h"

class Remote : public QObject
{
    Q_OBJECT
    HttpClient *Client;
    QStringList Arguments;
    DownloadingWidget *UI;

    //Errors
    bool IsValid;
    QString ErrorMessage;

    //Initial params
    bool IsX64;
    bool IsSilent;
    bool IsRemote;
    QString ScriptName;
    QString Server;
    QString Username;
    QString Password;


    //Script params
    QString ScriptHash;
    QString EngineVersion;
    bool ForceFree;


public:
    explicit Remote(QObject *parent = 0);
    bool Start(const QStringList& Arguments);
    void DetectSettings();
    void DetectScriptProperties();
    void EnginePrepared();
signals:

public slots:
private slots:
    void Exit();
    void ScriptPropertiesHttpClientResp();
    void ScriptPropertiesDetected(const QString& ScriptHash, const QString& EngineVersion);
    void DownloadProgress(qint64 BytesReceived, qint64 BytesTotal);
    void EngineDownloaded();

};

#endif // REMOTE_H
