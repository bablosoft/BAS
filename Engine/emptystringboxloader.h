#ifndef EMPTYSTRINGBOXLOADER_H
#define EMPTYSTRINGBOXLOADER_H
#include "engine_global.h"
#include "istringboxloader.h"
#include <QStringList>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT EmptyStringBoxLoader : public IStringBoxLoader
    {
        Q_OBJECT
    public:
        explicit EmptyStringBoxLoader(QObject *parent = 0);

    signals:

    public slots:
        virtual void Load();
    };
}

#endif // EMPTYSTRINGBOXLOADER_H
