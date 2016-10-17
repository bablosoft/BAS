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
    use_flash = false;
    force_utf8 = true;
    skip_frames = 1;
    toolbox_height = 250;
    scenario_width = 500;
    zoom = 100;
    maximized = false;
    restart = false;
    emulate_mouse = true;
    std::ifstream fin("settings_worker.ini");
    if(fin.is_open())
    {
        std::string line;
        while(std::getline(fin, line))
        {
            if(line.find("ForceUtf8=false") != std::string::npos)
            {
                force_utf8 = false;
            }
            if(line.find("EnableFlash=true") != std::string::npos)
            {
                use_flash = true;
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

bool settings::EmulateMouse()
{
    return emulate_mouse;
}

bool settings::UseFlash()
{
    return use_flash;
}

bool settings::ForceUtf8()
{
    return force_utf8;
}

int settings::SkipFrames()
{
    return skip_frames + 1;
}

int settings::ToolboxHeight()
{
    return toolbox_height;
}

int settings::ScenarioWidth()
{
    return scenario_width;
}

int settings::Zoom()
{
    return zoom;
}

bool settings::Maximized()
{
    return maximized;
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
            outfile<<"ForceUtf8="<<((force_utf8) ? "true" : "false")<<std::endl;
            outfile<<"SkipFrames="<<skip_frames<<std::endl;
            outfile<<"ToolboxHeight="<<toolbox_height<<std::endl;
            outfile<<"ScenarioWidth="<<scenario_width<<std::endl;
            outfile<<"Zoom="<<zoom<<std::endl;
            outfile<<"IsMaximized="<<((maximized) ? "true" : "false")<<std::endl;
            outfile<<"Restart="<<((restart) ? "true" : "false")<<std::endl;
            outfile<<"UseHumanLikeMouseMoves="<<((emulate_mouse) ? "true" : "false")<<std::endl;

        }
    }catch(...)
    {
        worker_log("Failed to save settings_worker");
    }
}

std::string settings::Serialize()
{
    picojson::value::object res;
    res["use_flash"] = picojson::value(use_flash);
    res["force_utf8"] = picojson::value(force_utf8);
    res["skip_frames"] = picojson::value((double)skip_frames);
    res["toolbox_height"] = picojson::value((double)toolbox_height);
    res["scenario_width"] = picojson::value((double)scenario_width);
    res["zoom"] = picojson::value((double)zoom);
    res["restart"] = picojson::value(restart);
    res["emulatemouse"] = picojson::value(emulate_mouse);
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
        force_utf8 = o["force_utf8"].get<bool>();
        skip_frames = o["skip_frames"].get<double>();
        toolbox_height = o["toolbox_height"].get<double>();
        scenario_width = o["scenario_width"].get<double>();
        zoom = o["zoom"].get<double>();
        restart = o["restart"].get<bool>();
        emulate_mouse = o["emulatemouse"].get<bool>();

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
