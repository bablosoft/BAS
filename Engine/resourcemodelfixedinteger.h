#ifndef RESOURCEMODELFIXEDINTEGER_H
#define RESOURCEMODELFIXEDINTEGER_H
#include "engine_global.h"

#include "resourcemodelabstract.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ResourceModelFixedInteger : public ResourceModelAbstract
    {
        Q_OBJECT
        int Value;
        int MaxValue;
        int MinValue;
    public:
        explicit ResourceModelFixedInteger(QObject *parent = 0);
        ~ResourceModelFixedInteger();
    signals:

    public slots:
        int GetValue();
        void SetValue(int Value);
        virtual QString GetTypeId();
        int GetMaxValue();
        void SetMaxValue(int MaxValue);
        int GetMinValue();
        void SetMinValue(int MinValue);
    };
}

#endif // RESOURCEMODELFIXEDINTEGER_H
