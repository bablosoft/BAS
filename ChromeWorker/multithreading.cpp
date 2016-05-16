#include "multithreading.h"

multithreading mthreading;

std::string GetCurrentThreadString()
{
    if(CefCurrentlyOn(TID_UI))
        return "TID_UI";

    if(CefCurrentlyOn(TID_DB))
        return "TID_DB";

    if(CefCurrentlyOn(TID_FILE))
        return "TID_FILE";

    if(CefCurrentlyOn(TID_FILE_USER_BLOCKING))
        return "TID_FILE_USER_BLOCKING";

    if(CefCurrentlyOn(TID_PROCESS_LAUNCHER))
        return "TID_PROCESS_LAUNCHER";

    if(CefCurrentlyOn(TID_CACHE))
        return "TID_CACHE";

    if(CefCurrentlyOn(TID_IO))
        return "TID_IO";

    if(CefCurrentlyOn(TID_RENDERER))
        return "TID_RENDERER";

    return "TID_UNKNOWN";
}
