#include "toolboxpreprocessor.h"
#include "replaceall.h"
#include "log.h"
#include "picojson.h"

void ScenarioPreprocess(const ModulesDataList & Modules, std::string& OriginalScript)
{
    std::string Localize;
    picojson::value::object LocalizeObject;
    for(ModulesData Module:Modules)
    {
        for(LocalizeData Localize:Module->Localization)
        {
            picojson::value::object LocalizeItemObject;
            for(std::map<std::string,std::string>::iterator it = Localize->Items.begin(); it != Localize->Items.end(); ++it)
            {
                LocalizeItemObject[it->first] = picojson::value(it->second);
            }
            LocalizeObject[Localize->Key] = picojson::value(LocalizeItemObject);
        }
    }
    Localize = "_L = $.extend(_L," +  picojson::value(LocalizeObject).serialize() + ");";
    WORKER_LOG("_MACRO_INSERT_LOCALIZE_");
    WORKER_LOG(Localize);
    ReplaceAllInPlace(OriginalScript,"_MACRO_INSERT_LOCALIZE_",Localize);

    std::string Actions;
    picojson::value::object ActionsObject;
    picojson::value::object GroupsObject;

    for(ModulesData Module:Modules)
    {
        if(!Module->Icon.empty())
        {
            picojson::value::object Object;
            Object["icon"] = picojson::value(std::string("../../modules/") + Module->Name + std::string("/") + Module->Icon);

            GroupsObject[Module->Name] = picojson::value(Object);
        }
        for(ActionData a:Module->Actions)
        {
            picojson::value::object Object;
            Object["name"] = picojson::value(a->Description);
            Object["description"] = picojson::value(a->Description);
            Object["template"] = picojson::value(a->Template);
            Object["group"] = picojson::value(Module->Name);

            ActionsObject[a->Name] = picojson::value(Object);
        }

    }
    Actions = "_A = $.extend(_A," +  picojson::value(ActionsObject).serialize() + ");";
    Actions += "_G = $.extend(_G," +  picojson::value(GroupsObject).serialize() + ");";

    WORKER_LOG("_MACRO_INSERT_ACTIONS_");
    WORKER_LOG(Actions);
    ReplaceAllInPlace(OriginalScript,"_MACRO_INSERT_ACTIONS_",Actions);
}


void ToolboxPreprocess(const ModulesDataList & Modules, std::string& OriginalScript)
{
    {
        std::string Actions;
        picojson::value::object ActionsObject;
        picojson::value::object GroupsObject;

        for(ModulesData Module:Modules)
        {
            if(!Module->Icon.empty())
            {
                picojson::value::object Object;
                Object["icon"] = picojson::value(std::string("../../modules/") + Module->Name + std::string("/") + Module->Icon);

                GroupsObject[Module->Name] = picojson::value(Object);
            }
            for(ActionData a:Module->Actions)
            {
                picojson::value::object Object;
                Object["name"] = picojson::value(a->Description);
                Object["description"] = picojson::value(a->Description);
                Object["template"] = picojson::value(a->Template);
                if(a->IsElement)
                {
                    Object["class"] = picojson::value("browser");
                }

                if(!a->SuggestionEn.empty() || a->SuggestionRu.empty())
                {
                    picojson::value::object Suggestion;
                    Suggestion["en"] = picojson::value(a->SuggestionEn);
                    Suggestion["ru"] = picojson::value(a->SuggestionRu);

                    Object["suggestion"] = picojson::value(Suggestion);
                }

                ActionsObject[a->Name] = picojson::value(Object);
            }

        }
        Actions = "_A = $.extend(_A," +  picojson::value(ActionsObject).serialize() + ");";
        Actions += "_G = $.extend(_G," +  picojson::value(GroupsObject).serialize() + ");";
        WORKER_LOG("_MACRO_INSERT_ACTIONS_");
        WORKER_LOG(Actions);
        ReplaceAllInPlace(OriginalScript,"_MACRO_INSERT_ACTIONS_",Actions);
    }

    std::string ActionList;
    for(ModulesData Module:Modules)
    {
        bool IsFirstAction = true;
        for(ActionData Action:Module->Actions)
        {
            if(!Action->IsElement)
            {
                //Add group if needed
                if(IsFirstAction)
                {
                    IsFirstAction = false;
                    picojson::value::object res;

                    res["description"] = picojson::value(Module->Description);
                    res["type"] = picojson::value("group");
                    res["show_only_with_database"] = picojson::value(Module->OnlyWithDatabase);
                    res["name"] = picojson::value(Module->Name);
                    if(!Module->Icon.empty())
                    {
                        res["icon"] = picojson::value(std::string("../../modules/") + Module->Name + std::string("/") + Module->Icon);
                    }
                    if(!Module->Info.empty())
                    {
                        res["info"] = picojson::value(Module->Info);
                    }


                    ActionList += ",";
                    ActionList += picojson::value(res).serialize();
                }

                //Add action to action tab
                {
                    picojson::value::object res;

                    res["name"] = picojson::value(Action->Description);
                    res["description"] = picojson::value(Action->Description);
                    res["ref"] = picojson::value(Action->Name);
                    res["show_only_with_database"] = picojson::value(Module->OnlyWithDatabase);


                    ActionList += ",";
                    ActionList += picojson::value(res).serialize();
                }

            }
        }
    }
    WORKER_LOG("_MACRO_INSERT_ACTION_LIST_");
    WORKER_LOG(ActionList);
    //std::string ActionList = ",{ description: \"Test\", type: \"group\" },{ name: \"Test\", description: \"Set proxy for http client\", ref: \"tst\" }";
    ReplaceAllInPlace(OriginalScript,"_MACRO_INSERT_ACTION_LIST_",ActionList);



    std::string RouterFunc;
    for(ModulesData Module:Modules)
    {
        for(ActionData Action:Module->Actions)
        {
                RouterFunc += "," +  Action->Name + ": function(){ _GobalModel.set({ state: \"" + Action->Name + "\" }); }";
        }
    }
    WORKER_LOG("_MACRO_INSERT_ROUTER_FUNC_");
    WORKER_LOG(RouterFunc);
    ReplaceAllInPlace(OriginalScript,"_MACRO_INSERT_ROUTER_FUNC_",RouterFunc);


    std::string RouterDef;
    for(ModulesData Module:Modules)
    {
        for(ActionData Action:Module->Actions)
        {
                RouterDef += ",\"!/" + Action->Name + "\": \"" + Action->Name + "\"";
        }
    }
    WORKER_LOG("_MACRO_INSERT_ROUTER_DEF_");
    WORKER_LOG(RouterDef);
    ReplaceAllInPlace(OriginalScript,"_MACRO_INSERT_ROUTER_DEF_",RouterDef);

    std::string Templates;
    for(ModulesData Module:Modules)
    {
        for(ActionData Action:Module->Actions)
        {
            Templates += ",\"" + Action->Name + "\": _.template($('#" + Action->Name + "').html())";
        }
    }
    WORKER_LOG("_MACRO_INSERT_TEMPLATES_");
    WORKER_LOG(Templates);
    ReplaceAllInPlace(OriginalScript,"_MACRO_INSERT_TEMPLATES_",Templates);


    std::string Select;
    for(ModulesData Module:Modules)
    {
        for(ActionData Action:Module->Actions)
        {
            Select += "else if(State == \"" + Action->Name + "\")"
            "{"
              + Action->SelectScript +
            "}";
        }
    }
    WORKER_LOG("_MACRO_INSERT_SELECT_");
    WORKER_LOG(Select);
    ReplaceAllInPlace(OriginalScript,"_MACRO_INSERT_SELECT_",Select);


    std::string Interface;
    for(ModulesData Module:Modules)
    {
        for(ActionData Action:Module->Actions)
        {
            Interface += "<script type=\"text/template\" id=\"" + Action->Name + "\">"
              + Action->InterfaceScript +
            "</script>";
        }
    }
    WORKER_LOG("_MACRO_INSERT_INTERFACE_");
    WORKER_LOG(Interface);
    ReplaceAllInPlace(OriginalScript,"_MACRO_INSERT_INTERFACE_",Interface);


    std::string Localize;
    picojson::value::object LocalizeObject;
    for(ModulesData Module:Modules)
    {
        for(LocalizeData Localize:Module->Localization)
        {
            picojson::value::object LocalizeItemObject;
            for(std::map<std::string,std::string>::iterator it = Localize->Items.begin(); it != Localize->Items.end(); ++it)
            {
                LocalizeItemObject[it->first] = picojson::value(it->second);
            }
            LocalizeObject[Localize->Key] = picojson::value(LocalizeItemObject);
        }
    }
    Localize = "_L = $.extend(_L," +  picojson::value(LocalizeObject).serialize() + ");";
    WORKER_LOG("_MACRO_INSERT_LOCALIZE_");
    WORKER_LOG(Localize);
    ReplaceAllInPlace(OriginalScript,"_MACRO_INSERT_LOCALIZE_",Localize);

    std::string CodeString;
    for(ModulesData Module:Modules)
    {
        for(ActionData Action:Module->Actions)
        {
            for(CodeData Code:Action->CodeScript)
            {
                CodeString += "<script type=\"text/template\" id=\"" + Code->Name + std::string("\">")
                  + Code->Code +
                "</script>";
            }
        }
    }
    WORKER_LOG("_MACRO_INSERT_CODE_");
    WORKER_LOG(CodeString);
    ReplaceAllInPlace(OriginalScript,"_MACRO_INSERT_CODE_",CodeString);


    std::string ElementFunction;
    for(ModulesData Module:Modules)
    {
        for(ActionData Action:Module->Actions)
        {
            if(Action->IsElement)
            {
                ElementFunction += "function BrowserAutomationStudio_" + Action->Name + "(selector, is_loop)"
                "{"
                  "BrowserAutomationStudio_ElementFunction(selector, \"" + Action->Name + "\", is_loop)"
                "}";

            }
        }
    }
    WORKER_LOG("_MACRO_INSERT_ELEMENT_FUNCTION_");
    WORKER_LOG(ElementFunction);
    ReplaceAllInPlace(OriginalScript,"_MACRO_INSERT_ELEMENT_FUNCTION_",ElementFunction);
}
