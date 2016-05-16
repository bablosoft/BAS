#ifndef ISTRINGBOXLOADER_H
#define ISTRINGBOXLOADER_H
#include "engine_global.h"

#include <QObject>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IStringBoxLoader : public QObject
    {
        Q_OBJECT
    public:
        explicit IStringBoxLoader(QObject *parent = 0);

    signals:
        void Loaded(QStringList &list);
        void DataLoadedCompletely();
    public slots:
        virtual void Load() = 0;

    };
}

#endif // ISTRINGBOXLOADER_H
