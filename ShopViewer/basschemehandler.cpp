#include "basschemehandler.h"
#include <QDebug>
#include <QWebEngineUrlRequestJob>
#include <QProcess>

BasSchemeHandler::BasSchemeHandler(QObject *parent) : QWebEngineUrlSchemeHandler(parent)
{

}

void BasSchemeHandler::requestStarted(QWebEngineUrlRequestJob *request)
{
    QString ScriptName = request->requestUrl().toString().replace("bas://","");
    qDebug()<<"Launching"<<ScriptName;
    QStringList Params;
    Params.append("--remote");
    Params.append("--script");
    Params.append(ScriptName);
    QProcess::startDetached("RemoteExecuteScript/RemoteExecuteScript.exe",Params,"RemoteExecuteScript");
}
