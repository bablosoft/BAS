#include "csvhelperwrapper.h"
#include <QVariant>


#include "every_cpp.h"



namespace BrowserAutomationStudioFramework
{
    CsvHelperWrapper::CsvHelperWrapper(QScriptEngine * Engine, ICsvHelper *Helper, QObject *parent) :
        QObject(parent)
    {
        this->Helper = Helper;
        this->Engine = Engine;
    }

    QScriptValue CsvHelperWrapper::Generate(const QScriptValue& List, QScriptValue Separator)
    {
        QStringList a1 = List.toVariant().toStringList();
        QChar a2 = Separator.toString()[0];
        return QScriptValue(Helper->Generate(a1,a2));

    }

    QScriptValue CsvHelperWrapper::Parse(const QScriptValue& Line)
    {
        return qScriptValueFromSequence(Engine,Helper->Parse(Line.toString()));
    }
}
