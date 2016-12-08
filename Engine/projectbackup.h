#ifndef PROJECTBACKUP_H
#define PROJECTBACKUP_H
#include "engine_global.h"
#include <QTimer>

namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT ProjectBackup : public QObject
    {
        Q_OBJECT
        int milliseconds;
        QString DestFolder;
        QTimer* Timer;
    public:
        explicit ProjectBackup(QObject *parent = 0);

        void SetPeriod(int milliseconds);
        void SetDestFolder(const QString& DestFolder);

        void Start();
    signals:
        void Backup(QString);
    private slots:
        void DoBackups();
    };
}

#endif // PROJECTBACKUP_H
