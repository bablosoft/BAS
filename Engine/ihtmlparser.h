#ifndef IHTMLPARSER_H
#define IHTMLPARSER_H

#include "engine_global.h"
#include <QObject>

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IHtmlParser : public QObject
    {
        Q_OBJECT
    public:
        explicit IHtmlParser(QObject *parent = 0);

    signals:

    public slots:
        virtual void Parse(const QString& page) = 0;
        virtual QString XpathXml(const QString& query) = 0;
        virtual QString XpathText(const QString& query) = 0;
        virtual QStringList XpathXmlList(const QString& query) = 0;
        virtual QStringList XpathTextList(const QString& query) = 0;
        virtual int XpathCount(const QString& query) = 0;
        virtual bool XpathExist(const QString& query) = 0;
    };
}

#endif // IHTMLPARSER_H
