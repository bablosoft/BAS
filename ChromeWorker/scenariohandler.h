#ifndef SCENARIOHANDLER_H
#define SCENARIOHANDLER_H

#include "include/cef_client.h"


class ScenarioHandler : public CefClient
{
public:
    ScenarioHandler();
private:
    IMPLEMENT_REFCOUNTING(ScenarioHandler);
};

#endif // SCENARIOHANDLER_H
