#ifndef IRESOURCEWIDGETFACTORY_H
#define IRESOURCEWIDGETFACTORY_H
#include "engine_global.h"

#include <QObject>
#include "iresourcewidget.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IResourceWidgetFactory : public QObject
    {
        Q_OBJECT
    public:
        explicit IResourceWidgetFactory(QObject *parent = 0);
        virtual IResourceWidget * CreateObject() = 0;
    signals:

    public slots:

    };
}

#endif // IRESOURCEWIDGETFACTORY_H
