#ifndef IVALIDATOR_H
#define IVALIDATOR_H

#include "engine_global.h"

#include <QObject>


namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IValidator : public QObject
    {
        Q_OBJECT
    public:
        explicit IValidator(QObject *parent = 0);
        virtual bool Validate() = 0;
    signals:

    public slots:

    };
}

#endif // IVALIDATOR_H
