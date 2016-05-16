#ifndef ITRANSLATOR_H
#define ITRANSLATOR_H
#include "engine_global.h"

#include <QObject>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ITranslator : public QObject
    {
        Q_OBJECT
    public:
        explicit ITranslator(QObject *parent = 0);
        virtual void Translate(const QString &lang) = 0;
        virtual void SetDirectory(const QString &directory) = 0;
    signals:

    public slots:

    };
}

#endif // ITRANSLATOR_H
