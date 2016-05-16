#include "memoryinfo.h"
#ifdef Q_OS_WIN
    #include <windows.h>
#endif
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    MemoryInfo::MemoryInfo(QObject *parent) :
        IMemoryInfo(parent)
    {
    }
    quint64 MemoryInfo::GetTotalPhysicalMemory()
    {
        #ifdef Q_OS_WIN
            MEMORYSTATUSEX status;
            status.dwLength = sizeof(status);
            GlobalMemoryStatusEx(&status);
            return status.ullTotalPhys / 1024;
        #endif
        return 4*1024*1024;
    }
    quint64 MemoryInfo::GetAvailablePhysicalMemory()
    {
        #ifdef Q_OS_WIN
            MEMORYSTATUSEX status;
            status.dwLength = sizeof(status);
            GlobalMemoryStatusEx(&status);
            return status.ullAvailPhys / 1024;
        #endif
        return 4*1024*1024;
    }
    quint64 MemoryInfo::GetTotalVirtualMemory()
    {
        #ifdef Q_OS_WIN
            MEMORYSTATUSEX status;
            status.dwLength = sizeof(status);
            GlobalMemoryStatusEx(&status);
            return status.ullTotalVirtual / 1024;
        #endif
        return 4*1024*1024;
    }
    quint64 MemoryInfo::GetAvailableVirtualMemory()
    {
        #ifdef Q_OS_WIN
            MEMORYSTATUSEX status;
            status.dwLength = sizeof(status);
            GlobalMemoryStatusEx(&status);
            return status.ullAvailVirtual / 1024;
        #endif
        return 4*1024*1024;
    }
}
