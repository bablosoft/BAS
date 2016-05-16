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
    int StageId;
    std::string FrameId;
    std::vector<std::pair<std::string,std::string> > Path;
    std::string SerializePath();
};
#endif // ELEMENTCOMMAND

