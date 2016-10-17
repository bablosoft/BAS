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
    /*
     * @type == 0 - up and down
     * @type == 1 - up
     * @type == 2 - down
     * */
    static void MouseClick(CefRefPtr<CefBrowser> Browser, int x, int y, const std::pair<int,int> scroll, int type = 0);

    static void MouseMove(CefRefPtr<CefBrowser> Browser,
                          bool & IsMouseMoveSimulation,
                          int MouseStartX, int MouseStartY,
                          int MouseEndX, int MouseEndY,
                          int& MouseCurrentX, int& MouseCurrentY,
                          float Speed,
                          int BrowserWidth, int BrowserHeight,
                          float Gravity, float Wind, float TargetArea,
                          bool IsInit, bool IsDouble
                          );
    static void MouseMoveLine(CefRefPtr<CefBrowser> Browser, bool & IsMouseMoveSimulation, int MouseStartX, int MouseStartY, int MouseEndX, int MouseEndY , int& MouseCurrentX, int& MouseCurrentY, float Speed, int BrowserWidth, int BrowserHeight);
    static bool IsPointOnScreen(int PointX, int PointY, int ScrollX, int ScrollY, int BrowserWidth, int BrowserHeight);
    static void Key(CefRefPtr<CefBrowser> Browser, std::string & text, KeyState& State, int mousex, int mousey);
};

#endif // BROWSEREVENTSEMULATOR_H
