#ifndef MEMORYINFO_H
#define MEMORYINFO_H
#include "engine_global.h"
#include "imemoryinfo.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT MemoryInfo : public IMemoryInfo
    {
        Q_OBJECT
    public:
        explicit MemoryInfo(QObject *parent = 0);

    signals:

    public slots:
        virtual quint64 GetTotalPhysicalMemory();
        virtual quint64 GetAvailablePhysicalMemory();
        virtual quint64 GetTotalVirtualMemory();
        virtual quint64 GetAvailableVirtualMemory();
    };
}

#endif // MEMORYINFO_H
