#ifndef HTMLPARSERFACTORY_H
#define HTMLPARSERFACTORY_H


#include "engine_global.h"

#include <QObject>
#include "ihtmlparserfactory.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT HtmlParserFactory : public IHtmlParserFactory
    {
        Q_OBJECT
    public:
        explicit HtmlParserFactory(QObject *parent = 0);
        virtual IHtmlParser * GetHtmlParser();
    signals:

    public slots:

    };
}

#endif // HTMLPARSERFACTORY_H
