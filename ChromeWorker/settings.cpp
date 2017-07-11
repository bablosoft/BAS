#include "settings.h"
#include <iostream>
#include <fstream>
#include "picojson.h"
#include <string>
#include <split.h>
#include "readallfile.h"
#include "log.h"

settings::settings()
{
    Init();
}

void settings::Init()
{
    use_flash = false;
    force_utf8 = true;
    skip_frames = 1;
    is_safe = true;
    toolbox_height = 300;
    scenario_width = 500;
    zoom = 100;
    maximized = false;
    restart = false;
    emulate_mouse = true;
    proxies_reconnect = false;
    debug_toolbox = false;
    debug_scenario = false;
    std::ifstream fin("settings_worker.ini");
    if(fin.is_open())
    {
        std::string line;
        while(std::getline(fin, line))
        {
            if(line.find("DebugToolbox=true") != std::string::npos)
            {
                debug_toolbox = true;
            }
            if(line.find("DebugScenario=true") != std::string::npos)
            {
                debug_scenario = true;
            }
            if(line.find("ForceUtf8=false") != std::string::npos)
            {
                force_utf8 = false;
            }
            if(line.find("IsSafe=false") != std::string::npos)
            {
                is_safe = false;
            }
            if(line.find("EnableFlash=true") != std::string::npos)
            {
                use_flash = true;
            }
            if(line.find("ProxiesReconnect=true") != std::string::npos)
            {
                proxies_reconnect = true;
            }
            if(line.find("SkipFrames=") != std::string::npos)
            {
                std::vector<std::string> s = split(line,'=');
                skip_frames = std::stoi(s[1]);
                if(skip_frames < 1)
                    skip_frames = 1;
            }
            if(line.find("ToolboxHeight=") != std::string::npos)
            {
                std::vector<std::string> s = split(line,'=');
                toolbox_height = std::stoi(s[1]);
                if(toolbox_height < 100)
                    toolbox_height = 100;
            }
            if(line.find("ScenarioWidth=") != std::string::npos)
            {
                std::vector<std::string> s = split(line,'=');
                scenario_width = std::stoi(s[1]);
                if(scenario_width < 100)
                    scenario_width = 100;
            }
            if(line.find("Zoom=") != std::string::npos)
            {
                std::vector<std::string> s = split(line,'=');
                zoom = std::stoi(s[1]);
            }
            if(line.find("IsMaximized=true") != std::string::npos)
            {
                maximized = true;
            }
            if(line.find("Restart=true") != std::string::npos)
            {
                restart = true;
            }
            if(line.find("UseHumanLikeMouseMoves=false") != std::string::npos)
            {
                emulate_mouse = false;
            }
        }
    }
    fin.close();
}

void settings::ParseCommandLine(std::vector<std::wstring>& Params)
{
    std::vector<std::wstring> res;


    bool NextIsSafe = false;
    bool NextUseFlash = false;
    bool NextSkipFrames = false;
    bool NextRefreshConnections = false;
    bool NextEncodeUtf8 = false;
    for(std::wstring& param: Params)
    {
        if(NextIsSafe)
        {
            is_safe = param == L"1";
            NextIsSafe = false;
            NextUseFlash = false;
            NextSkipFrames = false;
            NextRefreshConnections = false;
            NextEncodeUtf8 = false;
            continue;
        }else if(NextUseFlash)
        {
            use_flash = param == L"1";
            NextIsSafe = false;
            NextUseFlash = false;
            NextSkipFrames = false;
            NextRefreshConnections = false;
            NextEncodeUtf8 = false;
            continue;
        }else if(NextSkipFrames)
        {
            skip_frames = std::stoi(param);
            NextIsSafe = false;
            NextUseFlash = false;
            NextSkipFrames = false;
            NextRefreshConnections = false;
            NextEncodeUtf8 = false;
            continue;
        }else if(NextRefreshConnections)
        {
            proxies_reconnect = param == L"1";
            NextIsSafe = false;
            NextUseFlash = false;
            NextSkipFrames = false;
            NextRefreshConnections = false;
            NextEncodeUtf8 = false;
            continue;
        }else if(NextEncodeUtf8)
        {
            force_utf8 = param == L"1";
            NextIsSafe = false;
            NextUseFlash = false;
            NextSkipFrames = false;
            NextRefreshConnections = false;
            NextEncodeUtf8 = false;
            continue;
        }

        if(param == L"--IsSafe")
        {
            NextIsSafe = true;
            continue;
        }else if(param == L"--UseFlash")
        {
            NextUseFlash = true;
            continue;
        }else if(param == L"--SkipFrames")
        {
            NextSkipFrames = true;
            continue;
        }else if(param == L"--RefreshConnections")
        {
            NextRefreshConnections = true;
            continue;
        }else if(param == L"--EncodeUtf8")
        {
            NextEncodeUtf8 = true;
            continue;
        }

        res.push_back(param);
    }

    Params = res;
}

bool settings::EmulateMouse()
{
    return emulate_mouse;
}

bool settings::UseFlash()
{
    return use_flash;
}

bool settings::IsSafe()
{
    return is_safe;
}

bool settings::ProxiesReconnect()
{
    return proxies_reconnect;
}

bool settings::ForceUtf8()
{
    return force_utf8;
}

int settings::SkipFrames()
{
    return skip_frames + 1;
}

void settings::SetProxiesReconnect(bool proxies_reconnect)
{
    this->proxies_reconnect = proxies_reconnect;
}
void settings::SetForceUtf8(bool force_utf8)
{
    this->force_utf8 = force_utf8;
}
void settings::SetSkipFrames(int skip_frames)
{
    if(skip_frames < 1)
        skip_frames = 1;
    this->skip_frames = skip_frames;
}

int settings::ToolboxHeight()
{
    return toolbox_height;
}

int settings::ScenarioWidth()
{
    return scenario_width;
}

void settings::SetToolboxHeight(int height)
{
    this->toolbox_height = height;
}

void settings::SetScenarioWidth(int width)
{
    this->scenario_width = width;
}

int settings::Zoom()
{
    return zoom;
}

bool settings::Maximized()
{
    return maximized;
}

bool settings::DebugToolbox()
{
    return debug_toolbox;
}

bool settings::DebugScenario()
{
    return debug_scenario;
}

void settings::SetMaximized(bool Maximized)
{
    maximized = Maximized;
    SaveToFile();
}

void settings::SaveToFile()
{
    try
    {
        std::ofstream outfile("settings_worker.ini");
        if(outfile.is_open())
        {
            outfile<<"EnableFlash="<<((use_flash) ? "true" : "false")<<std::endl;
            outfile<<"ProxiesReconnect="<<((proxies_reconnect) ? "true" : "false")<<std::endl;
            outfile<<"ForceUtf8="<<((force_utf8) ? "true" : "false")<<std::endl;
            outfile<<"IsSafe="<<((is_safe) ? "true" : "false")<<std::endl;
            outfile<<"SkipFrames="<<skip_frames<<std::endl;
            outfile<<"ToolboxHeight="<<toolbox_height<<std::endl;
            outfile<<"ScenarioWidth="<<scenario_width<<std::endl;
            outfile<<"Zoom="<<zoom<<std::endl;
            outfile<<"IsMaximized="<<((maximized) ? "true" : "false")<<std::endl;
            outfile<<"Restart="<<((restart) ? "true" : "false")<<std::endl;
            outfile<<"UseHumanLikeMouseMoves="<<((emulate_mouse) ? "true" : "false")<<std::endl;
            outfile<<"DebugToolbox="<<((debug_toolbox) ? "true" : "false")<<std::endl;
            outfile<<"DebugScenario="<<((debug_scenario) ? "true" : "false")<<std::endl;

        }
    }catch(...)
    {
        WORKER_LOG("Failed to save settings_worker");
    }
}

std::string settings::Serialize()
{
    picojson::value::object res;
    res["use_flash"] = picojson::value(use_flash);
    res["proxies_reconnect"] = picojson::value(proxies_reconnect);
    res["force_utf8"] = picojson::value(force_utf8);
    res["is_safe"] = picojson::value(is_safe);
    res["skip_frames"] = picojson::value((double)skip_frames);
    res["toolbox_height"] = picojson::value((double)toolbox_height);
    res["scenario_width"] = picojson::value((double)scenario_width);
    res["zoom"] = picojson::value((double)zoom);
    res["restart"] = picojson::value(restart);
    res["emulatemouse"] = picojson::value(emulate_mouse);
    /*res["debug_toolbox"] = picojson::value(debug_toolbox);
    res["debug_scenario"] = picojson::value(debug_scenario);*/
    return picojson::value(res).serialize();
}

void settings::Deserialize(const std::string & Data)
{
    picojson::value val;
    try
    {
        picojson::parse(val, Data);
        picojson::value::object o = val.get<picojson::value::object>();

        use_flash = o["use_flash"].get<bool>();
        proxies_reconnect = o["proxies_reconnect"].get<bool>();
        force_utf8 = o["force_utf8"].get<bool>();
        is_safe = o["is_safe"].get<bool>();
        skip_frames = o["skip_frames"].get<double>();
        toolbox_height = o["toolbox_height"].get<double>();
        scenario_width = o["scenario_width"].get<double>();
        zoom = o["zoom"].get<double>();
        restart = o["restart"].get<bool>();
        emulate_mouse = o["emulatemouse"].get<bool>();
        /*debug_scenario = o["debug_scenario"].get<bool>();
        debug_toolbox = o["debug_toolbox"].get<bool>();*/

        if(toolbox_height < 100)
            toolbox_height = 100;

        if(scenario_width < 100)
            scenario_width = 100;

        if(skip_frames < 1)
            skip_frames = 1;

        SaveToFile();
    }catch(...)
    {

    }
}
