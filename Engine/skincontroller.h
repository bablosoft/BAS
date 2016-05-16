#ifndef SKINCONTROLLER_H
#define SKINCONTROLLER_H
#include "engine_global.h"

#include "iskincontroller.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT SkinController : public ISkinController
    {
        Q_OBJECT
    public:
        explicit SkinController(QObject *parent = 0);

    signals:

    public slots:
        virtual void ApplyTheme(const QString & theme);
    };
}
#endif // SKINCONTROLLER_H
