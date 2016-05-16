#ifndef TRANSLATOR_H
#define TRANSLATOR_H
#include "engine_global.h"

#include "itranslator.h"
#include <QTranslator>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT Translator : public ITranslator
    {
        Q_OBJECT
        QTranslator *LastLanguage;
        QString Directory;
    public:
        explicit Translator(QObject *parent = 0);
        virtual void Translate(const QString &lang);
        virtual void SetDirectory(const QString &Directory);
    signals:

    public slots:

    };
}

#endif // TRANSLATOR_H
