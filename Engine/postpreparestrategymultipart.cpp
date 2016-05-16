#include "postpreparestrategymultipart.h"
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    PostPrepareStrategyMultipart::PostPrepareStrategyMultipart(QObject *parent) :
        IPostPrepareStrategy(parent)
    {
        const char alphanum[] = "abcdefghijklmnopqrstuvwxyz";
        for(int i = 0;i<40;i++)
            Boundary += QString(alphanum[qrand() % (sizeof(alphanum) - 1)]);
    }


    QByteArray PostPrepareStrategyMultipart::GenerateData(const QHash<QString,ContentData> & params)
    {
        QByteArray data;
        QList<QString> keys = params.keys();
        QList<ContentData> values = params.values();


        for(int i = 0;i<params.size();++i)
        {
            data.append("--" + Boundary + "\r\n");
            ContentData Data = values.at(i);
            data.append("Content-Disposition: form-data; name=\"" + keys.at(i) + "\"; ");
            if(!Data.FileName.isEmpty())
                data.append(QString("filename=\"") + Data.FileName + QString("\""));
            data.append("\r\n");


            if(!Data.ContentType.isEmpty())
                data.append("Content-Type: " + Data.ContentType + "\r\n");

            data.append("\r\n");

            if(!Data.DataString.isEmpty())
                data.append(Data.DataString);
            else if(!Data.DataRaw.isEmpty())
                data.append(Data.DataRaw);

            data.append("\r\n");
        }
        data.append("--" + Boundary + "--\r\n");
        return data;
    }

    QByteArray PostPrepareStrategyMultipart::GetContentType()
    {
        return (QString("multipart/form-data; boundary=") + Boundary).toUtf8();
    }
}
