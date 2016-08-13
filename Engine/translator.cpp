#include "translator.h"
#include <QCoreApplication>
#include <QVariant>
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    Translator::Translator(QObject *parent) :
        ITranslator(parent)
    {
        LastLanguage = 0;
    }
    void Translator::Translate(const QString &lang)
    {

        if(LastLanguage != 0)
        {
            QCoreApplication::removeTranslator(LastLanguage);
            LastLanguage->deleteLater();
            LastLanguage = 0;
        }

        LastLanguage = new QTranslator(this);
        bool res = LastLanguage->load(lang, Directory);
        QCoreApplication::installTranslator(LastLanguage);
        qApp->setProperty("lang",QVariant(lang));

    }

    void Translator::SetDirectory(const QString &Directory)
    {
        this->Directory = Directory;
    }
}
