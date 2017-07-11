#include "scriptresourcesfromqt.h"
#include <QFile>
#include <QTextStream>
#include <QDirIterator>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonObject>
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    ScriptResourcesFromQt::ScriptResourcesFromQt(QObject *parent) :
        IScriptResources(parent)
    {
    }

    QString ScriptResourcesFromQt::GetFromRes(const QString & res)
    {
        QFile f(res);
        if (!f.open(QFile::ReadOnly | QFile::Text)) return QString();
        QTextStream in(&f);
        in.setCodec("UTF-8");
        QString ret = in.readAll();
        f.close();
        return ret;

    }

    QList<QString> ScriptResourcesFromQt::GetJqueryPlugins()
    {
        QList<QString> res;
        res.append(GetFromRes(":/engine/scripts/browser/jquery.plugins.js"));
        res.append(GetFromRes(":/engine/scripts/browser/extend.js"));
        return res;
    }

    QString ScriptResourcesFromQt::GetJquery()
    {
        return GetFromRes(":/engine/scripts/browser/jquery.js");
    }

    QList<QString> ScriptResourcesFromQt::GetEngineScripts()
    {
        QList<QString> res;
        res.append(GetFromRes(":/engine/scripts/engine/worker/template.js"));
        res.append(GetFromRes(":/engine/scripts/engine/worker/translate.js"));
        res.append(GetFromRes(":/engine/scripts/engine/common/cycles.js"));
        res.append(GetFromRes(":/engine/scripts/engine/common/memory.js"));
        res.append(GetFromRes(":/engine/scripts/engine/common/html_parser.js"));
        res.append(GetFromRes(":/engine/scripts/engine/common/helpers.js"));
        res.append(GetFromRes(":/engine/scripts/engine/common/translit.js"));
        res.append(GetFromRes(":/engine/scripts/engine/worker/flow.js"));
        res.append(GetFromRes(":/engine/scripts/engine/worker/httpclient.js"));
        res.append(GetFromRes(":/engine/scripts/engine/worker/pop3client.js"));
        res.append(GetFromRes(":/engine/scripts/engine/worker/imapclient.js"));
        res.append(GetFromRes(":/engine/scripts/engine/worker/waiters.js"));
        res.append(GetFromRes(":/engine/scripts/engine/worker/resources.js"));
        res.append(GetFromRes(":/engine/scripts/engine/worker/properties.js"));
        res.append(GetFromRes(":/engine/scripts/engine/worker/worker.js"));
        res.append(GetFromRes(":/engine/scripts/engine/worker/cache.js"));
        res.append(GetFromRes(":/engine/scripts/engine/worker/record.js"));
        res.append(GetFromRes(":/engine/scripts/engine/worker/images.js"));
        return res;
    }

    QList<QString> ScriptResourcesFromQt::GetMultiEngineScripts()
    {
        QList<QString> res;
        res.append(GetFromRes(":/engine/scripts/engine/common/cycles.js"));
        res.append(GetFromRes(":/engine/scripts/engine/common/memory.js"));
        res.append(GetFromRes(":/engine/scripts/engine/common/html_parser.js"));
        res.append(GetFromRes(":/engine/scripts/engine/common/helpers.js"));
        res.append(GetFromRes(":/engine/scripts/engine/common/translit.js"));
        res.append(GetFromRes(":/engine/scripts/engine/multiworker/flow.js"));
        res.append(GetFromRes(":/engine/scripts/engine/multiworker/multi.js"));
        res.append(GetFromRes(":/engine/scripts/engine/multiworker/resources.js"));
        res.append(GetFromRes(":/engine/scripts/engine/multiworker/properties.js"));


        return res;
    }

    QList<QString> ScriptResourcesFromQt::GetPageScripts()
    {

        QList<QString> res;
        res.append(GetFromRes(":/engine/scripts/browser/helpers.js"));
        return res;
    }

}
