#ifndef IHTMLPARSERFACTORY_H
#define IHTMLPARSERFACTORY_H

#include "engine_global.h"

#include <QObject>
#include "ihtmlparser.h"

namespace BrowserAutomationStudioFramework
{
    class ENGINESHARED_EXPORT IHtmlParserFactory : public QObject
    {
        Q_OBJECT
    public:
        explicit IHtmlParserFactory(QObject *parent = 0);
        virtual IHtmlParser * GetHtmlParser() = 0;
    signals:

    public slots:

    };
}

#endif // IHTMLPARSERFACTORY_H
