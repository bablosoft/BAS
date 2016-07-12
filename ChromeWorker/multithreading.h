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
    base::Lock _LockPrompt;
    base::Lock _LockHttpAuth;
};
extern multithreading mthreading;

#define LOCK_BROWSER_DATA base::AutoLock lock_scope(mthreading._LockBrowserData);
#define LOCK_V8_HANDLER base::AutoLock lock_scope(mthreading._LockV8Handler);
#define LOCK_CONTEXT_LIST base::AutoLock lock_scope(mthreading._LockNewContextList);
#define LOCK_PROMPT base::AutoLock lock_scope(mthreading._LockPrompt);
#define LOCK_HTTP_AUTH base::AutoLock lock_scope(mthreading._LockHttpAuth);

std::string GetCurrentThreadString();


#endif // MULTITHREADING_H
