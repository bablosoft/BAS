#ifndef TOOLBOXHANDLER_H
#define TOOLBOXHANDLER_H

#include "include/cef_client.h"

class ToolboxHandler : public CefClient
{
public:
    ToolboxHandler();

private:
    IMPLEMENT_REFCOUNTING(ToolboxHandler);
};

#endif // TOOLBOXHANDLER_H
