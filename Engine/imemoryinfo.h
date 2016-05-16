#ifndef IMEMORYINFO_H
#define IMEMORYINFO_H

#include <QObject>
#include "engine_global.h"


namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IMemoryInfo : public QObject
    {
        Q_OBJECT
    public:
        explicit IMemoryInfo(QObject *parent = 0);


    signals:

    public slots:
        virtual quint64 GetTotalPhysicalMemory() = 0;
        virtual quint64 GetAvailablePhysicalMemory() = 0;
        virtual quint64 GetTotalVirtualMemory() = 0;
        virtual quint64 GetAvailableVirtualMemory() = 0;

    };
}

#endif // IMEMORYINFO_H
