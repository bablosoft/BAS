#include "ihttpclient.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "every_cpp.h"
namespace BrowserAutomationStudioFramework
{
    IHttpClient::IHttpClient(QObject *parent) :
        QObject(parent)
    {
    }

    PostOptions::PostOptions()
    {
        ContentTypeEncoding = "UTF-8";
        PrepareStrategy = "multipart";
        Method = "POST";
    }

    GetOptions::GetOptions()
    {
        Method = "GET";
    }

    QVariantMap IHttpClient::SerializeTime(const QDateTime& time)
    {
        QVariantMap res;

        res.insert("year",QString::number(time.date().year()));
        res.insert("month",QString::number(time.date().month()));
        res.insert("day_of_week",QString::number(time.date().dayOfWeek()));
        res.insert("day_of_month",QString::number(time.date().day()));
        res.insert("hour",QString::number(time.time().hour()));
        res.insert("minute",QString::number(time.time().minute()));
        res.insert("second",QString::number(time.time().second()));
        res.insert("millisecond",QString::number(0));

        return res;
    }

    QDateTime IHttpClient::DeserializeTime(const QJsonObject& object)
    {
        int year = object["year"].toString().toInt();
        int month = object["month"].toString().toInt();
        int day_of_month = object["day_of_month"].toString().toInt();
        int hour = object["hour"].toString().toInt();
        int minute = object["minute"].toString().toInt();
        int second = object["second"].toString().toInt();
        int millisecond = object["millisecond"].toString().toInt();

        return QDateTime(QDate(year,month,day_of_month),QTime(hour,minute,second,millisecond));
    }

}
