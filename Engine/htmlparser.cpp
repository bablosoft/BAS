#include "htmlparser.h"
#include "every_cpp.h"


namespace BrowserAutomationStudioFramework
{
    HtmlParser::HtmlParser(QObject *parent) :
         IHtmlParser(parent)
    {
        NeedParse = true;
        htmlDoc = 0;
        ctxt = 0;
    }

    HtmlParser::~HtmlParser()
    {
        Release();
    }

    void HtmlParser::Release()
    {
        if(htmlDoc)
        {
            xmlFreeDoc(htmlDoc);
            htmlDoc = 0;
        }
        if(ctxt)
        {
            htmlFreeParserCtxt(ctxt);
            ctxt = 0;
        }
    }

    void HtmlParser::Parse(const QString& page)
    {
        Release();
        Page = page;
        NeedParse = true;
    }

    void HtmlParser::ParseInternal()
    {
        ctxt = htmlNewParserCtxt();
        htmlDoc = htmlCtxtReadMemory(ctxt, Page.toUtf8().constData(), strlen(Page.toUtf8().constData()), "", "UTF-8", HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);
        NeedParse = false;
        Page.clear();
    }

    QStringList HtmlParser::XpathXmlList(const QString& query)
    {
        if(NeedParse)
            ParseInternal();

        QStringList res;
        xmlXPathContextPtr context = xmlXPathNewContext ( htmlDoc );
        xmlXPathObjectPtr result = xmlXPathEvalExpression ((xmlChar*) query.toUtf8().constData(), context);

        xmlXPathFreeContext(context);
        if (result == NULL) {

        }
        else {
            xmlNodeSetPtr nodeSet = result->nodesetval;
            if ( !xmlXPathNodeSetIsEmpty ( nodeSet ) ) {
                for (int i = 0; i < nodeSet->nodeNr; i++ ) {
                    xmlNodePtr  nodePtr;
                    nodePtr = nodeSet->nodeTab[i];
                    if(nodePtr && nodePtr->type == XML_ATTRIBUTE_NODE && nodePtr->children && nodePtr->children->content)
                    {
                        QString xml = QString::fromUtf8((char*)nodePtr->children->content);
                        res.append(xml);
                        //break;
                    }else
                    {
                        xmlBufferPtr buffer = xmlBufferCreate();
                            xmlNodeDump(buffer,htmlDoc,nodePtr,10,1);
                            res.append(QString::fromUtf8((char*)buffer->content));
                        xmlBufferFree(buffer);
                        //break;
                    }
                }
            }
        }

        xmlXPathFreeObject (result);

        return res;
    }

    QStringList HtmlParser::XpathTextList(const QString& query)
    {
        if(NeedParse)
            ParseInternal();

        QStringList res;
        xmlXPathContextPtr context = xmlXPathNewContext ( htmlDoc );
        xmlXPathObjectPtr result = xmlXPathEvalExpression ((xmlChar*) query.toUtf8().constData(), context);

        xmlXPathFreeContext(context);
        if (result == NULL) {

        }
        else {
            xmlNodeSetPtr nodeSet = result->nodesetval;
            if ( !xmlXPathNodeSetIsEmpty ( nodeSet ) ) {
                for (int i = 0; i < nodeSet->nodeNr; i++ ) {
                    xmlNodePtr  nodePtr;
                    nodePtr = nodeSet->nodeTab[i];
                    if(nodePtr)
                    {
                        QString r;
                        RecursiveGetText(nodePtr,&r);
                        res.append(r);
                        //break;
                    }
                }
            }
        }

        xmlXPathFreeObject (result);

        return res;
    }

    QString HtmlParser::XpathXml(const QString& query)
    {
        if(NeedParse)
            ParseInternal();

        QString res;
        xmlXPathContextPtr context = xmlXPathNewContext ( htmlDoc );
        xmlXPathObjectPtr result = xmlXPathEvalExpression ((xmlChar*) query.toUtf8().constData(), context);

        xmlXPathFreeContext(context);
        if (result == NULL) {

        }
        else {
            xmlNodeSetPtr nodeSet = result->nodesetval;
            if ( !xmlXPathNodeSetIsEmpty ( nodeSet ) ) {
                for (int i = 0; i < nodeSet->nodeNr; i++ ) {
                    xmlNodePtr  nodePtr;
                    nodePtr = nodeSet->nodeTab[i];
                    if(nodePtr && nodePtr->type == XML_ATTRIBUTE_NODE && nodePtr->children && nodePtr->children->content)
                    {
                        QString xml = QString::fromUtf8((char*)nodePtr->children->content);
                        res = xml;
                        break;
                    }else
                    {
                        xmlBufferPtr buffer = xmlBufferCreate();
                            xmlNodeDump(buffer,htmlDoc,nodePtr,10,1);
                            res = QString::fromUtf8((char*)buffer->content);
                        xmlBufferFree(buffer);
                        break;
                    }
                }
            }
        }

        xmlXPathFreeObject (result);

        return res;
    }

    QString HtmlParser::XpathText(const QString& query)
    {
        if(NeedParse)
            ParseInternal();

        QString res;
        xmlXPathContextPtr context = xmlXPathNewContext ( htmlDoc );
        xmlXPathObjectPtr result = xmlXPathEvalExpression ((xmlChar*) query.toUtf8().constData(), context);

        xmlXPathFreeContext(context);
        if (result == NULL) {

        }
        else {
            xmlNodeSetPtr nodeSet = result->nodesetval;
            if ( !xmlXPathNodeSetIsEmpty ( nodeSet ) ) {
                for (int i = 0; i < nodeSet->nodeNr; i++ ) {
                    xmlNodePtr  nodePtr;
                    nodePtr = nodeSet->nodeTab[i];
                    if(nodePtr)
                    {
                        RecursiveGetText(nodePtr,&res);
                        break;
                    }
                }
            }
        }

        xmlXPathFreeObject (result);

        return res;
    }

    void HtmlParser::RecursiveGetText(xmlNodePtr nodePtr, QString *text)
    {
        xmlNodePtr it = nodePtr->children;
        while(it)
        {
            if(it->content)
            {
                text->append(QString::fromUtf8((char*)it->content));
            }
            RecursiveGetText(it,text);
            it = it->next;
        }

    }

    int HtmlParser::XpathCount(const QString& query)
    {
        if(NeedParse)
            ParseInternal();

        int res = 0;
        xmlXPathContextPtr context = xmlXPathNewContext ( htmlDoc );
        xmlXPathObjectPtr result = xmlXPathEvalExpression ((xmlChar*) query.toUtf8().constData(), context);

        xmlXPathFreeContext(context);
        if (result == NULL) {

        }
        else {
            xmlNodeSetPtr nodeSet = result->nodesetval;
            if ( !xmlXPathNodeSetIsEmpty ( nodeSet ) ) {
                res = nodeSet->nodeNr;
            }
        }

        xmlXPathFreeObject (result);

        return res;
    }
    bool HtmlParser::XpathExist(const QString& query)
    {
        return XpathCount(query)>0;
    }
}
