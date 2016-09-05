#include "modulesdata.h"
#include "picojson.h"
#include "readallfile.h"
#include "log.h"



std::string GetAllBrowserDataCode(const ModulesDataList& Modules)
{
    std::string Result;
    for(ModulesData Module:Modules)
    {
        for(std::string Script:Module->BrowserScripts)
        {
            Result += Script;
            Result += "\n";
        }
    }
    return Result;
}


ModulesDataList LoadModulesData(const std::string& Locale)
{
    worker_log("Start Loading Modules");
    ModulesDataList Result;

    std::vector<std::string> DisabledModules;
    try
    {
        std::string Meta = ReadAllString("modules/meta.json");
        picojson::value MetaJson;
        picojson::parse(MetaJson, Meta);
        picojson::value::object MetaObject = MetaJson.get<picojson::value::object>();
        for (picojson::value::object::iterator it = MetaObject.begin(); it != MetaObject.end(); ++it)
        {
          if(!it->second.get<bool>())
          {
              std::string ModuleName = it->first;
              worker_log(std::string("Module ") + ModuleName + std::string(" is disabled"));
              DisabledModules.push_back(ModuleName);
          }
        }
    }catch(...)
    {

    }

    std::vector<FileEntry> Dirs = GetFilesInDirectory("modules");
    for(FileEntry Entry:Dirs)
    {
        if(Entry.IsDirectory)
        {
            try
            {
                worker_log(std::string("Loading Module From ") + Entry.Path);
                std::string Manifest = ReadAllString(Entry.Path + "/manifest.json");
                picojson::value ManifestJson;
                picojson::parse(ManifestJson, Manifest);
                picojson::value::object ManifestObject = ManifestJson.get<picojson::value::object>();

                worker_log(std::string("Found ") + std::to_string(ManifestObject.size()) + std::string(" keys"));

                if(ManifestObject.find("name") == ManifestObject.end())
                {
                    worker_log("Attribute 'name' is empty");
                    continue;
                }

                if(ManifestObject.find("description_small") == ManifestObject.end())
                {
                    worker_log("Attribute 'description_small' is empty");
                    continue;
                }

                if(ManifestObject.find("actions") == ManifestObject.end())
                {
                    worker_log("Attribute 'actions' is empty");
                    continue;
                }

                if(ManifestObject.find("browser") == ManifestObject.end())
                {
                    worker_log("Attribute 'browser' is empty");
                    continue;
                }


                {
                    ModulesData DataItem = std::make_shared<ModulesDataClass>();
                    DataItem->Name = ManifestObject["name"].get<std::string>();
                    worker_log(std::string("Name ") + DataItem->Name);

                    if(std::find(std::begin(DisabledModules), std::end(DisabledModules), DataItem->Name) != std::end(DisabledModules))
                    {
                        worker_log(std::string("Skip because module is disabled"));
                        continue;
                    }

                    picojson::value::object DescriptionObject = ManifestObject["description_small"].get<picojson::value::object>();
                    if((DescriptionObject).find(Locale) != DescriptionObject.end())
                    {
                        DataItem->Description = DescriptionObject[Locale].get<std::string>();
                    }else if((DescriptionObject).find("en") != DescriptionObject.end())
                    {
                        DataItem->Description = DescriptionObject["en"].get<std::string>();
                    }
                    worker_log(std::string("Description ") + DataItem->Description);

                    picojson::value::array BrowserArray = ManifestObject["browser"].get<picojson::value::array>();
                    for(picojson::value BrowserValue: BrowserArray)
                    {
                        std::string BrowserPath = BrowserValue.get<std::string>();
                        worker_log(std::string("Found browser path ") + BrowserPath);

                        std::string BrowserData = ReadAllString(Entry.Path + std::string("/") + BrowserPath);
                        if(!BrowserData.empty())
                        {
                            worker_log(std::string("Found browser script length ") + std::to_string(BrowserData.size()));

                            DataItem->BrowserScripts.push_back(BrowserData);
                        }
                    }

                    if(ManifestObject.find("localize") != ManifestObject.end())
                    {
                        worker_log("Found localize element");
                        picojson::value::object LocalizeObject = ManifestObject["localize"].get<picojson::value::object>();
                        for(picojson::value::object::iterator it = LocalizeObject.begin(); it != LocalizeObject.end(); ++it)
                        {
                            worker_log(std::string("Found localize key ") + it->first);
                            LocalizeData LocalizeKey = std::make_shared<LocalizeDataClass>();
                            LocalizeKey->Key = it->first;
                            picojson::value::object LocalizeValueObject = it->second.get<picojson::value::object>();

                            for(picojson::value::object::iterator it = LocalizeValueObject.begin(); it != LocalizeValueObject.end(); ++it)
                            {
                                worker_log(std::string("Add localize key item ") + it->first + std::string(" ") + it->second.get<std::string>());
                                LocalizeKey->Items.insert(std::pair<std::string,std::string>(it->first,it->second.get<std::string>()));
                            }

                            DataItem->Localization.push_back(LocalizeKey);
                        }
                    }


                    picojson::value::array ActionsArray = ManifestObject["actions"].get<picojson::value::array>();
                    for(picojson::value ActionValue: ActionsArray)
                    {
                        picojson::value::object ActionObject = ActionValue.get<picojson::value::object>();

                        if(ActionObject.find("name") == ActionObject.end())
                        {
                            worker_log("Found some action, but it has no name");
                            continue;
                        }


                        if(ActionObject.find("description") == ActionObject.end())
                        {
                            worker_log("Attribute 'description' is empty");
                            continue;
                        }

                        if(ActionObject.find("is_element") == ActionObject.end())
                        {
                            worker_log("Attribute 'is_element' is empty");
                            continue;
                        }

                        if(ActionObject.find("interface") == ActionObject.end())
                        {
                            worker_log("Attribute 'interface' is empty");
                            continue;
                        }

                        if(ActionObject.find("select") == ActionObject.end())
                        {
                            worker_log("Attribute 'select' is empty");
                            continue;
                        }

                        if(ActionObject.find("code") == ActionObject.end())
                        {
                            worker_log("Attribute 'code' is empty");
                            continue;
                        }

                        ActionData ActionItem = std::make_shared<ActionDataClass>();
                        ActionItem->Name = ActionObject["name"].get<std::string>();
                        ActionItem->Template = ActionObject["template"].get<std::string>();

                        worker_log(std::string("Found some action with name ") + ActionItem->Name);


                        picojson::value::object ActionDescriptionObject = ActionObject["description"].get<picojson::value::object>();
                        if((ActionDescriptionObject).find(Locale) != ActionDescriptionObject.end())
                        {
                            ActionItem->Description = ActionDescriptionObject[Locale].get<std::string>();
                        }else if((ActionDescriptionObject).find("en") != ActionDescriptionObject.end())
                        {
                            ActionItem->Description = ActionDescriptionObject["en"].get<std::string>();
                        }


                        worker_log(std::string("Action description ") + ActionItem->Description);


                        ActionItem->IsElement = ActionObject["is_element"].get<bool>();
                        worker_log(std::string("Action iselement ") + std::to_string(ActionItem->IsElement));

                        ActionItem->InterfaceScript = ReadAllString(Entry.Path + std::string("/") + ActionObject["interface"].get<std::string>());
                        worker_log(std::string("Action interface script length ") + std::to_string(ActionItem->InterfaceScript.length()));

                        ActionItem->SelectScript = ReadAllString(Entry.Path + std::string("/") + ActionObject["select"].get<std::string>());
                        worker_log(std::string("Action select script length ") + std::to_string(ActionItem->SelectScript.length()));

                        picojson::value::array CodeArray = ActionObject["code"].get<picojson::value::array>();
                        for(picojson::value CodeValue: CodeArray)
                        {
                            picojson::value::object CodeObject = CodeValue.get<picojson::value::object>();
                            if(CodeObject.find("file") == CodeObject.end())
                            {
                                worker_log("Attribute 'file' is empty");
                                continue;
                            }

                            if(CodeObject.find("name") == CodeObject.end())
                            {
                                worker_log("Attribute 'name' is empty");
                                continue;
                            }

                            worker_log(std::string("Found code object"));

                            CodeData CodeItem = std::make_shared<CodeDataClass>();


                            CodeItem->Code = ReadAllString(Entry.Path + std::string("/") + CodeObject["file"].get<std::string>());
                            worker_log(std::string("Code object file length ") + std::to_string(CodeItem->Code.length()));

                            CodeItem->Name = CodeObject["name"].get<std::string>();
                            worker_log(std::string("Code object name ") + CodeItem->Name);

                            ActionItem->CodeScript.push_back(CodeItem);

                        }

                        DataItem->Actions.push_back(ActionItem);
                    }

                    Result.push_back(DataItem);
                }
            }catch(...)
            {
                worker_log("Error loading module");
            }
        }
    }



    worker_log("End Loading Modules");

    return Result;
}

