#include "settings.h"
#include <iostream>
#include <fstream>
#include <string>
#include <split.h>
#include "readallfile.h"

settings::settings()
{
    use_flash = false;
    force_utf8 = true;
    skip_frames = 74;
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
            }
        }
    }
    fin.close();
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
