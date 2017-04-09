#ifndef MULTITHREADING_H
#define MULTITHREADING_H
#include "include/base/cef_lock.h"
#include "include/wrapper/cef_helpers.h"
#include <string>

struct multithreading
{
    base::Lock _LockBrowserData;
    base::Lock _LockV8Handler;
    base::Lock _LockNewContextList;
    base::Lock _LockMapBrowserIdToTabNumber;
    base::Lock _LockPrompt;
    base::Lock _LockHttpAuth;
    base::Lock _LockLocalStorage;
    base::Lock _LockDomainClear;
    base::Lock _LockTimezone;
    base::Lock _LockGeolocation;
    base::Lock _LockFonts;
    base::Lock _LockPostManager;
};
extern multithreading mthreading;

#define LOCK_BROWSER_DATA base::AutoLock lock_scope(mthreading._LockBrowserData);
#define LOCK_V8_HANDLER base::AutoLock lock_scope(mthreading._LockV8Handler);
#define LOCK_CONTEXT_LIST base::AutoLock lock_scope(mthreading._LockNewContextList);
#define LOCK_MAP_BROWSER_ID_TO_TAB_NUMBER base::AutoLock lock_scope(mthreading._LockMapBrowserIdToTabNumber);
#define LOCK_PROMPT base::AutoLock lock_scope(mthreading._LockPrompt);
#define LOCK_HTTP_AUTH base::AutoLock lock_scope(mthreading._LockHttpAuth);
#define LOCK_LOCAL_STORAGE base::AutoLock lock_scope(mthreading._LockLocalStorage);
#define LOCK_DOMAIN_CLEAR base::AutoLock lock_scope(mthreading._LockDomainClear);
#define LOCK_TIMEZONE base::AutoLock lock_scope(mthreading._LockTimezone);
#define LOCK_GEOLOCATION base::AutoLock lock_scope(mthreading._LockGeolocation);
#define LOCK_FONTS base::AutoLock lock_scope(mthreading._LockFonts);
#define LOCK_POST_MANAGER base::AutoLock lock_scope(mthreading._LockPostManager);

std::string GetCurrentThreadString();


#endif // MULTITHREADING_H
