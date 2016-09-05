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
    worker_log("_MACRO_INSERT_LOCALIZE_");
    worker_log(Localize);
    ReplaceAllInPlace(OriginalScript,"_MACRO_INSERT_LOCALIZE_",Localize);

    std::string Actions;
    picojson::value::object ActionsObject;
    for(ModulesData Module:Modules)
    {

        for(ActionData a:Module->Actions)
        {
            picojson::value::object Object;
            Object["name"] = picojson::value(a->Description);
            Object["description"] = picojson::value(a->Description);
            Object["template"] = picojson::value(a->Template);

            ActionsObject[a->Name] = picojson::value(Object);
        }

    }
    Actions = "_A = $.extend(_A," +  picojson::value(ActionsObject).serialize() + ");";
    worker_log("_MACRO_INSERT_ACTIONS_");
    worker_log(Actions);
    ReplaceAllInPlace(OriginalScript,"_MACRO_INSERT_ACTIONS_",Actions);
}


void ToolboxPreprocess(const ModulesDataList & Modules, std::string& OriginalScript)
{
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


                    ActionList += ",";
                    ActionList += picojson::value(res).serialize();
                }

                //Add action to action tab
                {
                    picojson::value::object res;

                    res["name"] = picojson::value(Action->Description);
                    res["description"] = picojson::value(Action->Description);
                    res["ref"] = picojson::value(Action->Name);

                    ActionList += ",";
                    ActionList += picojson::value(res).serialize();
                }

            }
        }
    }
    worker_log("_MACRO_INSERT_ACTION_LIST_");
    worker_log(ActionList);
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
    worker_log("_MACRO_INSERT_ROUTER_FUNC_");
    worker_log(RouterFunc);
    ReplaceAllInPlace(OriginalScript,"_MACRO_INSERT_ROUTER_FUNC_",RouterFunc);


    std::string RouterDef;
    for(ModulesData Module:Modules)
    {
        for(ActionData Action:Module->Actions)
        {
                RouterDef += ",\"!/" + Action->Name + "\": \"" + Action->Name + "\"";
        }
    }
    worker_log("_MACRO_INSERT_ROUTER_DEF_");
    worker_log(RouterDef);
    ReplaceAllInPlace(OriginalScript,"_MACRO_INSERT_ROUTER_DEF_",RouterDef);

    std::string Templates;
    for(ModulesData Module:Modules)
    {
        for(ActionData Action:Module->Actions)
        {
            Templates += ",\"" + Action->Name + "\": _.template($('#" + Action->Name + "').html())";
        }
    }
    worker_log("_MACRO_INSERT_TEMPLATES_");
    worker_log(Templates);
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
    worker_log("_MACRO_INSERT_SELECT_");
    worker_log(Select);
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
    worker_log("_MACRO_INSERT_INTERFACE_");
    worker_log(Interface);
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
    worker_log("_MACRO_INSERT_LOCALIZE_");
    worker_log(Localize);
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
    worker_log("_MACRO_INSERT_CODE_");
    worker_log(CodeString);
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
    worker_log("_MACRO_INSERT_ELEMENT_FUNCTION_");
    worker_log(ElementFunction);
    ReplaceAllInPlace(OriginalScript,"_MACRO_INSERT_ELEMENT_FUNCTION_",ElementFunction);
}
