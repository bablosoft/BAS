#ifndef RESOURCEMODELFIXEDSTRING_H
#define RESOURCEMODELFIXEDSTRING_H
#include "engine_global.h"


#include "resourcemodelabstract.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ResourceModelFixedString : public ResourceModelAbstract
    {
        Q_OBJECT
        QString Value;
        bool NotEmpty;
    public:
        explicit ResourceModelFixedString(QObject *parent = 0);

    signals:

    public slots:
        QString GetValue();
        void SetValue(const QString& Value);
        bool GetNotEmpty();
        void SetNotEmpty(bool NotEmpty);
        virtual QString GetTypeId();
    };
}

#endif // RESOURCEMODELFIXEDSTRING_H
