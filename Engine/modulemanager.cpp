#include "modulemanager.h"
#include <QDir>
#include <QTextStream>
#include <QDirIterator>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonObject>
#include <QLibrary>

#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    ModuleManager::ModuleManager(QObject *parent) :
        IModuleManager(parent)
    {
    }

    ModuleManager::DllData ModuleManager::FindDllData(const QList<DllData> & List, const QString& DllName, int ThreadNumber)
    {
        for(DllData dat:List)
        {
            if(dat->DllName == DllName && dat->ThreadNumber == ThreadNumber)
                return dat;
        }
        return 0;
    }

    void ModuleManager::StartAllDlls()
    {
        DllDataList.clear();
        ThreadDataList.clear();
        ModuleInfoCache = GetModuleInfo();
        for(ModuleInfo Info:ModuleInfoCache)
        {
            if(!Info->IsEnabled)
                continue;
            for(ModuleDll dll:Info->Dlls)
            {
                //qDebug()<<dll->Name;
                //qDebug()<<dll->FileName;
                //qDebug()<<dll->StartDllFunction;
                DllData data = std::make_shared<DllDataClass>();
                data->DllName = dll->Name;
                data->ThreadNumber = -1;
                if(dll->StartDllFunction)
                    data->data = dll->StartDllFunction();
                else
                    data->data = 0;
                //qDebug()<<data->data;
                DllDataList.append(data);
            }
        }
    }

    void ModuleManager::StopAllDlls()
    {
        for(ModuleInfo Info:ModuleInfoCache)
        {
            if(!Info->IsEnabled)
                continue;
            for(ModuleDll dll:Info->Dlls)
            {
                //qDebug()<<dll->Name;
                //qDebug()<<dll->FileName;
                //qDebug()<<dll->EndDllFunction;
                if(dll->EndDllFunction)
                {
                    dll->EndDllFunction(GetDllData(dll->Name));
                }
            }
        }
        DllDataList.clear();
    }

    void ModuleManager::RemoveAllThreadData(int ThreadNumber)
    {
        QMutableListIterator<DllData> i(ThreadDataList);
        while (i.hasNext())
        {
            DllData data = i.next();
            if(data->ThreadNumber == ThreadNumber)
                i.remove();
        }
    }

    void ModuleManager::StartThread(unsigned int ThreadId)
    {
        RemoveAllThreadData(ThreadId);
        for(ModuleInfo Info:ModuleInfoCache)
        {
            if(!Info->IsEnabled)
                continue;
            for(ModuleDll dll:Info->Dlls)
            {
                //qDebug()<<dll->Name;
                //qDebug()<<dll->FileName;
                //qDebug()<<dll->EndDllFunction;
                DllData data = std::make_shared<DllDataClass>();
                data->DllName = dll->Name;
                data->ThreadNumber = ThreadId;
                if(dll->StartThreadFunction)
                    data->data = dll->StartThreadFunction();
                else
                    data->data = 0;
                ThreadDataList.append(data);
            }
        }
    }

    void ModuleManager::StopThread(unsigned int ThreadId)
    {
        for(ModuleInfo Info:ModuleInfoCache)
        {
            if(!Info->IsEnabled)
                continue;
            for(ModuleDll dll:Info->Dlls)
            {
                //qDebug()<<dll->Name;
                //qDebug()<<dll->FileName;
                //qDebug()<<dll->EndDllFunction;
                if(dll->EndThreadFunction)
                    dll->EndThreadFunction(GetThreadData(dll->Name,ThreadId));
            }
        }
        RemoveAllThreadData(ThreadId);
    }

    void* ModuleManager::GetDllData(const QString& DllName)
    {
        DllData data = FindDllData(DllDataList,DllName);
        if(data)
            return data->data;
        return 0;
    }

    void* ModuleManager::GetThreadData(const QString& DllName, unsigned int ThreadId)
    {
        DllData data = FindDllData(ThreadDataList,DllName,ThreadId);
        if(data)
            return data->data;
        return 0;
    }

    IModuleManager::ModuleFunction ModuleManager::FindFunction(const QString& DllName, const QString& FunctionName)
    {
        for(ModuleInfo module:ModuleInfoCache)
        {
            if(!module->IsEnabled)
                continue;
            for(ModuleDll dll :module->Dlls)
            {
                if(dll->Name == DllName)
                {
                    for(ModuleFunction func :dll->FunctionList)
                    {
                        if(func->Alias == FunctionName)
                        {
                            return func;
                        }
                    }
                    return 0;
                }
            }
        }
        return 0;
    }

    FunctionRunData * ModuleManager::PrepareExecuteFunction(const QString& DllName, const QString& FunctionName, const QString& InputParam, unsigned int ThreadId)
    {
        FunctionRunData *res = new FunctionRunData();
        res->FunctionPointer = 0;
        res->DllData = 0;
        res->ThreadData = 0;
        res->ThreadId = ThreadId;
        res->IsError = true;
        res->IsAync = false;
        res->WaitInfinite = false;
        res->NeedToStop = false;
        res->FunctionName = FunctionName;
        res->DllName = DllName;
        ModuleFunction func = FindFunction(DllName, FunctionName);

        if(!func)
        {
            res->ErrorString = std::string("Failed to find function ") +  DllName.toStdString() + std::string(".") + FunctionName.toStdString();
            return res;
        }


        res->FunctionPointer = func->WorkFunction;
        res->IsAync = func->IsAsync;
        res->WaitInfinite = func->IsWaitInfinite;

        res->DllData = FindDllData(DllDataList,DllName)->data;
        res->ThreadData = FindDllData(ThreadDataList,DllName,ThreadId)->data;

        QByteArray InputData = InputParam.toUtf8();
        res->InputJson.assign(InputData.begin(),InputData.end());
        res->InputJson.push_back(0);

        res->IsError = false;

        return res;
    }


    QList<QString> ModuleManager::GetModuleEngineCode()
    {
        QList<QString> res;
        for(IModuleManager::ModuleInfo Info: GetModuleInfo())
        {
            if(Info->IsEnabled)
            {
                res.append(Info->EngineCode);
            }
        }
        return res;
    }

    QList<IModuleManager::ModuleInfo> ModuleManager::GetModuleInfo()
    {
        QList<IModuleManager::ModuleInfo> res;


        QDir dir("modules");
        dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
        QStringList dirList = dir.entryList();

        QJsonDocument DocumentMeta;
        {
            QJsonParseError err;

            QFile meta("modules/meta.json");
            if(meta.open(QIODevice::ReadOnly))
            {
                QByteArray json = meta.readAll();
                DocumentMeta = QJsonDocument::fromJson(json, &err);
                meta.close();
            }
        }

        foreach(QString dir, dirList)
        {
            QJsonParseError err;
            QFile manifest(QString("modules/") + dir + QString("/manifest.json"));
            if(manifest.open(QIODevice::ReadOnly))
            {
                QByteArray json = manifest.readAll();
                QJsonDocument doc = QJsonDocument::fromJson(json, &err);
                manifest.close();

                if(err.error == QJsonParseError::NoError)
                {
                    if(doc.object().contains("name")
                    && doc.object().contains("description")
                    && doc.object().contains("developer_name")
                    && doc.object().contains("developer_email")
                    && doc.object().contains("developer_site")
                    && doc.object().contains("api_version")
                    && doc.object().contains("engine")
                    && doc.object().contains("browser")
                    && doc.object().contains("actions")
                    && doc.object().contains("major_version")
                    && doc.object().contains("minor_version")
                            )
                    {
                        if(doc.object()["api_version"].toInt() > GetModuleSystemVersion())
                        {
                            continue;
                        }
                        IModuleManager::ModuleInfo Info = std::make_shared<IModuleManager::ModuleInfoClass>();



                        Info->Name = doc.object()["name"].toString();
                        Info->Description = doc.object()["description"].toString();
                        Info->DeveloperName = doc.object()["developer_name"].toString();
                        Info->DeveloperEmail = doc.object()["developer_email"].toString();
                        Info->DeveloperSite = doc.object()["developer_site"].toString();
                        Info->ApiVersion = doc.object()["api_version"].toInt();
                        Info->MajorVersion = doc.object()["major_version"].toInt();
                        Info->MinorVersion = doc.object()["minor_version"].toInt();

                        Info->IsEnabled = true;

                        if(DocumentMeta.object().contains(Info->Name))
                        {
                            Info->IsEnabled = DocumentMeta.object()[Info->Name].toBool();
                        }

                        if(Info->IsEnabled)
                        {
                            foreach(QJsonValue val, doc.object()["engine"].toArray())
                            {
                                QFile engine_module(QString("modules/") + dir + QString("/") + val.toString());
                                if(engine_module.open(QIODevice::ReadOnly))
                                {
                                    Info->EngineCode.append(QString("{\n") + QString::fromUtf8(engine_module.readAll()) + QString("\n}"));
                                    engine_module.close();
                                }
                            }
                            if(doc.object().contains("dll"))
                            {
                                foreach(QJsonValue val, doc.object()["dll"].toArray())
                                {
                                    if(!val.isObject())
                                        continue;
                                    QJsonObject obj = val.toObject();
                                    if(obj.contains("name") && obj.contains("filename64") && obj.contains("filename32") && obj.contains("exportlist"))
                                    {
                                        ModuleDll dll = std::make_shared<ModuleDllClass>();
                                        dll->Name = obj["name"].toString();

                                        #ifdef IS_X64
                                            dll->FileName = obj["filename64"].toString();
                                        #else
                                            dll->FileName = obj["filename32"].toString();
                                        #endif

                                        if(obj.contains("startdllfunction"))
                                        {
                                            dll->StartDllFunction = (ModuleOnStartFunction)QLibrary::resolve(QString("modules/") + dir + QString("/") + dll->FileName, obj["startdllfunction"].toString().toUtf8().data());
                                        }else
                                        {
                                            dll->StartDllFunction = 0;
                                        }
                                        if(obj.contains("enddllfunction"))
                                        {
                                            dll->EndDllFunction = (ModuleOnEndFunction)QLibrary::resolve(QString("modules/") + dir + QString("/") + dll->FileName, obj["enddllfunction"].toString().toUtf8().data());
                                        }else
                                        {
                                            dll->EndDllFunction = 0;
                                        }

                                        if(obj.contains("startthreadfunction"))
                                        {
                                            dll->StartThreadFunction = (ModuleOnStartFunction)QLibrary::resolve(QString("modules/") + dir + QString("/") + dll->FileName, obj["startthreadfunction"].toString().toUtf8().data());
                                        }else
                                        {
                                            dll->StartThreadFunction = 0;
                                        }
                                        if(obj.contains("endthreadfunction"))
                                        {
                                            dll->EndThreadFunction = (ModuleOnEndFunction)QLibrary::resolve(QString("modules/") + dir + QString("/") + dll->FileName, obj["endthreadfunction"].toString().toUtf8().data());
                                        }else
                                        {
                                            dll->EndThreadFunction = 0;
                                        }
                                        if(obj.contains("exportlist") && obj["exportlist"].isArray())
                                        {
                                            foreach(QJsonValue val, obj["exportlist"].toArray())
                                            {
                                                if(!val.isObject())
                                                    continue;
                                                QJsonObject obj = val.toObject();
                                                if(obj.contains("name") && obj.contains("workfunction"))
                                                {
                                                    ModuleFunction func = std::make_shared<ModuleFunctionClass>();
                                                    func->Alias = obj["name"].toString();
                                                    if(obj.contains("isasync"))
                                                    {
                                                        func->IsAsync = obj["isasync"].toBool();
                                                    }else
                                                    {
                                                        func->IsAsync = false;
                                                    }

                                                    if(obj.contains("waitinfinite"))
                                                    {
                                                        func->IsWaitInfinite = obj["waitinfinite"].toBool();
                                                    }else
                                                    {
                                                        func->IsWaitInfinite = false;
                                                    }

                                                    func->WorkFunction = (ModuleWorkFunction)QLibrary::resolve(QString("modules/") + dir + QString("/") + dll->FileName, obj["workfunction"].toString().toUtf8().data());
                                                    dll->FunctionList.append(func);
                                                }
                                            }
                                        }




                                        Info->Dlls.append(dll);
                                    }
                                }


                            }
                        }

                        res.append(Info);
                    }
                }
            }
        }
        return res;
    }

    bool ModuleManager::IsModuleEnabled(const QString& ModuleName)
    {
        QJsonParseError err;
        QFile meta("modules/meta.json");
        if(meta.open(QIODevice::ReadOnly))
        {
            QByteArray json = meta.readAll();
            QJsonDocument doc = QJsonDocument::fromJson(json, &err);
            meta.close();

            if(err.error == QJsonParseError::NoError)
            {
                if(doc.object().contains(ModuleName) && doc.object()[ModuleName].toObject().contains("enabled"))
                {
                    return doc.object()[ModuleName].toObject()["enabled"].toBool();
                }
            }
        }
        return true;
    }

    void ModuleManager::SetModuleEnabled(const QString& ModuleName, bool IsEnabled)
    {
        QByteArray json;
        {
            QFile meta("modules/meta.json");
            if(meta.open(QIODevice::ReadOnly))
            {
                json = meta.readAll();
                meta.close();
            }
        }

        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson(json, &err);

        if(err.error == QJsonParseError::NoError)
        {
            {
                QFile meta("modules/meta.json");
                meta.remove();
            }
            QFile meta("modules/meta.json");
            if(meta.open(QIODevice::WriteOnly))
            {
                QJsonObject object = doc.object();
                object[ModuleName] = IsEnabled;
                doc.setObject(object);
                meta.write(doc.toJson());
                return;
            }
        }

        //Error happend

        {
            QFile meta("modules/meta.json");
            meta.remove();
        }

        {
            QFile meta("modules/meta.json");

            if(meta.open(QIODevice::WriteOnly))
            {
                QVariantMap map;
                map.insert(ModuleName, IsEnabled);
                QJsonObject object = QJsonObject::fromVariantMap(map);

                QJsonDocument document;
                document.setObject(object);

                meta.write(document.toJson());
                meta.close();
            }
        }

    }

    int ModuleManager::GetModuleSystemVersion()
    {
        return 1;
    }

}
