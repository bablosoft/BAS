#include "workersettings.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    WorkerSettings::WorkerSettings(QObject *parent) :
        IWorkerSettings(parent)
    {
        IsSafe = true;
        UseFlash = false;
        SkipFrames = 1;
        RefreshConnections = false;
        EncodeUtf8 = true;
    }

    void WorkerSettings::SetWorkerPathSafe(const QString& PathSafe)
    {
        this->PathSafe = PathSafe;
    }
    void WorkerSettings::SetWorkerPathNotSafe(const QString& PathNotSafe)
    {
        this->PathNotSafe = PathNotSafe;
    }
    void WorkerSettings::SetIsSafe(bool IsSafe)
    {
        this->IsSafe = IsSafe;
    }
    void WorkerSettings::SetUseFlash(bool UseFlash)
    {
        this->UseFlash = UseFlash;
    }
    void WorkerSettings::SetSkipFrames(int SkipFrames)
    {
        this->SkipFrames = SkipFrames;
    }
    void WorkerSettings::SetRefreshConnections(bool RefreshConnections)
    {
        this->RefreshConnections = RefreshConnections;
    }
    void WorkerSettings::SetEncodeUtf8(bool EncodeUtf8)
    {
        this->EncodeUtf8 = EncodeUtf8;
    }

    QString WorkerSettings::GetWorkerPathSafe()
    {
        return PathSafe;
    }
    QString WorkerSettings::GetWorkerPathNotSafe()
    {
        return PathNotSafe;
    }
    bool WorkerSettings::GetIsSafe()
    {
        return IsSafe;
    }
    QString WorkerSettings::GetWorkerPath()
    {
        return (IsSafe) ? PathSafe : PathNotSafe;
    }
    bool WorkerSettings::GetUseFlash()
    {
        return UseFlash;
    }
    int WorkerSettings::GetSkipFrames()
    {
        return SkipFrames;
    }
    bool WorkerSettings::GetRefreshConnections()
    {
        return RefreshConnections;
    }
    bool WorkerSettings::GetEncodeUtf8()
    {
        return EncodeUtf8;
    }

    IWorkerSettings* WorkerSettings::Clone()
    {
        WorkerSettings * res = new WorkerSettings();
        res->SetWorkerPathSafe(PathSafe);
        res->SetWorkerPathNotSafe(PathNotSafe);
        res->SetIsSafe(IsSafe);
        res->SetUseFlash(UseFlash);
        res->SetSkipFrames(SkipFrames);
        res->SetRefreshConnections(RefreshConnections);
        res->SetEncodeUtf8(EncodeUtf8);
        return res;
    }

    void WorkerSettings::ParseFromSettings(QSettings& Settings)
    {
        SetIsSafe(Settings.value("IsSafe",true).toBool());
        SetUseFlash(Settings.value("EnableFlash",false).toBool());
        SetSkipFrames(Settings.value("SkipFrames",1).toInt());
        SetRefreshConnections(Settings.value("ProxiesReconnect",false).toBool());
        SetEncodeUtf8(Settings.value("ForceUtf8",true).toBool());
    }

    void WorkerSettings::Change(const QString& JsonString, bool& NeedRestart,bool& NeedSend)
    {
        NeedRestart = false;
        NeedSend = false;

        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(JsonString.toUtf8(), &err);

        if(err.error != QJsonParseError::NoError)
        {
            return;
        }

         QJsonObject object = doc.object();
         if(object.contains("IsSafe"))
         {
            bool prev = GetIsSafe();
            bool next = object["IsSafe"].toBool();
            if(prev != next)
            {
                NeedRestart = true;
                SetIsSafe(next);
            }
         }

         if(object.contains("UseFlash"))
         {
            bool prev = GetUseFlash();
            bool next = object["UseFlash"].toBool();
            if(prev != next)
            {
                NeedRestart = true;
                SetUseFlash(next);
            }
         }

         if(object.contains("SkipFrames"))
         {
            int prev = GetSkipFrames();
            int next = object["SkipFrames"].toInt();
            if(prev != next)
            {
                NeedSend = true;
                SetSkipFrames(next);
            }
         }

         if(object.contains("RefreshConnections"))
         {
            bool prev = GetRefreshConnections();
            bool next = object["RefreshConnections"].toBool();
            if(prev != next)
            {
                NeedSend = true;
                SetRefreshConnections(next);
            }
         }

         if(object.contains("EncodeUtf8"))
         {
            bool prev = GetEncodeUtf8();
            bool next = object["EncodeUtf8"].toBool();
            if(prev != next)
            {
                NeedSend = true;
                SetEncodeUtf8(next);
            }
         }
    }

    QStringList WorkerSettings::GetCommandLineParameters()
    {
        QStringList res;
        res.append("--IsSafe");
        res.append(QString::number(GetIsSafe()));

        res.append("--UseFlash");
        res.append(QString::number(GetUseFlash()));

        res.append("--SkipFrames");
        res.append(QString::number(GetSkipFrames()));

        res.append("--RefreshConnections");
        res.append(QString::number(GetRefreshConnections()));

        res.append("--EncodeUtf8");
        res.append(QString::number(GetEncodeUtf8()));

        return res;

    }


}
