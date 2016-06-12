#include "proxydata.h"
#include "replaceall.h"

ProxyData::ProxyData()
{
    Clear();
}

bool ProxyData::IsEqual(const ProxyData& Proxy)
{
    return Server == Proxy.Server &&
           Port == Proxy.Port &&
           ProxyType == Proxy.ProxyType &&
           UserName == Proxy.UserName &&
           Password == Proxy.Password &&
           IsNull == Proxy.IsNull;

}

void ProxyData::Clear()
{
    Server.clear();
    Port = 0;
    ProxyType = Http;
    UserName.clear();
    Password.clear();
    IsNull = true;
}



std::string ProxyData::AuthToString()
{
    if(UserName.empty() || Password.empty())
        return std::string();

    return ReplaceAll(UserName,":","%3A") + ":" + ReplaceAll(Password,":","%3A");
}

std::string ProxyData::ToString()
{
    std::string res;
    if(IsNull)
        return res;

    if(ProxyType == Socks4)
    {
        res += "socks4";
    }else if(ProxyType == Socks5)
    {
        res += "socks5h";
    }else if(ProxyType == Http)
    {
        res += "http";
    }
    res += "://";
    res += Server;
    res += ":";
    res += std::to_string(Port);
    return res;
}

