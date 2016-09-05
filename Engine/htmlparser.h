#ifndef HTMLPARSER_H
#define HTMLPARSER_H
#include "engine_global.h"
#include <QObject>

#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>
#include "ihtmlparser.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT HtmlParser : public IHtmlParser
    {
        Q_OBJECT
        QString Page;
        bool NeedParse;
        htmlParserCtxtPtr ctxt;
        htmlDocPtr htmlDoc;
        void ParseInternal();
        void Release();
        void RecursiveGetText(xmlNodePtr nodePtr, QString *text);
    public:
        explicit HtmlParser(QObject *parent = 0);
        virtual ~HtmlParser();
    signals:

    public slots:
        virtual void Parse(const QString& page);
        virtual QString XpathXml(const QString& query);
        virtual QString XpathText(const QString& query);
        virtual QStringList XpathXmlList(const QString& query);
        virtual QStringList XpathTextList(const QString& query);
        virtual int XpathCount(const QString& query);
        virtual bool XpathExist(const QString& query);

    };
}

#endif // HTMLPARSER_H
