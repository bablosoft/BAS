#include "moduledll.h"
#include <QDir>
#include <QJsonObject>
#include <QMap>
#include <QDir>
#include <QJsonDocument>
#include <QByteArray>
#include <QVariant>
#include "GeoIP.h"
#include "GeoIPCity.h"

extern "C" {

    struct GeoDllData
    {
        GeoIP *gic;
        GeoIP *gic6;
    };

    void* StartDll()
    {
        GeoDllData * data = new GeoDllData();
        data->gic = GeoIP_open("modules/Timezones/GeoLiteCity.dat", GEOIP_STANDARD);
        data->gic6 = GeoIP_open("modules/Timezones/GeoLiteCityv6.dat", GEOIP_STANDARD);
        return data;
    }

    void EndDll(void * DllData)
    {
        GeoDllData * data = (GeoDllData *)DllData;
        GeoIP_delete(data->gic);
        GeoIP_delete(data->gic6);
        delete data;
    }

    void* StartThread()
    {
        return 0;
    }

    void EndThread(void * DllData)
    {

    }

    static unsigned long __addr_to_num(const char *addr)
    {
        unsigned int c, octet, t;
        unsigned long ipnum;
        int i = 3;

        octet = ipnum = 0;
        while ((c = *addr++)) {
            if (c == '.') {
                if (octet > 255) {
                    return 0;
                }
                ipnum <<= 8;
                ipnum += octet;
                i--;
                octet = 0;
            } else {
                t = octet;
                octet <<= 3;
                octet += t;
                octet += t;
                c -= '0';
                if (c > 9) {
                    return 0;
                }
                octet += c;
            }
        }
        if ((octet > 255) || (i != 0)) {
            return 0;
        }
        ipnum <<= 8;
        return ipnum + octet;
    }


    void IpInfo(char *InputJson, ResizeFunction AllocateSpace, void* AllocateData, void* DllData, void* ThreadData, unsigned int ThreadId, bool *NeedToStop, bool* WasError)
    {
        GeoDllData * data = (GeoDllData *)DllData;
        QVariantMap res;

        QString ip = InputJson;

        GeoIPRecord *record;
        if(ip.startsWith("["))
        {
            geoipv6_t Ip = _GeoIP_lookupaddress_v6(ip.replace("[","").replace("]","").toStdString().c_str());
            record = GeoIP_record_by_ipnum_v6(data->gic6,Ip);
        }else
        {
            unsigned long Ip = __addr_to_num(ip.toStdString().c_str());
            record = GeoIP_record_by_ipnum(data->gic,Ip);
        }

        if(record)
        {
            res.insert("valid", true);
            res.insert("city", QString::fromLatin1(record->city));
            res.insert("country", QString::fromLatin1(record->country_code));
            res.insert("latitude", record->latitude);
            res.insert("longitude", record->longitude);
            res.insert("timezone", GeoIP_time_zone_by_country_and_region(record->country_code,record->region));
            res.insert("offset", GeoIP_time_zone_offset_by_country_and_region(record->country_code,record->region));
            res.insert("dstoffset", GeoIP_time_zone_dst_offset_by_country_and_region(record->country_code,record->region));
            GeoIPRecord_delete(record);
        }else
        {
            res.insert("valid", false);
        }


        QJsonObject object = QJsonObject::fromVariantMap(res);

        QJsonDocument document;
        document.setObject(object);

        QByteArray ResArray = document.toJson();

        char * ResMemory = AllocateSpace(ResArray.size(),AllocateData);
        memcpy(ResMemory, ResArray.data(), ResArray.size() );
    }


}
