#ifndef WORKERSETTINGS_H
#define WORKERSETTINGS_H
#include "engine_global.h"
#include "iworkersettings.h"
#include <QObject>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT WorkerSettings : public IWorkerSettings
    {
        Q_OBJECT

        QString PathSafe;
        QString PathNotSafe;
        bool IsSafe;
        bool UseFlash;
        int SkipFrames;
        bool RefreshConnections;
        bool EncodeUtf8;

    public:
        explicit WorkerSettings(QObject *parent = 0);

        virtual void SetWorkerPathSafe(const QString& PathSafe);
        virtual void SetWorkerPathNotSafe(const QString& PathNotSafe);
        virtual void SetIsSafe(bool IsSafe);
        virtual void SetUseFlash(bool UseFlash);
        virtual void SetSkipFrames(int SkipFrames);
        virtual void SetRefreshConnections(bool RefreshConnections);
        virtual void SetEncodeUtf8(bool EncodeUtf8);

        virtual QString GetWorkerPathSafe();
        virtual QString GetWorkerPathNotSafe();
        virtual QString GetWorkerPath();

        virtual bool GetIsSafe();
        virtual bool GetUseFlash();
        virtual int GetSkipFrames();
        virtual bool GetRefreshConnections();
        virtual bool GetEncodeUtf8();

        virtual IWorkerSettings* Clone();
        virtual void ParseFromSettings(QSettings& Settings);
        virtual void Change(const QString& JsonString, bool& NeedRestart,bool& NeedSend);
        virtual QStringList GetCommandLineParameters();

    signals:

    public slots:

    };
}

#endif // WORKERSETTINGS_H
