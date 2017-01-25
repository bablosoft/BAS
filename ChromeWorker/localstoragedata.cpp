#include "localstoragedata.h"
#include <algorithm>
#include "picojson.h"
#include "log.h"

LocalStorageData::LocalStorageData()
{

}


void LocalStorageData::SortAndUpdate()
{
    /*std::sort(Items.begin(), Items.end(), [](const Item & a, const Item & b) -> bool
    {
        return a.Time > b.Time;
    });*/
}

std::string LocalStorageData::Get()
{
    SortAndUpdate();
    //picojson::value::object res;
    /*for (Item i: Items)
    {
        switch(i.Type)
        {
            case Item::Set:
                if(res.count(i.Domain) > 0)
                {
                    picojson::value::object o = res[i.Domain].get<picojson::value::object>();
                    o[i.Key] = picojson::value(i.Value);
                    res[i.Domain] = o;
                }else
                {
                    picojson::value::object o;
                    o[i.Key] = picojson::value(i.Value);
                    res[i.Domain] = o;
                }
            break;
            case Item::Remove:
                if(res.count(i.Domain) > 0)
                {
                    picojson::value::object o = res[i.Domain].get<picojson::value::object>();
                    o.erase(i.Key);
                    res[i.Domain] = o;
                }
            break;
            case Item::ClearDomain: res.erase(i.Domain); break;
            case Item::ClearAll: res.clear(); break;
        }
    }*/
    picojson::value::array res;
    for (Item i: Items)
    {
        //type, key, value, domain, frame, time
        picojson::value::object item;
        switch(i.Type)
        {
            case Item::Set:
                item["type"] = picojson::value("set");
            break;
            case Item::Remove:
                item["type"] = picojson::value("remove");
            break;
            case Item::ClearDomain:
                item["type"] = picojson::value("cleardomain");
            break;
            case Item::ClearAll:
                item["type"] = picojson::value("clearall");
            break;
        }
        item["key"] = picojson::value(i.Key);
        item["value"] = picojson::value(i.Value);
        item["domain"] = picojson::value(i.Domain);
        item["frame"] = picojson::value(double(i.FrameHash));
        item["time"] = picojson::value(i.Time);
        res.push_back(picojson::value(item));
    }

    return picojson::value(res).serialize();
}

void LocalStorageData::Set(const LocalStorageDataItem& item)
{
    Item i;
    if(item.TypeString == "set")
    {
       i.Type = Item::Set;
    }else if(item.TypeString == "remove")
    {
       i.Type = Item::Remove;
    }else if(item.TypeString == "cleardomain")
    {
       i.Type = Item::ClearDomain;
    }else if(item.TypeString == "clearall")
    {
       i.Type = Item::ClearAll;
    }else
    {
        return;
    }
    i.Key = item.Key;
    i.Value = item.Value;
    i.Domain = item.Domain;
    i.FrameHash = item.FrameHash;
    i.Time = item.Time;

    Items.push_back(i);


    SortAndUpdate();
}

void LocalStorageData::Parse(const std::string& value)
{
    WORKER_LOG(value);
    Items.clear();
    Current.clear();
    picojson::value parsed;
    std::string err = picojson::parse(parsed, value);
    if(!err.empty())
        return;
    if(!parsed.is<picojson::value::array>())
        return;
    picojson::value::array all = parsed.get<picojson::value::array>();
    for(picojson::value v:all)
    {
        if(!v.is<picojson::value::object>())
            continue;

        picojson::value::object o = v.get<picojson::value::object>();
        Item i;
        std::string type = o["type"].get<std::string>();
        if(type == "set")
        {
           i.Type = Item::Set;
        }else if(type == "remove")
        {
           i.Type = Item::Remove;
        }else if(type == "cleardomain")
        {
           i.Type = Item::ClearDomain;
        }else if(type == "clearall")
        {
           i.Type = Item::ClearAll;
        }else
        {
            continue;
        }
        i.Key = o["key"].get<std::string>();
        i.Value = o["value"].get<std::string>();
        i.Domain = o["domain"].get<std::string>();
        i.FrameHash = o["frame"].get<double>();
        i.Time = o["time"].get<std::string>();
        Items.push_back(i);
    }
}

void LocalStorageData::Clear()
{
    Items.clear();
    Current.clear();
}
