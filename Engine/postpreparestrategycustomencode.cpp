#include "postpreparestrategycustomencode.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    PostPrepareStrategyCustomEncode::PostPrepareStrategyCustomEncode()
    {

    }

    QByteArray PostPrepareStrategyCustomEncode::GenerateData(const QHash<QString,ContentData> & params)
    {
        QByteArray data;
        if(params.contains("data"))
        {
            ContentData d = params["data"];
            if(!d.DataString.isEmpty())
                data.append(d.DataString.toUtf8());
            else if(!d.DataRaw.isEmpty())
                data.append(d.DataRaw);
        }
        return data;
    }


    void PostPrepareStrategyCustomEncode::SetContentType(const QString& ContentType)
    {
        this->ContentType = ContentType;
    }
    QByteArray PostPrepareStrategyCustomEncode::GetContentType()
    {
        return ContentType.toUtf8();
    }

}
