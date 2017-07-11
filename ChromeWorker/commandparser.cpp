#include "commandparser.h"
#include "rapidxml.hpp"
#include "picojson.h"
#include "log.h"
#include "split.h"
#include "replaceall.h"
#include "snappy.h"
#include "base64.h"


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

        AllXml.erase(0,pos + FindTag.length());

        ReplaceAllInPlace(CurrentXml,"</Messages>","");
        ReplaceAllInPlace(CurrentXml,"<Messages>","");

        std::string Uncompressed;
        CurrentXml = base64_decode(CurrentXml);
        snappy::Uncompress(CurrentXml.data(),CurrentXml.length(),&Uncompressed);
        CurrentXml = std::string("<Messages>") + Uncompressed + std::string("</Messages>");

        //WORKER_LOG(std::string("Found xml : ") + CurrentXml);

        std::vector<char> data(CurrentXml.begin(), CurrentXml.end());
        data.push_back(0);
        doc.parse<0>(data.data());

        rapidxml::xml_node<> *MessagesNode = doc.first_node("Messages");
        if(!MessagesNode)
        {
            WORKER_LOG("Not found Messages element");
            continue;
        }

        rapidxml::xml_node<> *CommandNode = 0;

        CommandNode = MessagesNode->first_node("SetNextAction");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG("SetNextAction");
            for(auto f:EventSetNextAction)
                f(value);
        }

        CommandNode = MessagesNode->first_node("Load");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG("Load");
            for(auto f:EventLoad)
                f(value);
        }

        CommandNode = MessagesNode->first_node("SetCode");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            std::string schema;
            for (rapidxml::xml_attribute<> *attr = CommandNode->first_attribute(); attr; attr = attr->next_attribute())
            {
                if(std::string(attr->name()) == std::string("Schema"))
                {
                    schema = attr->value();
                }
            }
            WORKER_LOG("SetCode");
            for(auto f:EventSetCode)
                f(value,schema);
        }

        CommandNode = MessagesNode->first_node("SetResources");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG(std::string("SetResources<<") + value);
            for(auto f:EventSetResources)
                f(value);
        }

        CommandNode = MessagesNode->first_node("Visible");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG("Visible");
            for(auto f:EventVisible)
                f(std::stoi(value));
        }

        CommandNode = MessagesNode->first_node("Reset");
        if(CommandNode)
        {
            WORKER_LOG("Reset");
            for(auto f:EventReset)
                f();
        }

        CommandNode = MessagesNode->first_node("IsChanged");
        if(CommandNode)
        {
            WORKER_LOG("IsChanged");
            for(auto f:EventIsChanged)
                f();
        }

        CommandNode = MessagesNode->first_node("SetUserAgent");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG("EventSetUserAgent");
            for(auto f:EventSetUserAgent)
                f(value);
        }

        CommandNode = MessagesNode->first_node("SetOpenFileName");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG("EventSetOpenFileName");
            for(auto f:EventSetOpenFileName)
                f(value);
        }

        CommandNode = MessagesNode->first_node("SetStartupScript");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG("EventSetStartupScript");
            std::string target,script_id;

            for (rapidxml::xml_attribute<> *attr = CommandNode->first_attribute(); attr; attr = attr->next_attribute())
            {
                if(std::string(attr->name()) == std::string("target"))
                {
                    target = attr->value();
                }

                if(std::string(attr->name()) == std::string("script_id"))
                {
                    script_id = attr->value();
                }
            }

            for(auto f:EventSetStartupScript)
            {
                f(value, target, script_id);
            }

        }

        CommandNode = MessagesNode->first_node("SendWorkerSettings");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG("EventSendWorkerSettings");
            bool EncodeUtf8 = true;
            bool RefreshConnections = false;
            int SkipFrames = 1;

            for (rapidxml::xml_attribute<> *attr = CommandNode->first_attribute(); attr; attr = attr->next_attribute())
            {
                if(std::string(attr->name()) == std::string("EncodeUtf8"))
                {
                    EncodeUtf8 = std::stoi(attr->value());
                }

                if(std::string(attr->name()) == std::string("RefreshConnections"))
                {
                    RefreshConnections = std::stoi(attr->value());
                }

                if(std::string(attr->name()) == std::string("SkipFrames"))
                {
                    SkipFrames = std::stoi(attr->value());
                }
            }

            for(auto f:EventSendWorkerSettings)
            {
                f(EncodeUtf8, RefreshConnections, SkipFrames);
            }

        }

        CommandNode = MessagesNode->first_node("SetPromptResult");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG("EventSetPromptResult");
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
                WORKER_LOG("EventSetHttpAuthResult");
                for(auto f:EventSetHttpAuthResult)
                    f(login,password);
            }
        }


        CommandNode = MessagesNode->first_node("GetCookiesForUrl");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG("EventGetCookiesForUrl");
            for(auto f:EventGetCookiesForUrl)
                f(value);
        }

        CommandNode = MessagesNode->first_node("SaveCookies");
        if(CommandNode)
        {
            WORKER_LOG("EventSaveCookies");
            for(auto f:EventSaveCookies)
                f();
        }

        CommandNode = MessagesNode->first_node("ClearImageData");
        if(CommandNode)
        {
            WORKER_LOG("EventClearImageData");
            for(auto f:EventClearImageData)
                f();
        }

        CommandNode = MessagesNode->first_node("SetImageData");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG("EventSetImageData");
            for(auto f:EventSetImageData)
                f(value);
        }

        CommandNode = MessagesNode->first_node("FindImage");
        if(CommandNode)
        {
            WORKER_LOG("EventFindImage");
            for(auto f:EventFindImage)
                f();
        }

        CommandNode = MessagesNode->first_node("RestoreCookies");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG("EventRestoreCookies");
            for(auto f:EventRestoreCookies)
                f(value);
        }

        CommandNode = MessagesNode->first_node("RestoreLocalStorage");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG("EventRestoreLocalStorage");
            for(auto f:EventRestoreLocalStorage)
                f(value);
        }

        CommandNode = MessagesNode->first_node("DebugVariablesResult");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG("DebugVariablesResult");
            for(auto f:EventDebugVariablesResult)
                f(value);
        }

        CommandNode = MessagesNode->first_node("ScriptFinished");
        if(CommandNode)
        {
            WORKER_LOG("ScriptFinished");
            for(auto f:EventScriptFinished)
                f();
        }

        CommandNode = MessagesNode->first_node("WaitCode");
        if(CommandNode)
        {
            WORKER_LOG("WaitCode");
            for(auto f:EventWaitCode)
                f();
        }

        CommandNode = MessagesNode->first_node("StartSection");
        if(CommandNode)
        {
            WORKER_LOG("StartSection");
            int value = std::stoi(CommandNode->value());
            for(auto f:EventStartSection)
                f(value);
        }

        CommandNode = MessagesNode->first_node("SetFontList");
        if(CommandNode)
        {
            WORKER_LOG("SetFontList");
            std::string value = CommandNode->value();
            for(auto f:EventSetFontList)
                f(value);
        }

        CommandNode = MessagesNode->first_node("GetUrl");
        if(CommandNode)
        {
            WORKER_LOG("GetUrl");
            for(auto f:EventGetUrl)
                f();
        }

        CommandNode = MessagesNode->first_node("Crush");
        if(CommandNode)
        {
            WORKER_LOG("EventCrush");
            for(auto f:EventCrush)
                f();
        }

        CommandNode = MessagesNode->first_node("Resize");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG("Resize");
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
            WORKER_LOG("SetWindow");
            
            for(auto f:EventSetWindow)
                f(value);
        }

        CommandNode = MessagesNode->first_node("HighlightAction");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG("EventHighlightAction");

            for(auto f:EventHighlightAction)
                f(value);
        }

        CommandNode = MessagesNode->first_node("MouseClick");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG("MouseClick");
            std::size_t pos = value.find(",");
            if(pos != std::string::npos)
            {
                std::string x = value.substr(0,pos);
                std::string y = value.substr(pos + 1,value.length() - pos - 1);
                for(auto f:EventMouseClick)
                    f(std::stoi(x),std::stoi(y));

            }
        }


        CommandNode = MessagesNode->first_node("RestoreOriginalStage");
        if(CommandNode)
        {
            WORKER_LOG("RestoreOriginalStage");
            for(auto f:EventRestoreOriginalStage)
                f();
        }



        CommandNode = MessagesNode->first_node("Timezone");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG("Timezone");
            for(auto f:EventTimezone)
                f(std::stoi(value));
        }

        CommandNode = MessagesNode->first_node("Geolocation");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG("Geolocation");
            std::size_t pos = value.find(";");
            if(pos != std::string::npos)
            {
                std::string x = value.substr(0,pos);
                std::string y = value.substr(pos + 1,value.length() - pos - 1);
                for(auto f:EventGeolocation)
                    f(std::stof(x),std::stof(y));

            }
        }

        CommandNode = MessagesNode->first_node("MouseClickUp");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG("MouseClickUp");
            std::size_t pos = value.find(",");
            if(pos != std::string::npos)
            {
                std::string x = value.substr(0,pos);
                std::string y = value.substr(pos + 1,value.length() - pos - 1);
                for(auto f:EventMouseClickUp)
                    f(std::stoi(x),std::stoi(y));

            }
        }

        CommandNode = MessagesNode->first_node("MouseClickDown");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG("MouseClickDown");
            std::size_t pos = value.find(",");
            if(pos != std::string::npos)
            {
                std::string x = value.substr(0,pos);
                std::string y = value.substr(pos + 1,value.length() - pos - 1);
                for(auto f:EventMouseClickDown)
                    f(std::stoi(x),std::stoi(y));

            }
        }


        CommandNode = MessagesNode->first_node("PopupClose");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG("PopupClose");
            for(auto f:EventPopupClose)
                f(std::stoi(value));
        }

        CommandNode = MessagesNode->first_node("PopupSelect");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG("PopupSelect");
            for(auto f:EventPopupSelect)
                f(std::stoi(value));
        }

        CommandNode = MessagesNode->first_node("MouseMove");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG("MouseMove");
            std::size_t pos = value.find(",");
            if(pos != std::string::npos)
            {
                std::string x = value.substr(0,pos);
                std::string y = value.substr(pos + 1,value.length() - pos - 1);
                float speed = -1.0;
                float gravity = -1.0;
                float deviation = -1.0;
                for (rapidxml::xml_attribute<> *attr = CommandNode->first_attribute(); attr; attr = attr->next_attribute())
                {
                    if(std::string(attr->name()) == std::string("params"))
                    {
                        picojson::value val;
                        picojson::parse(val,attr->value());
                        picojson::object obj = val.get<picojson::object>();
                        if(obj.count("speed")>0)
                        {
                            speed = obj["speed"].get<double>();
                        }
                        if(obj.count("gravity")>0)
                        {
                            gravity = obj["gravity"].get<double>();
                        }
                        if(obj.count("deviation")>0)
                        {
                            deviation = obj["deviation"].get<double>();
                        }

                    }
                }

                for(auto f:EventMouseMove)
                    f(std::stoi(x),std::stoi(y),speed,gravity,deviation);

            }
        }

        CommandNode = MessagesNode->first_node("Scroll");
        if(CommandNode)
        {
            std::string value = CommandNode->value();
            WORKER_LOG("Scroll");
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
            WORKER_LOG("Render");
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
            WORKER_LOG("AddHeader");

            std::string key,value;
            std::string target;
            for (rapidxml::xml_attribute<> *attr = CommandNode->first_attribute(); attr; attr = attr->next_attribute())
            {
                WORKER_LOG(attr->name());
                if(std::string(attr->name()) == std::string("name"))
                {
                    WORKER_LOG(attr->value());
                    key = attr->value();
                }else if(std::string(attr->name()) == std::string("value"))
                {
                    WORKER_LOG(attr->value());
                    value = attr->value();
                }else if(std::string(attr->name()) == std::string("target"))
                {
                    target = attr->value();
                }
            }

            for(auto f:EventAddHeader)
                f(key,value,target);
        }

        CommandNode = MessagesNode->first_node("SetHeaderList");
        if(CommandNode)
        {
            WORKER_LOG("SetHeaderList");

            std::string json;
            for (rapidxml::xml_attribute<> *attr = CommandNode->first_attribute(); attr; attr = attr->next_attribute())
            {
                WORKER_LOG(attr->name());
                if(std::string(attr->name()) == std::string("json"))
                {
                    WORKER_LOG(attr->value());
                    json = attr->value();
                }
            }

            for(auto f:EventSetHeaderList)
                f(json);
        }


        CommandNode = MessagesNode->first_node("CleanHeader");
        if(CommandNode)
        {
            WORKER_LOG("CleanHeader");
            for(auto f:EventCleanHeader)
                f();
        }

        CommandNode = MessagesNode->first_node("AddCacheMaskAllow");
        if(CommandNode)
        {
            WORKER_LOG("AddCacheMaskAllow");
            std::string value = CommandNode->value();
            for(auto f:EventAddCacheMaskAllow)
                f(value);
        }



        CommandNode = MessagesNode->first_node("AddCacheMaskDeny");
        if(CommandNode)
        {
            WORKER_LOG("AddCacheMaskDeny");
            std::string value = CommandNode->value();
            for(auto f:EventAddCacheMaskDeny)
                f(value);
        }

        CommandNode = MessagesNode->first_node("AddRequestMaskAllow");
        if(CommandNode)
        {
            WORKER_LOG("AddRequestMaskAllow");
            std::string value = CommandNode->value();
            for(auto f:EventAddRequestMaskAllow)
                f(value);
        }

        CommandNode = MessagesNode->first_node("AddRequestMaskDeny");
        if(CommandNode)
        {
            WORKER_LOG("AddRequestMaskDeny");
            std::string value = CommandNode->value();
            for(auto f:EventAddRequestMaskDeny)
                f(value);
        }

        CommandNode = MessagesNode->first_node("ClearCacheMask");
        if(CommandNode)
        {
            WORKER_LOG("ClearCacheMask");
            for(auto f:EventClearCacheMask)
                f();
        }

        CommandNode = MessagesNode->first_node("ClearRequestMask");
        if(CommandNode)
        {
            WORKER_LOG("ClearRequestMask");
            for(auto f:EventClearRequestMask)
                f();
        }

        CommandNode = MessagesNode->first_node("RestrictPopups");
        if(CommandNode)
        {
            WORKER_LOG("RestrictPopups");
            for(auto f:EventRestrictPopups)
                f();
        }

        CommandNode = MessagesNode->first_node("AllowPopups");
        if(CommandNode)
        {
            WORKER_LOG("AllowPopups");
            for(auto f:EventAllowPopups)
                f();
        }

        CommandNode = MessagesNode->first_node("RestrictDownloads");
        if(CommandNode)
        {
            WORKER_LOG("RestrictDownloads");
            for(auto f:EventRestrictDownloads)
                f();
        }

        CommandNode = MessagesNode->first_node("AllowDownloads");
        if(CommandNode)
        {
            WORKER_LOG("AllowDownloads");
            for(auto f:EventAllowDownloads)
                f();
        }

        CommandNode = MessagesNode->first_node("ClearLoadedUrl");
        if(CommandNode)
        {
            WORKER_LOG("ClearLoadedUrl");
            for(auto f:EventClearLoadedUrl)
                f();
        }

        CommandNode = MessagesNode->first_node("ClearCachedData");
        if(CommandNode)
        {
            WORKER_LOG("ClearCachedData");
            for(auto f:EventClearCachedData)
                f();
        }

        CommandNode = MessagesNode->first_node("ClearAll");
        if(CommandNode)
        {
            WORKER_LOG("ClearAll");
            for(auto f:EventClearAll)
                f();
        }

        CommandNode = MessagesNode->first_node("ClearMasks");
        if(CommandNode)
        {
            WORKER_LOG("ClearMasks");
            for(auto f:EventClearMasks)
                f();
        }

        CommandNode = MessagesNode->first_node("ClearData");
        if(CommandNode)
        {
            WORKER_LOG("ClearData");
            for(auto f:EventClearData)
                f();
        }

        CommandNode = MessagesNode->first_node("FindCacheByMaskBase64");
        if(CommandNode)
        {
            WORKER_LOG("FindCacheByMaskBase64");
            std::string value = CommandNode->value();
            for(auto f:EventFindCacheByMaskBase64)
                f(value);
        }

        CommandNode = MessagesNode->first_node("FindStatusByMask");
        if(CommandNode)
        {
            WORKER_LOG("FindStatusByMask");
            std::string value = CommandNode->value();
            for(auto f:EventFindStatusByMask)
                f(value);
        }

        CommandNode = MessagesNode->first_node("FindCacheByMaskString");
        if(CommandNode)
        {
            WORKER_LOG("FindCacheByMaskString");
            std::string value = CommandNode->value();
            for(auto f:EventFindCacheByMaskString)
                f(value);
        }

        CommandNode = MessagesNode->first_node("IsUrlLoadedByMask");
        if(CommandNode)
        {
            WORKER_LOG("IsUrlLoadedByMask");
            std::string value = CommandNode->value();
            for(auto f:EventIsUrlLoadedByMask)
                f(value);
        }

        CommandNode = MessagesNode->first_node("GetLoadStats");
        if(CommandNode)
        {
            WORKER_LOG("GetLoadStats");
            for(auto f:EventGetLoadStats)
                f();
        }


        CommandNode = MessagesNode->first_node("Element");
        if(CommandNode)
        {
            WORKER_LOG("Element");
            ElementCommand send;
            CommandNode = CommandNode->first_node();
            send.CommandName = CommandNode->name();
            WORKER_LOG(std::string("command : ") + send.CommandName);
            for (rapidxml::xml_attribute<> *attr = CommandNode->first_attribute(); attr; attr = attr->next_attribute())
            {
                if(std::string(attr->name()) == std::string("ID"))
                {
                    send.CommandId = attr->value();
                    WORKER_LOG(std::string("id : ") + send.CommandId);
                }
                if(std::string(attr->name()) == std::string("NoWait"))
                {
                    send.IsNoWait = std::stoi(attr->value());
                    WORKER_LOG(std::string("nowait : ") + std::to_string(send.IsNoWait));
                }
            }
            rapidxml::xml_node<> *A = CommandNode->first_node("A");
            if(A)
            {
                send.CommandParam1 = A->first_attribute("value")->value();
                WORKER_LOG(std::string("param1 : ") + send.CommandParam1);
            }

            rapidxml::xml_node<> *B = CommandNode->first_node("B");
            if(B)
            {
                send.CommandParam2 = B->first_attribute("value")->value();
                WORKER_LOG(std::string("param2 : ") + send.CommandParam2);
            }

            rapidxml::xml_node<> *Path = CommandNode->first_node("Path");
            if(Path)
            {
                for (rapidxml::xml_node<> *path_part = Path->first_node(); path_part; path_part = path_part->next_sibling())
                {
                    std::pair<std::string,std::string> p;
                    p.first = path_part->name();
                    p.second = path_part->value();
                    WORKER_LOG(std::string("path1 : ") + p.first);
                    WORKER_LOG(std::string("path2 : ") + p.second);
                    if(p.first == "frame")
                    {
                        send.FrameUrl = p.second;
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
            WORKER_LOG("SetProxy");

            std::string server,name,password;
            int Port;
            bool IsHttp;
            std::string target;
            for (rapidxml::xml_attribute<> *attr = CommandNode->first_attribute(); attr; attr = attr->next_attribute())
            {
                WORKER_LOG(attr->name());
                if(std::string(attr->name()) == std::string("server"))
                {
                    WORKER_LOG(attr->value());
                    server = attr->value();
                }else if(std::string(attr->name()) == std::string("Port"))
                {
                    WORKER_LOG(attr->value());
                    Port = std::stoi(attr->value());
                }else if(std::string(attr->name()) == std::string("IsHttp"))
                {
                    WORKER_LOG(attr->value());
                    IsHttp = std::stoi(attr->value());
                }else if(std::string(attr->name()) == std::string("name"))
                {
                    WORKER_LOG(attr->value());
                    name = attr->value();
                }else if(std::string(attr->name()) == std::string("password"))
                {
                    WORKER_LOG(attr->value());
                    password = attr->value();
                }else if(std::string(attr->name()) == std::string("target"))
                {
                    target = attr->value();
                }
            }



            for(auto f:EventSetProxy)
                f(server,Port,IsHttp,name,password,target);
        }
    }

}
