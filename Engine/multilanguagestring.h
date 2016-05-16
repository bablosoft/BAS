#ifndef MULTILANGUAGESTRING_H
#define MULTILANGUAGESTRING_H
#include "engine_global.h"
#include <QObject>
#include <QHash>
#include <QString>
#include <QXmlStreamReader>
namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT MultiLanguageString
    {

        QHash<QString,QString> Data;
    public:
        void SetData(const QHash<QString,QString>& Data);
        QHash<QString,QString> GetData();
        void Clear();
        void SetTranslation(const QString &Language, const QString &Translation);
        QString GetTranslation(const QString &Language);
        void ParseXml(QXmlStreamReader* XmlStreamReader);
        void WriteXml(QXmlStreamWriter* XmlStreamWriter);
        bool IsEmpty();
    };
}

#endif // MULTILANGUAGESTRING_H
