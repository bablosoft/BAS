#ifndef ITABBLINK_H
#define ITABBLINK_H


#include "engine_global.h"

#include <QObject>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ITabBlink : public QObject
    {
        Q_OBJECT
    public:
        explicit ITabBlink(QObject *parent = 0);

    signals:

    public slots:
        virtual void Stop() = 0;
        virtual void Start() = 0;

    };
}


#endif // ITABBLINK_H
