#include "postpreparestrategyjsonencode.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QVariantMap>
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    PostPrepareStrategyJsonEncode::PostPrepareStrategyJsonEncode()
    {

    }

    QByteArray PostPrepareStrategyJsonEncode::GenerateData(const QHash<QString,ContentData> & params)
    {
        QByteArray data;
        QList<QString> keys = params.keys();
        QList<ContentData> values = params.values();

        QVariantMap res;
        for(int i = 0;i<params.size();++i)
        {
            res[keys.at(i)] = values.at(i).DataString;
        }
        QJsonObject object = QJsonObject::fromVariantMap(res);

        QJsonDocument document;
        document.setObject(object);

        data = document.toJson();

        return data;
    }

    QByteArray PostPrepareStrategyJsonEncode::GetContentType()
    {
        return QByteArray("application/json");
    }
}
