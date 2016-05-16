#include "htmlparserfactory.h"
#include "htmlparser.h"
#include "every_cpp.h"

namespace BrowserAutomationStudioFramework
{
    HtmlParserFactory::HtmlParserFactory(QObject *parent) :
        IHtmlParserFactory(parent)
    {
    }

    IHtmlParser * HtmlParserFactory::GetHtmlParser()
    {
        return new HtmlParser();
    }
}
