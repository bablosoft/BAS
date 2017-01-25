#ifndef CONFIGURABLEITEM_H
#define CONFIGURABLEITEM_H

#include <string>
#include <vector>
#include "match.h"
#include "urlnormalize.h"
#include "picojson.h"


template < typename TYPE > class ConfigurableItem
{
    template < typename TYPE > struct ConfigurableSingleItem
    {
        std::string url;
        std::string tab;
        TYPE value;
    };
    std::vector<ConfigurableSingleItem<TYPE> > data;

    bool IsMatch(const std::string& UrlMatch, const std::string& TabMatch,const std::string& Url,int Tab)
    {
        bool IsUrlMatch = false;
        if((UrlMatch.empty() || UrlMatch == "*"))
        {
            IsUrlMatch = true;
        }else
        {
            IsUrlMatch = match(UrlMatch,Url) || match(urlnormalize(UrlMatch),urlnormalize(Url));
        }

        bool IsTabMatch = false;
        if((TabMatch.empty() || TabMatch == "*"))
        {
            IsTabMatch = true;
        }else
        {
            IsTabMatch = std::to_string(Tab) == TabMatch;
        }

        return IsUrlMatch && IsTabMatch;
    }

    bool IsItemEmpty(const ConfigurableSingleItem<TYPE>& item)
    {
        return (item.tab.empty() || item.tab == "*") && (item.url.empty() || item.url == "*");
    }

public:
    void Clear()
    {
        data.clear();
    }

    std::vector<TYPE> MatchAll(const std::string& Url, int Tab)
    {
        std::vector<TYPE> res;
        //search for default value
        for(ConfigurableSingleItem<TYPE> i:data)
        {
            if(IsItemEmpty(i))
            {
                if(IsMatch(i.url,i.tab,Url,Tab))
                    res.push_back(i.value);
                break;
            }
        }

        //search for other values
        for(ConfigurableSingleItem<TYPE> i:data)
        {
            if(!IsItemEmpty(i))
            {
                if(IsMatch(i.url,i.tab,Url,Tab))
                    res.push_back(i.value);
            }
        }

        return res;
    }

    TYPE Match(const std::string& Url,int Tab)
    {
        std::vector<TYPE> ResAll = MatchAll(Url, Tab);
        TYPE Res;
        if(!ResAll.empty())
        {
            Res = ResAll.at(ResAll.size() - 1);
        }
        //WORKER_LOG(std::string("TARGET ") + Url + std::string(";;;") + std::to_string(Tab) + std::string("===") + std::to_string(ResAll.size()));

        return Res;
    }

    TYPE Get(const std::string& Target)
    {
        try
        {
            std::string Url;
            std::string Tab;
            if(!Target.empty())
            {
                picojson::value v;
                picojson::parse(v, Target);
                Url = v.get<picojson::value::object>()["url"].get<std::string>();
                Tab = v.get<picojson::value::object>()["tab"].get<std::string>();
            }

            for(ConfigurableSingleItem<TYPE> i: data)
            {
                if((i.url == Url && i.tab == Tab) || (IsItemEmpty(i) && ((Tab.empty() || Tab == "*") && (Url.empty() || Url == "*"))))
                {
                    return i.value;
                }
            }

        }catch(...)
        {

        }


        TYPE Res;
        return Res;
    }

    void Set(const TYPE& Value, const std::string& Target)
    {
        try
        {
            ConfigurableSingleItem<TYPE> item;
            if(!Target.empty())
            {
                picojson::value v;
                picojson::parse(v, Target);
                item.url = v.get<picojson::value::object>()["url"].get<std::string>();
                item.tab = v.get<picojson::value::object>()["tab"].get<std::string>();
            }

            int IndexFound = -1;
            int Index = 0;

            for(ConfigurableSingleItem<TYPE> i: data)
            {
                if((i.url == item.url && i.tab == item.tab) || (IsItemEmpty(i) && IsItemEmpty(item)))
                {
                    IndexFound = Index;
                    break;
                }
                Index++;
            }
            if(IndexFound>=0)
            {
                data.erase(data.begin() + IndexFound);
            }
            item.value = Value;
            data.push_back(item);


        }catch(...)
        {

        }
    }
};

#endif // CONFIGURABLEITEM_H
