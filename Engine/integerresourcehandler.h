#ifndef INTEGERRESOURCEHANDLER_H
#define INTEGERRESOURCEHANDLER_H
#include "engine_global.h"



#include "resourcehandlerabstract.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IntegerResourceHandler : public ResourceHandlerAbstract
    {
        Q_OBJECT
        int Value;
    public:
        explicit IntegerResourceHandler(QObject *parent = 0);


    signals:

    public slots:
        virtual QScriptValue get();
        int GetInteger();
        void SetInteger(int value);
    };
}

#endif // INTEGERRESOURCEHANDLER_H
