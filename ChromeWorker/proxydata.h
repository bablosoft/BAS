#ifndef PROXYDATA_H
#define PROXYDATA_H

#include <string>

class ProxyData
{
public:
    ProxyData();
    std::string Server;
    int Port;
    enum ProxyTypeEnum{Socks4,Socks5,Http}ProxyType;
    std::string UserName;
    std::string Password;
    bool IsNull;
    bool IsEqual(const ProxyData& Proxy);
    std::string ToString();
    std::string AuthToString();
    void Clear();

};

#endif // PROXYDATA_H
