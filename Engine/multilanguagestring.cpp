#include "multilanguagestring.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{

    void MultiLanguageString::SetData(const QHash<QString,QString>& Data)
    {
        this->Data = Data;
    }

    QHash<QString,QString> MultiLanguageString::GetData()
    {
        return Data;
    }

    void MultiLanguageString::Clear()
    {
        Data.clear();
    }

    void MultiLanguageString::SetTranslation(const QString &Language, const QString &Translation)
    {
         Data[Language] = Translation;
    }
    QString MultiLanguageString::GetTranslation(const QString &Language)
    {
        if(Language.isEmpty())
        {
            return Data["en"];
        }
        return Data[Language];
    }

    void MultiLanguageString::ParseXml(QXmlStreamReader* XmlStreamReader)
    {
        Clear();
        if(XmlStreamReader->attributes().count() > 0)
        {
            foreach(QXmlStreamAttribute attr, XmlStreamReader->attributes())
            {
                SetTranslation(attr.name().toString(),attr.value().toString());
            }

        }else
        {
            XmlStreamReader->readNext();
            SetTranslation("en",XmlStreamReader->text().toString());
        }

    }

    bool MultiLanguageString::IsEmpty()
    {
        return Data.isEmpty();
    }

    void MultiLanguageString::WriteXml(QXmlStreamWriter* XmlStreamWriter)
    {

        QHash<QString, QString>::iterator i;
        for (i = Data.begin(); i != Data.end(); ++i)
        {
            if(!i.key().isEmpty())
            {
                XmlStreamWriter->writeAttribute(i.key(),i.value());
            }
        }

    }
}
