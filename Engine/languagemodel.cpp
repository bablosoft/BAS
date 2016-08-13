#include "languagemodel.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    LanguageModel::LanguageModel(QObject *parent) :
        ILanguageModel(parent)
    {
        EngineAvailableLanguages = QStringList()<<"en"<<"ru";
        ScriptAvailableLanguages = QList<int>()<<0;
        InterfaceLanguage = "en";
    }

    void LanguageModel::SetInterfaceLanguage(const QString& lang)
    {
        if(lang == "ru")
        {
            ScriptAvailableLanguages = QList<int>()<<0<<1;
            emit DefaultLanguageChanged("ru");
        }
        InterfaceLanguage = lang;
    }

    QString LanguageModel::GetInterfaceLanguage()
    {
        return InterfaceLanguage;
    }

    void LanguageModel::ChangeDefaultLanguage(const QString& lang)
    {
        emit DefaultLanguageChanged(lang);
    }

    QStringList LanguageModel::GetEngineAvailableLanguages()
    {
        return EngineAvailableLanguages;
    }

    QList<int> LanguageModel::GetScriptAvailableLanguages()
    {
        return ScriptAvailableLanguages;
    }

    void LanguageModel::SetScriptAvailableLanguages(const QList<int>& indexes)
    {
        ScriptAvailableLanguages = indexes;
        emit ScriptAvailableLanguagesChanged();
    }

    QString LanguageModel::GetScriptAvailableLanguagesString()
    {
        QString res;
        foreach(int index,ScriptAvailableLanguages)
        {
            if(!res.isEmpty())
                res += ",";
            res+=EngineAvailableLanguages[index];
        }
        return res;
    }

    void LanguageModel::SetScriptAvailableLanguagesString(const QString& val)
    {
        if(val.isEmpty())
            return;
        ScriptAvailableLanguages.clear();
        foreach(QString lang,val.split(","))
        {
            int index = EngineAvailableLanguages.indexOf(lang);
            if(index >= 0)
            {
                ScriptAvailableLanguages.append(index);
            }
        }
        if(ScriptAvailableLanguages.isEmpty())
        {
            ScriptAvailableLanguages<<1;
        }
        emit ScriptAvailableLanguagesChanged();
    }



}
