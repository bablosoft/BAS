#ifndef MULTITHREADING_H
#define MULTITHREADING_H
#include "include/base/cef_lock.h"
#include "include/wrapper/cef_helpers.h"
#include <string>

struct multithreading
{
    base::Lock _LockBrowserData;
    base::Lock _LockV8Handler;
};
extern multithreading mthreading;

#define LOCK_BROWSER_DATA base::AutoLock lock_scope(mthreading._LockBrowserData);
#define LOCK_V8_HANDLER base::AutoLock lock_scope(mthreading._LockV8Handler);



std::string GetCurrentThreadString();


#endif // MULTITHREADING_H
