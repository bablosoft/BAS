#ifndef CSVHELPERWRAPPER_H
#define CSVHELPERWRAPPER_H

#include "engine_global.h"
#include "icsvhelper.h"
#include <QObject>
#include <QScriptValue>
#include <QScriptEngine>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT CsvHelperWrapper : public QObject
    {
        Q_OBJECT
        ICsvHelper *Helper;
        QScriptEngine * Engine;
    public:
        explicit CsvHelperWrapper(QScriptEngine * Engine, ICsvHelper *Helper, QObject *parent = 0);

    signals:

    public slots:
        QScriptValue Generate(const QScriptValue& List, QScriptValue Separator);
        QScriptValue Parse(const QScriptValue& Line);
    };
}
#endif // CSVHELPERWRAPPER_H
