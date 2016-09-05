#include "commandparser.h"
#include "rapidxml.hpp"
#include "log.h"
#include "split.h"

CommandParser::CommandParser()
{

}

void CommandParser::Parse(const std::string& Xml)
{
    rapidxml::xml_document<> doc;
    AllXml += Xml;
    std::string FindTag("</Messages>");


    while(true)
    {
        std::size_t pos = AllXml.find(FindTag);

        if(pos == std::string::npos)
            break;

        std::string CurrentXml = AllXml.substr(0,pos + FindTag.length());
        worker_log(std::string("Found xml : ") + CurrentXml);
        AllXml.erase(0,pos + FindTag.length());

        std::vector<char> data(CurrentXml.begin(), CurrentXml.end());
        data.push_back(0);
        doc.parse<0>(data.data());

        rapidxml::xml_node<> *MessagesNode = doc.first_node("Messages");
        if(!MessagesNode)
        {
            worker_log("Not found Messages element");
            continue;
        }

        rapidxml::xml_node<> *CommandNode = 0;

        //SetInitialState
        CommandNode = MessagesNode->first_node("SetInitialState");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            std::size_t pos = value.find(",");
            if(pos != std::string::npos)
            {
                worker_log("SetInitialState");
                std::string lang = value.substr(0,pos);
                std::string number_string = value.substr(pos + 1,value.length() - pos - 1);
                for(auto f:EventSetInitialState)
                    f(lang,std::stoi(number_string));

            }
        }

        CommandNode = MessagesNode->first_node("Load");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            worker_log("Load");
            for(auto f:EventLoad)
                f(value);
        }

        CommandNode = MessagesNode->first_node("SetCode");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            worker_log("SetCode");
            for(auto f:EventSetCode)
                f(value);
        }

        CommandNode = MessagesNode->first_node("SetResources");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            worker_log(std::string("SetResources<<") + value);
            for(auto f:EventSetResources)
                f(value);
        }

        CommandNode = MessagesNode->first_node("Visible");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            worker_log("Visible");
            for(auto f:EventVisible)
                f(std::stoi(value));
        }

        CommandNode = MessagesNode->first_node("Reset");
        if(CommandNode)
        {
            worker_log("Reset");
            for(auto f:EventReset)
                f();
        }

        CommandNode = MessagesNode->first_node("IsChanged");
        if(CommandNode)
        {
            worker_log("IsChanged");
            for(auto f:EventIsChanged)
                f();
        }

        CommandNode = MessagesNode->first_node("SetUserAgent");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            worker_log("EventSetUserAgent");
            for(auto f:EventSetUserAgent)
                f(value);
        }

        CommandNode = MessagesNode->first_node("SetOpenFileName");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            worker_log("EventSetOpenFileName");
            for(auto f:EventSetOpenFileName)
                f(value);
        }

        CommandNode = MessagesNode->first_node("SetStartupScript");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            worker_log("EventSetStartupScript");
            for(auto f:EventSetStartupScript)
                f(value);
        }

        CommandNode = MessagesNode->first_node("SetPromptResult");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            worker_log("EventSetPromptResult");
            for(auto f:EventSetPromptResult)
                f(value);
        }

        CommandNode = MessagesNode->first_node("SetHttpAuthResult");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            std::vector<std::string> s = split(value,':');
            if(s.size() == 2)
            {
                std::string login = s[0];
                std::string password = s[1];
                worker_log("EventSetHttpAuthResult");
                for(auto f:EventSetHttpAuthResult)
                    f(login,password);
            }
        }

        CommandNode = MessagesNode->first_node("GetCookiesForUrl");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            worker_log("EventGetCookiesForUrl");
            for(auto f:EventGetCookiesForUrl)
                f(value);
        }

        CommandNode = MessagesNode->first_node("SaveCookies");
        if(CommandNode)
        {
            worker_log("EventSaveCookies");
            for(auto f:EventSaveCookies)
                f();
        }

        CommandNode = MessagesNode->first_node("RestoreCookies");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            worker_log("EventRestoreCookies");
            for(auto f:EventRestoreCookies)
                f(value);
        }

        CommandNode = MessagesNode->first_node("DebugVariablesResult");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            worker_log("DebugVariablesResult");
            for(auto f:EventDebugVariablesResult)
                f(value);
        }

        CommandNode = MessagesNode->first_node("ScriptFinished");
        if(CommandNode)
        {
            worker_log("ScriptFinished");
            for(auto f:EventScriptFinished)
                f();
        }

        CommandNode = MessagesNode->first_node("WaitCode");
        if(CommandNode)
        {
            worker_log("WaitCode");
            for(auto f:EventWaitCode)
                f();
        }

        CommandNode = MessagesNode->first_node("StartSection");
        if(CommandNode)
        {
            worker_log("StartSection");
            int value = std::stoi(CommandNode->value());
            for(auto f:EventStartSection)
                f(value);
        }


        CommandNode = MessagesNode->first_node("GetUrl");
        if(CommandNode)
        {
            worker_log("GetUrl");
            for(auto f:EventGetUrl)
                f();
        }

        CommandNode = MessagesNode->first_node("Resize");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            worker_log("Resize");
            std::size_t pos = value.find(",");
            if(pos != std::string::npos)
            {
                std::string width = value.substr(0,pos);
                std::string height = value.substr(pos + 1,value.length() - pos - 1);
                for(auto f:EventResize)
                    f(std::stoi(width),std::stoi(height));

            }
        }

        CommandNode = MessagesNode->first_node("SetWindow");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            worker_log("SetWindow");
            
            for(auto f:EventSetWindow)
                f(value);
        }

        CommandNode = MessagesNode->first_node("MouseClick");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            worker_log("MouseClick");
            std::size_t pos = value.find(",");
            if(pos != std::string::npos)
            {
                std::string x = value.substr(0,pos);
                std::string y = value.substr(pos + 1,value.length() - pos - 1);
                for(auto f:EventMouseClick)
                    f(std::stoi(x),std::stoi(y));

            }
        }


        CommandNode = MessagesNode->first_node("PopupClose");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            worker_log("PopupClose");
            for(auto f:EventPopupClose)
                f(std::stoi(value));
        }

        CommandNode = MessagesNode->first_node("PopupSelect");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            worker_log("PopupSelect");
            for(auto f:EventPopupSelect)
                f(std::stoi(value));
        }

        CommandNode = MessagesNode->first_node("MouseMove");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            worker_log("MouseMove");
            std::size_t pos = value.find(",");
            if(pos != std::string::npos)
            {
                std::string x = value.substr(0,pos);
                std::string y = value.substr(pos + 1,value.length() - pos - 1);
                for(auto f:EventMouseMove)
                    f(std::stoi(x),std::stoi(y));

            }
        }

        CommandNode = MessagesNode->first_node("Scroll");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            worker_log("Scroll");
            std::size_t pos = value.find(",");
            if(pos != std::string::npos)
            {
                std::string x = value.substr(0,pos);
                std::string y = value.substr(pos + 1,value.length() - pos - 1);
                for(auto f:EventScroll)
                    f(std::stoi(x),std::stoi(y));

            }
        }

        CommandNode = MessagesNode->first_node("Render");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            worker_log("Render");
            int x=-1,y=-1,width=-1,height=-1;

            std::size_t pos = value.find(",");
            if(pos != std::string::npos)
            {
                x = std::stoi(value.substr(0,pos));
                value = value.substr(pos + 1,value.length() - pos - 1);
            }

            pos = value.find(",");
            if(pos != std::string::npos)
            {
                y = std::stoi(value.substr(0,pos));
                value = value.substr(pos + 1,value.length() - pos - 1);
            }

            pos = value.find(",");
            if(pos != std::string::npos)
            {
                width = std::stoi(value.substr(0,pos));
                value = value.substr(pos + 1,value.length() - pos - 1);
            }

            height = std::stoi(value);

            for(auto f:EventRender)
                f(x,y,width,height);
        }

        CommandNode = MessagesNode->first_node("AddHeader");
        if(CommandNode)
        {
            worker_log("AddHeader");

            std::string key,value;
            for (rapidxml::xml_attribute<> *attr = CommandNode->first_attribute(); attr; attr = attr->next_attribute())
            {
                worker_log(attr->name());
                if(std::string(attr->name()) == std::string("name"))
                {
                    worker_log(attr->value());
                    key = attr->value();
                }else if(std::string(attr->name()) == std::string("value"))
                {
                    worker_log(attr->value());
                    value = attr->value();
                }
            }

            for(auto f:EventAddHeader)
                f(key,value);
        }


        CommandNode = MessagesNode->first_node("CleanHeader");
        if(CommandNode)
        {
            worker_log("CleanHeader");
            for(auto f:EventCleanHeader)
                f();
        }

        CommandNode = MessagesNode->first_node("AddCacheMaskAllow");
        if(CommandNode)
        {
            worker_log("AddCacheMaskAllow");
            std::string value = CommandNode->value();
            for(auto f:EventAddCacheMaskAllow)
                f(value);
        }



        CommandNode = MessagesNode->first_node("AddCacheMaskDeny");
        if(CommandNode)
        {
            worker_log("AddCacheMaskDeny");
            std::string value = CommandNode->value();
            for(auto f:EventAddCacheMaskDeny)
                f(value);
        }

        CommandNode = MessagesNode->first_node("AddRequestMaskAllow");
        if(CommandNode)
        {
            worker_log("AddRequestMaskAllow");
            std::string value = CommandNode->value();
            for(auto f:EventAddRequestMaskAllow)
                f(value);
        }

        CommandNode = MessagesNode->first_node("AddRequestMaskDeny");
        if(CommandNode)
        {
            worker_log("AddRequestMaskDeny");
            std::string value = CommandNode->value();
            for(auto f:EventAddRequestMaskDeny)
                f(value);
        }

        CommandNode = MessagesNode->first_node("ClearCacheMask");
        if(CommandNode)
        {
            worker_log("ClearCacheMask");
            for(auto f:EventClearCacheMask)
                f();
        }

        CommandNode = MessagesNode->first_node("ClearRequestMask");
        if(CommandNode)
        {
            worker_log("ClearRequestMask");
            for(auto f:EventClearRequestMask)
                f();
        }

        CommandNode = MessagesNode->first_node("ClearLoadedUrl");
        if(CommandNode)
        {
            worker_log("ClearLoadedUrl");
            for(auto f:EventClearLoadedUrl)
                f();
        }

        CommandNode = MessagesNode->first_node("ClearCachedData");
        if(CommandNode)
        {
            worker_log("ClearCachedData");
            for(auto f:EventClearCachedData)
                f();
        }

        CommandNode = MessagesNode->first_node("ClearAll");
        if(CommandNode)
        {
            worker_log("ClearAll");
            for(auto f:EventClearAll)
                f();
        }

        CommandNode = MessagesNode->first_node("ClearMasks");
        if(CommandNode)
        {
            worker_log("ClearMasks");
            for(auto f:EventClearMasks)
                f();
        }

        CommandNode = MessagesNode->first_node("ClearData");
        if(CommandNode)
        {
            worker_log("ClearData");
            for(auto f:EventClearData)
                f();
        }

        CommandNode = MessagesNode->first_node("FindCacheByMaskBase64");
        if(CommandNode)
        {
            worker_log("FindCacheByMaskBase64");
            std::string value = CommandNode->value();
            for(auto f:EventFindCacheByMaskBase64)
                f(value);
        }

        CommandNode = MessagesNode->first_node("FindStatusByMask");
        if(CommandNode)
        {
            worker_log("FindStatusByMask");
            std::string value = CommandNode->value();
            for(auto f:EventFindStatusByMask)
                f(value);
        }

        CommandNode = MessagesNode->first_node("FindCacheByMaskString");
        if(CommandNode)
        {
            worker_log("FindCacheByMaskString");
            std::string value = CommandNode->value();
            for(auto f:EventFindCacheByMaskString)
                f(value);
        }

        CommandNode = MessagesNode->first_node("IsUrlLoadedByMask");
        if(CommandNode)
        {
            worker_log("IsUrlLoadedByMask");
            std::string value = CommandNode->value();
            for(auto f:EventIsUrlLoadedByMask)
                f(value);
        }

        CommandNode = MessagesNode->first_node("GetLoadStats");
        if(CommandNode)
        {
            worker_log("GetLoadStats");
            for(auto f:EventGetLoadStats)
                f();
        }


        CommandNode = MessagesNode->first_node("Element");
        if(CommandNode)
        {
            worker_log("Element");
            ElementCommand send;
            CommandNode = CommandNode->first_node();
            send.CommandName = CommandNode->name();
            worker_log(std::string("command : ") + send.CommandName);
            for (rapidxml::xml_attribute<> *attr = CommandNode->first_attribute(); attr; attr = attr->next_attribute())
            {
                if(std::string(attr->name()) == std::string("ID"))
                {
                    send.CommandId = attr->value();
                    worker_log(std::string("id : ") + send.CommandId);
                }
            }
            rapidxml::xml_node<> *A = CommandNode->first_node("A");
            if(A)
            {
                send.CommandParam1 = A->value();
                worker_log(std::string("param1 : ") + send.CommandParam1);
            }

            rapidxml::xml_node<> *B = CommandNode->first_node("B");
            if(B)
            {
                send.CommandParam2 = B->value();
                worker_log(std::string("param2 : ") + send.CommandParam2);
            }

            rapidxml::xml_node<> *Path = CommandNode->first_node("Path");
            if(Path)
            {
                for (rapidxml::xml_node<> *path_part = Path->first_node(); path_part; path_part = path_part->next_sibling())
                {
                    std::pair<std::string,std::string> p;
                    p.first = path_part->name();
                    p.second = path_part->value();
                    worker_log(std::string("path1 : ") + p.first);
                    worker_log(std::string("path2 : ") + p.second);
                    if(p.first == "frame")
                    {
                        send.FrameId = p.second;
                    }else
                        send.Path.push_back(p);
                }
            }
            for(auto f:EventElementCommand)
                f(send);
        }



        CommandNode = MessagesNode->first_node("SetProxy");
        if(CommandNode)
        {
            worker_log("SetProxy");

            std::string server,name,password;
            int Port;
            bool IsHttp;
            for (rapidxml::xml_attribute<> *attr = CommandNode->first_attribute(); attr; attr = attr->next_attribute())
            {
                worker_log(attr->name());
                if(std::string(attr->name()) == std::string("server"))
                {
                    worker_log(attr->value());
                    server = attr->value();
                }else if(std::string(attr->name()) == std::string("Port"))
                {
                    worker_log(attr->value());
                    Port = std::stoi(attr->value());
                }else if(std::string(attr->name()) == std::string("IsHttp"))
                {
                    worker_log(attr->value());
                    IsHttp = std::stoi(attr->value());
                }else if(std::string(attr->name()) == std::string("name"))
                {
                    worker_log(attr->value());
                    name = attr->value();
                }else if(std::string(attr->name()) == std::string("password"))
                {
                    worker_log(attr->value());
                    password = attr->value();
                }
            }



            for(auto f:EventSetProxy)
                f(server,Port,IsHttp,name,password);
        }
    }

}
