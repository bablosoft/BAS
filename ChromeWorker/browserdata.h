#ifndef BROWSERDATA_H
#define BROWSERDATA_H

#include <vector>
#include <memory>
#include <map>
#include "proxydata.h"
#include "include/cef_base.h"
#include "inspectresult.h"
#include <atomic>

class BrowserData
{
public:
    BrowserData();

    std::map<std::string,std::string> _Headers;
    std::string _OpenFileName;
    ProxyData _Proxy;
    CefWindowHandle _MainWindowHandle;
    CefWindowHandle _ParentWindowHandle;
    std::vector<std::pair<bool, std::string> > _CacheMask;
    std::vector<std::pair<bool, std::string> > _RequestMask;
    std::vector<std::pair<std::string, int> > _LoadedUrls;
    std::vector<std::pair<std::string, std::shared_ptr<std::vector<char> > > > _CachedData;
    std::atomic_int WidthBrowser;
    std::atomic_int HeightBrowser;
    std::atomic_int WidthAll;
    std::atomic_int HeightAll;
    std::atomic_int ScrollX;
    std::atomic_int ScrollY;
    std::atomic_int CursorX;
    std::atomic_int CursorY;
    std::atomic_bool IsRecord;
    InspectResult _Inspect;

    //Reset
    std::atomic_bool IsReset;
    std::atomic_bool IsAboutBlankLoaded;
};

#endif // BROWSERDATA_H
