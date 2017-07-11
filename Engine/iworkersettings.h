#ifndef IWORKERSETTINGS_H
#define IWORKERSETTINGS_H

#include "engine_global.h"

#include <QObject>
#include <QSettings>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IWorkerSettings : public QObject
    {
        Q_OBJECT
    public:
        explicit IWorkerSettings(QObject *parent = 0);

        virtual void SetWorkerPathSafe(const QString& PathSafe) = 0;
        virtual void SetWorkerPathNotSafe(const QString& PathNotSafe) = 0;
        virtual void SetIsSafe(bool IsSafe) = 0;
        virtual void SetUseFlash(bool UseFlash) = 0;
        virtual void SetSkipFrames(int SkipFrames) = 0;
        virtual void SetRefreshConnections(bool RefreshConnections) = 0;
        virtual void SetEncodeUtf8(bool EncodeUtf8) = 0;

        virtual QString GetWorkerPathSafe() = 0;
        virtual QString GetWorkerPathNotSafe() = 0;
        virtual QString GetWorkerPath() = 0;
        virtual bool GetIsSafe() = 0;
        virtual bool GetUseFlash() = 0;
        virtual int GetSkipFrames() = 0;
        virtual bool GetRefreshConnections() = 0;
        virtual bool GetEncodeUtf8() = 0;

        virtual IWorkerSettings* Clone() = 0;
        virtual void ParseFromSettings(QSettings& Settings) = 0;
        virtual void Change(const QString& JsonString, bool& NeedRestart,bool& NeedSend) = 0;
        virtual QStringList GetCommandLineParameters() = 0;


    signals:

    public slots:

    };
}

#endif // IWORKERSETTINGS_H
