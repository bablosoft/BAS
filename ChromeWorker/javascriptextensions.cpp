#include "javascriptextensions.h"
#include <fstream>
#include "log.h"
#include "picojson.h"
#include "replaceall.h"
#include "split.h"

JavaScriptExtensions::JavaScriptExtensions()
{

}

std::string JavaScriptExtensions::GetReferrerExtension(const std::string& Referrer)
{
    std::string rescode;
    //if(!Referrer.empty())
    {
        rescode += std::string("Object.defineProperty(window.document, 'referrer', {"
        "    configurable: true, get: function() {"
         "        return ") + picojson::value(Referrer).serialize() + std::string(";"
         "    }"
         "});");
    }
    return rescode;
}
std::string JavaScriptExtensions::GetReferrerEmptyExtension()
{
    return "delete window.document.referrer;";
}


std::string JavaScriptExtensions::GetUserAgentExtension(const std::string& UserAgent)
{
    std::string rescode;
    if(!UserAgent.empty())
    {
        rescode += std::string("Object.defineProperty(window.navigator, 'userAgent', {"
        "    configurable: true, get: function() {"
         "        return ") + picojson::value(UserAgent).serialize() + std::string(";"
         "    }"
         "});");

        rescode += std::string("Object.defineProperty(window.navigator, 'appVersion', {"
        "    configurable: true, get: function() {"
         "        return ") + picojson::value(ReplaceAll( UserAgent, "Mozilla/", "")).serialize() + std::string(";"
         "    }"
         "});");

        rescode += std::string("Object.defineProperty(window.navigator, 'vendor', {"
        "    configurable: true, get: function() {"
         "        return ") + picojson::value("").serialize() + std::string(";"
         "    }"
         "});");

        rescode += std::string("Object.defineProperty(window.navigator, 'platform', {"
        "    configurable: true, get: function() {"
         "        return ") + picojson::value("").serialize() + std::string(";"
         "    }"
         "});");
    }
    return rescode;
}


std::string JavaScriptExtensions::GetUserAgentEmptyExtension()
{
    std::string rescode;
    rescode += "delete window.navigator.userAgent;";
    rescode += "delete window.navigator.appVersion;";
    rescode += "delete window.navigator.vendor;";
    rescode += "delete window.navigator.platform;";
    return rescode;
}

std::string JavaScriptExtensions::GetLanguage(const std::string& Language)
{
    std::string rescode;
    if(!Language.empty())
    {
        rescode += std::string("Object.defineProperty(window.navigator, 'language', {"
        "    configurable: true, get: function() {"
         "        return ") + picojson::value(Language).serialize() + std::string(";"
         "    }"
         "});");

        rescode += std::string("Object.defineProperty(window.navigator, 'languages', {"
        "    configurable: true, get: function() {"
         "        return [") + picojson::value(Language).serialize() + std::string("];"
         "    }"
         "});");


        rescode += std::string("if(typeof(Intl.DateTimeFormatOriginal) == 'undefined')"
        "{"
            "Intl.DateTimeFormatOriginal = Intl.DateTimeFormat();"
            "Intl.ResolvedOptionsOriginal = Intl.DateTimeFormatOriginal.resolvedOptions();"
            "Intl.ResolvedOptionsOriginal['locale'] = ") + picojson::value(split(split(Language,';')[0],',')[0]).serialize() + std::string(";"
            "Object.defineProperty(Intl, 'DateTimeFormat', {"
                "configurable: true, get: function() {"
                     "return function(){"
                        "var dtres = Intl.DateTimeFormatOriginal;"
                        "dtres.resolvedOptions = function()"
                        "{"
                            "return Intl.ResolvedOptionsOriginal;"
                        "};"
                        "return dtres;"
                     "};"
                 "}"
             "});"
        "}else"
        "{"
            "Intl.ResolvedOptionsOriginal['locale'] = ") + picojson::value(split(split(Language,';')[0],',')[0]).serialize() + std::string(";"
        "};");


    }
    return rescode;
}

std::string JavaScriptExtensions::GetEmptyLanguage()
{
    std::string rescode;
    rescode += "delete window.navigator.language;";
    rescode += "delete window.navigator.languages;";
    return rescode;
}



std::string JavaScriptExtensions::GetBasicExtension(bool IsRecord)
{

    std::string additional;
    if(IsRecord)
    {
        try
        {
            std::ifstream ifs("html/main/css_path.js");
            additional = std::string((std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));
        }catch(...){}
        try
        {
            std::ifstream ifs("html/main/xpath_path.js");
            additional += std::string((std::istreambuf_iterator<char>(ifs)),(std::istreambuf_iterator<char>()));
        }catch(...){}
        //WORKER_LOG(additional);
    }

    std::string inspect_script;

    if(IsRecord)
    {
        inspect_script = std::string(
        "var BrowserAutomationStudio_CssSelectorGenerator2 = new CssSelectorGenerator({selectors: ['tag', 'nthchild']});"
        "var BrowserAutomationStudio_CssSelectorGenerator = new CssSelectorGenerator({selectors: ['id', 'tag', 'nthchild']});"
        "var BrowserAutomationStudio_CssSelectorGenerator3 = new CssSelectorGenerator({selectors: ['id', 'class', 'tag', 'nthchild']});"

        "function BrowserAutomationStudio_InspectElement(x,y)"
        "{"
            "var el = document.elementFromPoint(x,y);"
            "if(el){"
                "var rect = el.getBoundingClientRect();"
                "var css = '';"
                "var css2 = '';"
                "var css3 = '';"
                "var match = '';"
                "var xpath = '';"
                "try"
                "{"
                    "css = ' >CSS> ' + BrowserAutomationStudio_CssSelectorGenerator.getSelector(el);"
                    "css2 = ' >CSS> ' + BrowserAutomationStudio_CssSelectorGenerator2.getSelector(el);"
                    "css3 = ' >CSS> ' + BrowserAutomationStudio_CssSelectorGenerator3.getSelector(el);"
                    "match = '>MATCH>' + el.outerHTML.substr(0,40).replace(/(?:\\r\\n|\\r|\\n)/g, ' ');"
                    "xpath = ' >XPATH> ' + BrowserAutomationStudio_CreateXPathFromElement(el);"
                "}catch(e){};"
                "var is_frame=false;"
                "var frame_name='';"
                "var frame_url='';"
                "var frame_tag_html='';"
                "var frame_index=0;"
                "var r = BrowserAutomationStudio_GetInternalBoundingRect(el);"
                "var x_with_padding=r.left;"
                "var y_with_padding=r.top;"
                "if(el.tagName.toLowerCase()=='iframe' || el.tagName.toLowerCase()=='frame')"
                "{"
                    "is_frame=true;"
                    "frame_name=el.getAttribute('name') || '';"
                    "frame_url=el.getAttribute('src') || '';"
                    "frame_tag_html=el.outerHTML || '';"
                    "frame_index=BrowserAutomationStudio_GetFrameIndex(el);"
                "}"
                "browser_automation_studio_inspect_result(parseInt(rect.left),parseInt(rect.top),parseInt(rect.width),parseInt(rect.height),css,css,css2,css3,match,xpath,x + document.body.scrollLeft,y + document.body.scrollTop,true,is_frame,frame_name,frame_url,frame_tag_html,frame_index,x_with_padding,y_with_padding);"
            "}else{"
                "browser_automation_studio_inspect_result(0,0,0,0,'','','','','','',x,y,false,false,'','','',0,0,0);"
            "}"
        "};"
        "function BrowserAutomationStudio_SetHighlightElements(elements)"
        "{"
            "window.BrowserAutomationStudio_HighlightElements = elements;"
        "}"
        "function BrowserAutomationStudio_Highlight()"
        "{"
            "var res = '';var elements=window.BrowserAutomationStudio_HighlightElements;"
            "try{"
                "for(var i = 0;i<elements.length;i++){"
                    "var el = elements[i];"

                    "if(window.getComputedStyle(el)['display'] != 'none' && window.getComputedStyle(el)['visibility'] != 'hidden')"
                    "{"
                        "var r = BrowserAutomationStudio_GetInternalBoundingRect(el);"

                        "var xi = parseInt(r.left);"
                        "var yi = parseInt(r.top);"
                        "var widthi = parseInt(r.width);"
                        "var heighti = parseInt(r.height);"

                        "var x = xi.toString();"
                        "var y = yi.toString();"
                        "var width = widthi.toString();"
                        "var height = heighti.toString();"

                        "if(widthi > 0 && heighti > 0 && x.length>0 && y.length > 0 && width.length > 0 && height.length > 0)"
                        "{"
                            "if(res.length>0)res+=';';"
                            "res += parseInt(r.left) + ';' + parseInt(r.top) + ';' + parseInt(r.width) + ';' + parseInt(r.height);"
                        "}"
                    "}"
                "};"
            "}catch(e){}"
            "browser_automation_studio_highlight_result(res);"
        "}");
    }
    return
    additional +
    inspect_script
     + std::string(
    "function BrowserAutomationStudio_GetFrameIndex(element){"
        "try{"
        "var frame_index = Array.prototype.slice.call(window.frames).indexOf(element.contentWindow);if(frame_index<0)frame_index=0;"
        "return frame_index;"
        "}catch(e){};"
        "return 0;"
    "}"
    "function BrowserAutomationStudio_GetInternalBoundingRect(element){"
        "var style = window.getComputedStyle(element);"
        "var margin = { left: parseInt(style['margin-left']), right: parseInt(style['margin-right']), top: parseInt(style['margin-top']), bottom: parseInt(style['margin-bottom'])};"
        "var padding = { left: parseInt(style['padding-left']), right: parseInt(style['padding-right']), top: parseInt(style['padding-top']), bottom: parseInt(style['padding-bottom'])};"
        "var border = { left: parseInt(style['border-left']), right: parseInt(style['border-right']), top: parseInt(style['border-top']), bottom: parseInt(style['border-bottom']) };"
        "var rect = element.getBoundingClientRect();"
        "rect = {left: parseInt(rect.left + padding.left + border.left),right: parseInt(rect.right - padding.right - border.right),top: parseInt(rect.top + padding.top + border.top),bottom: parseInt(rect.bottom  - padding.top - border.top)};"
        "rect.width = rect.right - rect.left;"
        "rect.height = rect.bottom - rect.top;"
        "return rect;"
    "}"
    "function BrowserAutomationStudio_ScrollToElement(el)"
    "{"
        "if(el)"
        "{"

            //"console.log('Moving to element');"
            //"console.log(el);"
            "el.scrollIntoViewIfNeeded(true);"
            //"document.body.scrollLeft = xc - window.innerWidth/2;"
            //"document.body.scrollTop = yc - window.innerHeight/2;"

            "setTimeout(function(){"
                "var rect = el.getBoundingClientRect();"

                "var xc = Math.floor(rect.left + rect.width/2);"
                "var yc = Math.floor(rect.top + rect.height/2);"
                "var x1 = Math.floor(rect.left);"
                "var y1 = Math.floor(rect.top);"
                "var x2 = Math.floor(rect.right);"
                "var y2 = Math.floor(rect.bottom);"

                //"if(x1 > 0 && x1 < window.innerWidth && y1 > 0 && y1 < window.innerHeight && x2 > 0 && x2 < window.innerWidth && y2 > 0 && y2 < window.innerHeight)"
                //"{"

                "var res = document.body.scrollLeft + ',' + document.body.scrollTop + ',' + xc + ',' + yc;"

                "if(x1<0)x1=0;"
                "if(x1>window.innerWidth-2)x1=window.innerWidth-2;"

                "if(y1<0)y1=0;"
                "if(y1>window.innerHeight-2)y1=window.innerHeight-2;"

                "if(x2<=x1)x2=x1+1;"
                "if(x2>window.innerWidth-1)x2=window.innerWidth-1;"

                "if(y2<=y1)y2=y1+1;"
                "if(y2>window.innerHeight-1)y2=window.innerHeight-1;"

                "res += ',' + x1 + ',' + y1 + ',' + x2 + ',' + y2;"

                "browser_automation_studio_result(res);"

                //"return;"
                //"}"
            "}, 100)"

        "}else{"
            "browser_automation_studio_result('BAS_NOT_EXISTS');"
        "}"

    "}"

    "function BrowserAutomationStudio_ScrollToCoordinates(x,y)"
    "{"
        "try{"
            "var x = Math.floor(x);"
            "var y = Math.floor(y);"

            "if(x > document.body.scrollLeft && x < document.body.scrollLeft + window.innerWidth && y > document.body.scrollTop && y < document.body.scrollTop + window.innerHeight)"
            "{"
                "var res = document.body.scrollLeft + ',' + document.body.scrollTop + ',' + x.toString() + ',' + y.toString();"
                "browser_automation_studio_result(res);"
                "return;"
            "}"

            //"console.log('Moving to coordinates ');"
            //"console.log(x - window.innerWidth/2);"
            //"console.log(y - window.innerHeight/2);"
            "document.body.scrollLeft = x - window.innerWidth/2;"
            "document.body.scrollTop = y - window.innerHeight/2;"
        "}catch(e)"
        "{"
            "var res = '0,0,' + x.toString() + ',' + y.toString();"
            "browser_automation_studio_result(res);"
            "return;"
        "}"

        "setTimeout(function(){"
            "try{"
                "x-=document.body.scrollLeft;"
                "if(x<0)x=0;"
                "if(x>window.innerWidth-2)x=window.innerWidth-2;"
                "x+=document.body.scrollLeft;"

                "y-=document.body.scrollTop;"
                "if(y<0)y=0;"
                "if(y>window.innerHeight-2)y=window.innerHeight-2;"
                "y+=document.body.scrollTop;"

                "var res = document.body.scrollLeft + ',' + document.body.scrollTop + ',' + x.toString() + ',' + y.toString();"
                "browser_automation_studio_result(res);"
            "}catch(e)"
            "{"
                "var res = '0,0,' + x.toString() + ',' + y.toString();"
                "browser_automation_studio_result(res);"
                "return;"
            "}"
        "}, 100)"
    "}"

    "function BrowserAutomationStudio_ScrollToCoordinatesNoResult(x,y)"
    "{"
        "if(x > document.body.scrollLeft && x < document.body.scrollLeft + window.innerWidth && y > document.body.scrollTop && y < document.body.scrollTop + window.innerHeight)"
        "{"
            "return;"
        "}"
        "document.body.scrollLeft = x - window.innerWidth/2;"
        "document.body.scrollTop = y - window.innerHeight/2;"
    "}"
    "function BrowserAutomationStudio_ScrollUp()"
    "{"
        "document.body.scrollTop-=100;"
    "}"
    "function BrowserAutomationStudio_ScrollDown()"
    "{"
        "document.body.scrollTop+=100;"
    "}"
    "function BrowserAutomationStudio_ScrollRight()"
    "{"
        "document.body.scrollLeft+=100"
    "}"
    "function BrowserAutomationStudio_ScrollLeft()"
    "{"
        "document.body.scrollLeft-=100"
    "}"
    "function BrowserAutomationStudio_ScrollRightRight()"
    "{"
        "document.body.scrollLeft+=10000"
    "}"
    "function BrowserAutomationStudio_ScrollLeftLeft()"
    "{"
        "document.body.scrollLeft-=10000"
    "}"
    "function BrowserAutomationStudio_MatchAllIteration(res,el,mask)"
    "{"
        "if(el == document)"
            "el = document.body;"
        "if(el.outerHTML.indexOf(mask)<0)"
            "return [];"
        "var no_child_match = true;"
        "try{"
            "for(var i = 0;i<el.childNodes.length;i++)"
            "{"
                "var e = el.childNodes[i];"
                "var content = '';"
                "try{"
                    "content = e.outerHTML;"
                "}catch(e)"
                "{"
                    "continue;"
                "}"
                "if(!content || content.length === 0)"
                    "continue;"
                "if(content.indexOf(mask)>=0)"
                "{"
                    "no_child_match = false;"
                    "res.concat(BrowserAutomationStudio_MatchAllIteration(res,e,mask));"
                "}"
            "}"
            "if(no_child_match)"
            "{"
                "res.push(el);"
            "}"
        "}"
        "catch(e){"
        "}"
        "return res;"
    "}"
    "function BrowserAutomationStudio_MatchIteration(el,mask)"
    "{"
        "if(el == document)"
            "el = document.body;"
        "if(el.outerHTML.indexOf(mask)<0)"
            "return null;"
        "for(var i = 0;i<el.childNodes.length;i++)"
        "{"
            "var e = el.childNodes[i];"
            "var content = '';"
            "try{"
                "content = e.outerHTML;"
            "}catch(e)"
            "{"
                "continue;"
            "}"
            "if(!content || content.length === 0)"
                "continue;"
            "if(content.indexOf(mask)>=0)"
            "{"
                "return BrowserAutomationStudio_MatchIteration(e,mask);"
            "}"
        "}"
        "return el;"
    "}"
    "function BrowserAutomationStudio_FindElement(search)"
    "{"
        "try{"
            "var json = JSON.parse(search);"
            "var res = document;"
            "for(var i = 0;i+1<json.length;i+=2)"
            "{"
                "var select_type = json[i];"
                "var select_value = json[i+1];"
                "if(select_type == 'xpath')"
                "{"
                    "res = document.evaluate(select_value, res, null, XPathResult.ORDERED_NODE_SNAPSHOT_TYPE, null ).snapshotItem(0);"
                "}"
                "if(select_type == 'xpath_all')"
                "{"
                    "var q = document.evaluate(select_value, res, null, XPathResult.ORDERED_NODE_SNAPSHOT_TYPE, null );"
                    "var len = q.snapshotLength;res=[];"
                    "for(var it = 0;it<len;it++)res.push(q.snapshotItem(it));"
                "}"
                "if(select_type == 'css')"
                "{"
                    "res = res.querySelector(select_value);"
                "}"
                "if(select_type == 'all')"
                "{"
                    "res = res.querySelectorAll(select_value);"
                "}"
                "if(select_type == 'at')"
                "{"
                    "res = res[parseInt(select_value)];"
                "}"
                "if(select_type == 'match')"
                "{"
                    "res = BrowserAutomationStudio_MatchIteration(res,select_value);"
                "}"
                "if(select_type == 'match_all')"
                "{"
                    "res = BrowserAutomationStudio_MatchAllIteration([],res,select_value);"
                "}"
                "if(select_type == 'position')"
                "{"
                    "var x = 0;"
                    "var y = 0;"
                    "try{"
                        "x = parseInt(select_value.split(',')[0].trim());"

                        "y = parseInt(select_value.split(',')[1].trim());"
                    "}catch(e){};"
                    "BrowserAutomationStudio_ScrollToCoordinatesNoResult(x,y);"
                    "res = document.elementFromPoint(x - document.body.scrollLeft,y - document.body.scrollTop);"
                "}"
                "if(!res)"
                    "return null;"
            "}"
            "if(res == document)"
                "return document.body;"
            "return res;"
        "}catch(e){return null}"
    "}"
    "function BrowserAutomationStudio_Sleep(milliseconds){"
      "confirm('BrowserAutomationStudio_Sleep' + milliseconds.toString())"
    "}");
}

std::string JavaScriptExtensions::GetJqueryExtension()
{
    return "";
}
