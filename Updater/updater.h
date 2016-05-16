#ifndef UPDATER_H
#define UPDATER_H

#include <QObject>
#include <QTimer>
#include "updateprogress.h"
#include "httpclient.h"

class Updater : public QObject
{
    Q_OBJECT
    bool CanSkip;
    UpdateProgress *Progress;
    QString GetLocalVersion();
    QString MaxVersion(const QStringList& Dirs);
    HttpClient *Client;
    QString CurrentVersion;
    QTimer *Timer;
    QString AppReference;
    QString RemoteVersion;
    QStringList Arguments;
public:
    explicit Updater(QObject *parent = 0);
    bool Start(const QStringList& Arguments);
signals:

public slots:
private slots:
    void Skip();
    void Update();
    void DownloadFinished();
    void DownloadProgress(qint64,qint64);
    void DoneLatestQuery();

};

#endif // UPDATER_H
