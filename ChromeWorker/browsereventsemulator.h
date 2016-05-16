#ifndef BROWSEREVENTSEMULATOR_H
#define BROWSEREVENTSEMULATOR_H

#include "include/cef_app.h"

struct KeyState
{
    bool IsShift;
    bool IsAlt;
    bool IsCtrl;
    KeyState();
    void Clear();
    bool IsClear();
};
class BrowserEventsEmulator
{
public:
    BrowserEventsEmulator();
    static void SetFocus(CefRefPtr<CefBrowser> Browser);
    static void MouseClick(CefRefPtr<CefBrowser> Browser, int x, int y, const std::pair<int,int> scroll);

    static void MouseMove(CefRefPtr<CefBrowser> Browser, bool & IsMouseMoveSimulation,int MouseStartX, int MouseStartY, int MouseEndX, int MouseEndY , int& MouseCurrentX, int& MouseCurrentY, float Speed, int ScrollX, int ScrollY, int BrowserWidth, int BrowserHeight);
    static bool IsPointOnScreen(int PointX, int PointY, int ScrollX, int ScrollY, int BrowserWidth, int BrowserHeight);
    static void Key(CefRefPtr<CefBrowser> Browser, std::string & text, KeyState& State);
};

#endif // BROWSEREVENTSEMULATOR_H
