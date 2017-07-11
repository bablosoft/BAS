#include "v8handler.h"
#include "log.h"
#include <thread>
#include "split.h"

V8Handler::V8Handler(BrowserData* Data, PostManager* _PostManager)
{
    Changed = false;
    ChangedInspect = false;
    ChangedHighlight = false;
    ChangedLocalStorage = false;
    ChangedFrameFind = false;
    NewLocalStorage.clear();
    this->Data = Data;
    this->_PostManager = _PostManager;
}

bool V8Handler::GetResultReady()
{
    return Changed;
}

std::pair<std::string,bool> V8Handler::GetResult()
{
    std::lock_guard<std::mutex> lock(mut);

    std::pair<std::string,bool> r;
    r.first = Result;
    r.second = Changed;
    //Changed = false;
    return r;
}

std::pair<std::vector<LocalStorageDataItem>,bool> V8Handler::GetLocalStorage()
{
    std::lock_guard<std::mutex> lock(mut_local_storage);

    std::pair<std::vector<LocalStorageDataItem>,bool> r;
    r.first = NewLocalStorage;
    r.second = ChangedLocalStorage;
    ChangedLocalStorage = false;
    NewLocalStorage.clear();
    return r;
}

void V8Handler::SetResultProcessed()
{
    std::lock_guard<std::mutex> lock(mut);
    Changed = false;
}

bool V8Handler::GetInspectResultReady()
{
    return ChangedInspect;
}

std::pair<InspectResult,bool> V8Handler::GetInspectResult()
{
    std::lock_guard<std::mutex> lock(mut_inspect);

    std::pair<InspectResult,bool> r;
    r.first = _InspectResult;
    r.second = ChangedInspect;
    _InspectResult.css.clear();
    _InspectResult.match.clear();
    _InspectResult.label.clear();
    ChangedInspect = false;
    return r;
}

bool V8Handler::GetHighlightResultReady()
{
    return ChangedHighlight;
}


std::pair<HighlightResult,bool> V8Handler::GetHighlightResult()
{
    std::lock_guard<std::mutex> lock(mut_highlight);

    std::pair<HighlightResult,bool> r;
    r.first = _HighlightResult;
    r.second = ChangedHighlight;
    _HighlightResult.highlights.clear();
    ChangedHighlight = false;
    return r;
}

bool V8Handler::GetFrameFindResultReady()
{
    return ChangedFrameFind;
}


std::pair<InspectResult,bool> V8Handler::GetFrameFindResult()
{
    std::lock_guard<std::mutex> lock(mut_frame_find);

    std::pair<InspectResult,bool> r;
    r.first = _FrameFindResult;
    r.second = ChangedFrameFind;
    _FrameFindResult.css.clear();
    _FrameFindResult.match.clear();
    _FrameFindResult.label.clear();
    ChangedFrameFind = false;
    return r;
}

void V8Handler::ClearHighlightLast()
{
    std::lock_guard<std::mutex> lock(mut_highlight_last);
    HighlightLast.clear();
}


bool V8Handler::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception)
{
    if(name == std::string("browser_automation_studio_result"))
    {
        if (arguments.size() == 1 && arguments[0]->IsString())
        {
            std::lock_guard<std::mutex> lock(mut);
            Result = arguments[0]->GetStringValue().ToString();
            Changed = true;
        }else if (arguments.size() == 1 && (arguments[0]->IsUndefined() || arguments[0]->IsNull()))
        {
            std::lock_guard<std::mutex> lock(mut);
            Result = "";
            Changed = true;
        } if (arguments.size() == 1 && (arguments[0]->IsInt()))
        {
            std::lock_guard<std::mutex> lock(mut);
            Result = std::to_string(arguments[0]->GetIntValue());
            Changed = true;
        }
    }else if(name == std::string("browser_automation_studio_frame_find_result"))
    {
        std::lock_guard<std::mutex> lock(mut_frame_find);

        _FrameFindResult.x = arguments[0]->GetIntValue();
        _FrameFindResult.y = arguments[1]->GetIntValue();

        _FrameFindResult.FrameData.frame_name = arguments[2]->GetStringValue().ToString();
        _FrameFindResult.FrameData.frame_url = arguments[3]->GetStringValue().ToString();
        _FrameFindResult.FrameData.frame_tag_html = arguments[4]->GetStringValue().ToString();
        _FrameFindResult.FrameData.frame_index = arguments[5]->GetIntValue();

        _FrameFindResult.FrameData.x_with_padding = arguments[6]->GetIntValue();
        _FrameFindResult.FrameData.y_with_padding = arguments[7]->GetIntValue();

        _FrameFindResult.FrameData.is_frame = true;

        _FrameFindResult.active = arguments[8]->GetBoolValue();

        ChangedFrameFind = true;
    }else if(name == std::string("browser_automation_studio_inspect_result"))
    {
        std::lock_guard<std::mutex> lock(mut_inspect);

        _InspectResult.x = arguments[0]->GetIntValue();
        _InspectResult.y = arguments[1]->GetIntValue();
        _InspectResult.width = arguments[2]->GetIntValue();
        _InspectResult.height = arguments[3]->GetIntValue();

        _InspectResult.label = arguments[4]->GetStringValue().ToString();
        _InspectResult.css = arguments[5]->GetStringValue().ToString();
        _InspectResult.css2 = arguments[6]->GetStringValue().ToString();
        _InspectResult.css3 = arguments[7]->GetStringValue().ToString();
        _InspectResult.match = arguments[8]->GetStringValue().ToString();
        _InspectResult.xpath = arguments[9]->GetStringValue().ToString();
        _InspectResult.mousex = arguments[10]->GetIntValue();
        _InspectResult.mousey = arguments[11]->GetIntValue();
        _InspectResult.active = arguments[12]->GetBoolValue();

        _InspectResult.FrameData.is_frame = arguments[13]->GetBoolValue();
        _InspectResult.FrameData.frame_name = arguments[14]->GetStringValue().ToString();
        _InspectResult.FrameData.frame_url = arguments[15]->GetStringValue().ToString();
        _InspectResult.FrameData.frame_tag_html = arguments[16]->GetStringValue().ToString();
        _InspectResult.FrameData.frame_index = arguments[17]->GetIntValue();

        _InspectResult.FrameData.x_with_padding = arguments[18]->GetIntValue();
        _InspectResult.FrameData.y_with_padding = arguments[19]->GetIntValue();

        ChangedInspect = true;
    }else if(name == std::string("browser_automation_studio_highlight_result"))
    {
        bool DoUpdate = false;
        std::string HighlightNow = arguments[0]->GetStringValue().ToString();

        {
            std::lock_guard<std::mutex> lock(mut_highlight_last);

            if(HighlightLast != HighlightNow)
            {
                HighlightLast = HighlightNow;
                DoUpdate = true;
            }
        }

        if(DoUpdate)
        {
            std::lock_guard<std::mutex> lock(mut_highlight);

            _HighlightResult.highlights.clear();

            std::vector<std::string> s = split(HighlightNow,';');

            HighlightResult::rect r;

            for(int i = 0;i<s.size();i++)
            {
                switch(i%4)
                {
                    case 0: r.x = std::stoi(s[i]);r.y = 0;r.height = -1;r.width = -1; break;
                    case 1: r.y = std::stoi(s[i]); break;
                    case 2: r.width = std::stoi(s[i]); break;
                    case 3: r.height = std::stoi(s[i]); _HighlightResult.highlights.push_back(r);  break;
                }
            }

            ChangedHighlight = true;
        }
    }/*else if(name == std::string("BrowserAutomationStudio_SaveLocalStorage"))
    {
        if (arguments.size() == 6 && arguments[0]->IsString()&& arguments[1]->IsString()&& arguments[2]->IsString()&& arguments[3]->IsString()&& arguments[4]->IsInt()&& arguments[5]->IsString())
        {
            std::lock_guard<std::mutex> lock(mut_local_storage);
            LocalStorageDataItem Item;
            Item.TypeString = arguments[0]->GetStringValue().ToString();
            Item.Key = arguments[1]->GetStringValue().ToString();
            Item.Value = arguments[2]->GetStringValue().ToString();
            Item.Domain = arguments[3]->GetStringValue().ToString();
            Item.FrameHash = arguments[4]->GetIntValue();
            Item.Time = arguments[5]->GetStringValue();

            NewLocalStorage.push_back(Item);


            ChangedLocalStorage = true;
        }
    }*/
    else if(name == std::string("BrowserAutomationStudio_DomainDataNeedClear"))
    {
        if (arguments.size() == 1 && arguments[0]->IsString())
        {
            bool Res = false;
            {
                LOCK_DOMAIN_CLEAR
                std::string Domain = arguments[0]->GetStringValue().ToString();
                if(Data->NeedClear)
                {
                    Res = std::find(Data->DomainClearData.begin(), Data->DomainClearData.end(), Domain) == Data->DomainClearData.end();
                }
                if(Res)
                {
                    Data->DomainClearData.push_back(Domain);
                }
            }
            retval = CefV8Value::CreateBool(Res);
        }
    }
    else if(name == std::string("BrowserAutomationStudio_SaveBlob"))
    {
        if (arguments.size() == 4 && arguments[0]->GetIntValue() && arguments[1]->IsString()&& arguments[2]->IsString()&& arguments[3]->IsString())
        {
            _PostManager->AddAttachment(arguments[0]->GetIntValue(), arguments[1]->GetStringValue().ToString(), arguments[2]->GetStringValue().ToString(), arguments[3]->GetStringValue().ToString());
        }

    }
    return true;
}

