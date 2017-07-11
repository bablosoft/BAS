#ifndef BROWSERDATA_H
#define BROWSERDATA_H

#include <vector>
#include <memory>
#include <map>
#include "proxydata.h"
#include "include/cef_base.h"
#include "inspectresult.h"
#include "highlightresult.h"
#include <atomic>
#include "modulesdata.h"
#include "configurableitem.h"
#include "localstoragedata.h"

class BrowserData
{
public:
    BrowserData();

    ConfigurableItem<std::shared_ptr<std::map<std::string,std::string> > > _Headers;
    std::vector<std::string> _HeadersDefaults;
    std::string _NextReferrer;
    std::string _OpenFileName;
    std::map<std::string,ConfigurableItem<std::string> > _StartupScript;
    ConfigurableItem<ProxyData> _Proxy;
    CefWindowHandle _MainWindowHandle;
    CefWindowHandle _ParentWindowHandle;
    std::atomic<int64> OldestRequestTime;
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
    std::atomic_bool AllowPopups;
    std::atomic_bool AllowDownloads;
    InspectResult _Inspect;
    HighlightResult _Highlight;
    ModulesDataList _ModulesData;

    //Dialogs
    std::string _PromptResult;
    std::string _HttpAuthLogin;
    std::string _HttpAuthPassword;

    //DragAndDrop
    bool IsDrag;
    bool IsMousePress;

    //Reset
    std::atomic_bool IsReset;
    std::atomic_bool IsAboutBlankLoaded;

    //LocalStorage
    //LocalStorageData _LocalStorageData;

    //DomainDataClear
    bool NeedClear;
    std::vector<std::string> DomainClearData;

    //Timezone
    std::atomic_bool TimezoneSelected;
    std::atomic_int Timezone;

    std::atomic_bool GeolocationSelected;
    std::atomic<float> Latitude;
    std::atomic<float> Longitude;

};

#endif // BROWSERDATA_H
