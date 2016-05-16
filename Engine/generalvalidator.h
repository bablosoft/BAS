#ifndef GENERALVALIDATOR_H
#define GENERALVALIDATOR_H

#include <QObject>
#include "engine_global.h"

#include "iresourcewidget.h"
#include "ivalidator.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT GeneralValidator : public IValidator
    {
        Q_OBJECT
        QList<IResourceWidget*> Data;
    public:
        explicit GeneralValidator(QObject *parent = 0);
        void InsertResourceWidget(IResourceWidget* Widget);
        virtual bool Validate();
        void Clear();
    signals:

    public slots:

    };
}

#endif // GENERALVALIDATOR_H
