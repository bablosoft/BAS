#include "chromecommandlineparser.h"
#include "trim.h"
#include "split.h"
#include <fstream>

std::vector<std::pair<std::string,std::string> > ParseChromeCommandLine()
{
    std::vector<std::pair<std::string,std::string> > res;
    std::ifstream fin("chrome_command_line.txt");
    if(fin.is_open())
    {
        std::string line;
        while(std::getline(fin, line))
        {
            line = trim(line);
            if(!line.empty())
            {
               std::vector<std::string> s = split(line,'=');
               if(s.size() == 1)
               {
                   std::pair<std::string,std::string> p;
                   p.first = s[0];
                   res.push_back(p);
               }
               if(s.size() == 2)
               {
                   std::pair<std::string,std::string> p;
                   p.first = s[0];
                   p.second = s[1];
                   res.push_back(p);
               }
            }

        }
    }
    fin.close();
    return res;
}
