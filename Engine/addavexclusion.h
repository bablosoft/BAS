#ifndef ADDAVEXCLUSION_H
#define ADDAVEXCLUSION_H

#include "engine_global.h"
#include <QObject>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT AddAVExclusion : public QObject
    {
        Q_OBJECT
    public:
        explicit AddAVExclusion(QObject *parent = 0);
        void Run();
    };
}

#endif // ADDAVEXCLUSION_H
