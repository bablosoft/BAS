#ifndef RESOURCEMODELRANDOMINTEGER_H
#define RESOURCEMODELRANDOMINTEGER_H
#include "engine_global.h"

#include "resourcemodelabstract.h"

namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT ResourceModelRandomInteger : public ResourceModelAbstract
    {
        Q_OBJECT
        int MinUserValue;
        int MaxUserValue;
        int MaxDesignValue;
        int MinDesignValue;
    public:
        explicit ResourceModelRandomInteger(QObject *parent = 0);

    signals:

    public slots:
        int GetMaxUserValue();
        void SetMaxUserValue(int MaxUserValue);
        int GetMinUserValue();
        void SetMinUserValue(int MinUserValue);
        virtual QString GetTypeId();
        int GetMaxDesignValue();
        void SetMaxDesignValue(int MaxDesignValue);
        int GetMinDesignValue();
        void SetMinDesignValue(int MinDesignValue);
    };

}
#endif // RESOURCEMODELRANDOMINTEGER_H
