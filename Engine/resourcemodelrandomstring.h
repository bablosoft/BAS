#ifndef RESOURCEMODELRANDOMSTRING_H
#define RESOURCEMODELRANDOMSTRING_H
#include "engine_global.h"

#include "resourcemodelabstract.h"

namespace BrowserAutomationStudioFramework
{

    class ENGINESHARED_EXPORT ResourceModelRandomString : public ResourceModelAbstract
    {
        Q_OBJECT
        QString Value;
    public:
        explicit ResourceModelRandomString(QObject *parent = 0);

    signals:

    public slots:
        virtual QString GetTypeId();
        QString GetValue();
        void SetValue(const QString& val);
    };

}
#endif // RESOURCEMODELRANDOMSTRING_H
