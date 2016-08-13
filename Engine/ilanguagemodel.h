#ifndef ILANGUAGEMODEL_H
#define ILANGUAGEMODEL_H
#include "engine_global.h"
#include <QObject>
#include <QStringList>
#include <QList>
namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT ILanguageModel : public QObject
    {
        Q_OBJECT
    public:
        explicit ILanguageModel(QObject *parent = 0);
        virtual QStringList GetEngineAvailableLanguages() = 0;
        virtual QList<int> GetScriptAvailableLanguages() = 0;
        virtual void SetScriptAvailableLanguages(const QList<int>& indexes) = 0;
        virtual QString GetScriptAvailableLanguagesString() = 0;
        virtual void SetScriptAvailableLanguagesString(const QString& val) = 0;
        virtual void ChangeDefaultLanguage(const QString& lang) = 0;
        virtual void SetInterfaceLanguage(const QString& lang) = 0;
        virtual QString GetInterfaceLanguage() = 0;
    signals:
        void ScriptAvailableLanguagesChanged();
        void DefaultLanguageChanged(const QString& lang);
    public slots:

    };
}

#endif // ILANGUAGEMODEL_H
