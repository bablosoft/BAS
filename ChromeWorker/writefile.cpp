#include "writefile.h"
#include <fstream>

void WriteStringToFile(const std::string& filename,const std::string& data)
{
    try
    {
        std::ofstream outfile(filename);
        if(outfile.is_open())
        {
            outfile<<data;
        }
        outfile.close();
    }catch(...)
    {

    }
}
