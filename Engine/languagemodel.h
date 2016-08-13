#ifndef LANGUAGEMODEL_H
#define LANGUAGEMODEL_H
#include "engine_global.h"

#include <QObject>
#include "ilanguagemodel.h"


namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT LanguageModel : public ILanguageModel
    {
        Q_OBJECT
        QStringList EngineAvailableLanguages;
        QList<int> ScriptAvailableLanguages;
        QString InterfaceLanguage;
    public:
        explicit LanguageModel(QObject *parent = 0);
        virtual QStringList GetEngineAvailableLanguages();
        virtual QList<int> GetScriptAvailableLanguages();
        virtual void SetScriptAvailableLanguages(const QList<int>& indexes);
        virtual QString GetScriptAvailableLanguagesString();
        virtual void SetScriptAvailableLanguagesString(const QString& val);
        virtual void ChangeDefaultLanguage(const QString& lang);
        virtual void SetInterfaceLanguage(const QString& lang);
        virtual QString GetInterfaceLanguage();
    signals:

    public slots:

    };
}

#endif // LANGUAGEMODEL_H
