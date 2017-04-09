#ifndef IDIFFPATCHER_H
#define IDIFFPATCHER_H

#include <QObject>

#include "engine_global.h"


namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IDiffPatcher : public QObject
    {
        Q_OBJECT
        public:
            explicit IDiffPatcher(QObject *parent = 0);

            virtual void Init(const QString& Text) = 0;
            virtual QString ApplyPatch(const QString& PatchString) = 0;
    };
}

#endif // IDIFFPATCHER_H
