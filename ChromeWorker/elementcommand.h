#ifndef ELEMENTCOMMAND
#define ELEMENTCOMMAND
#include <vector>
#include <string>
struct ElementCommand
{
    std::string CommandName;
    std::string CommandId;
    std::string CommandParam1;
    std::string CommandParam2;
    bool IsNoWait = false;
    int StageId;
    std::string FrameUrl;


    std::vector<std::pair<std::string,std::string> > Path;

    std::string SerializePath();
};
#endif // ELEMENTCOMMAND

