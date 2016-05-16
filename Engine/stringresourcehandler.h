#ifndef STRINGRESOURCEHANDLER_H
#define STRINGRESOURCEHANDLER_H
#include "engine_global.h"

#include "resourcehandlerabstract.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT StringResourceHandler : public ResourceHandlerAbstract
    {
        Q_OBJECT
        QString Value;
    public:
        explicit StringResourceHandler(QObject *parent = 0);

    signals:

    public slots:
        virtual QScriptValue get();
        QString GetString();
        void SetString(const QString & value);
    };
}

#endif // STRINGRESOURCEHANDLER_H
