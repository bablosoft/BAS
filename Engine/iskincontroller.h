#ifndef ISKINCONTROLLER_H
#define ISKINCONTROLLER_H
#include "engine_global.h"

#include <QObject>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ISkinController : public QObject
    {
        Q_OBJECT
    public:
        explicit ISkinController(QObject *parent = 0);

    signals:

    public slots:
        virtual void ApplyTheme(const QString & theme) = 0;
    };
}

#endif // ISKINCONTROLLER_H
