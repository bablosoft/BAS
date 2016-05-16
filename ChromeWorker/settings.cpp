#include "settings.h"
#include <iostream>
#include <fstream>
#include <string>
#include <split.h>

settings::settings()
{
    use_flash = false;
    skip_frames = 74;
    std::ifstream fin("settings_worker.ini");
    if(fin.is_open())
    {
        std::string line;
        while(std::getline(fin, line))
        {
            if(line.find("EnableFlash=true") != std::string::npos)
            {
                use_flash = true;
                return;
            }
            if(line.find("SkipFrames=") != std::string::npos)
            {
                std::vector<std::string> s = split(line,'=');
                skip_frames = std::stoi(s[1]);
                return;
            }
        }
    }
    fin.close();
}

bool settings::UseFlash()
{
    return use_flash;
}

int settings::SkipFrames()
{
    return skip_frames + 1;
}
