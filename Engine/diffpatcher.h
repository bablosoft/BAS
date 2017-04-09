#ifndef DIFFPATCHER_H
#define DIFFPATCHER_H

#include "idiffpatcher.h"

#include "engine_global.h"


namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT DiffPatcher : public IDiffPatcher
    {
        Q_OBJECT
        QString LastText;
        public:
            explicit DiffPatcher(QObject *parent = 0);
            virtual void Init(const QString& Text);
            virtual QString ApplyPatch(const QString& PatchString);

    };
}

#endif // DIFFPATCHER_H
