#include "postpreparestrategyurlencode.h"
#include <QUrl>

    PostPrepareStrategyUrlEncode::PostPrepareStrategyUrlEncode(QObject *parent) :
        IPostPrepareStrategy(parent)
    {
    }

    QByteArray PostPrepareStrategyUrlEncode::GenerateData(const QHash<QString,ContentData> & params)
    {
        QByteArray data;
        QList<QString> keys = params.keys();
        QList<ContentData> values = params.values();

        for(int i = 0;i<params.size();++i)
        {
            if(i)
                data.append("&");
            data.append(QUrl::toPercentEncoding(keys.at(i).toUtf8()));
            data.append("=");

            data.append(QUrl::toPercentEncoding(values.at(i).DataString.toUtf8()));
        }
        return data;
    }

    QByteArray PostPrepareStrategyUrlEncode::GetContentType()
    {
        return QByteArray("application/x-www-form-urlencoded");
    }

