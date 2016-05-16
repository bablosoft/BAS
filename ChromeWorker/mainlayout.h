#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

#include <windows.h>
#include <vector>

class MainLayout
{
    int DevToolsRectWidth;
    void MoveDevTools();
    void CalculateAllSize(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight, RECT& DevToolsRectangle, RECT& ToolboxRectangle, RECT& BrowserRectangle);
    bool DevToolsTab;
public:

    enum StateClass{Ready,Hold,Finished}State;

    bool IsRecord;

    //Minimize/Maximize
    bool IsMinimized;
    HBITMAP ButtonMinimize, ButtonMaximize;
    HWND HButtonMinimizeMaximize;
    LONG SavelStyle,SavelExStyle;


    //Buttons
    HWND HButtonUp,HButtonDown,HButtonLeft,HButtonRight;
    HWND HButtonDevTools,HButtonScenario;

    //Browsers
    HWND BrowserHandle;
    HWND ToolBoxHandle;
    HWND ScenarioHandle;
    HWND DevToolsHandle;

    //Mainwindow
    HWND MainWindowHandle;

    //States
    HWND HTextHold,HTextFinished;

    //Images
    HBITMAP ButtonDevToolsBitmap, ButtonDevToolsBitmapGray, ButtonScenarioBitmap, ButtonScenarioBitmapGray;


    int BrowserWidth, BrowserHeight, WindowWidth, WindowHeight;

    MainLayout();
    void MinimizeOrMaximize(HWND MainWindow, HWND ParentWindow);

    void Update(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight);
    void CustomDraw(HDC hdc,int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight);
    void UpdateTabs(bool DevToolsTab);
    bool IsDevToolsTab();
    void UpdateTabs();
    void UpdateState(StateClass State);
    std::pair<int,int> GetDefaultWindowSize();
    std::pair<int,int> GetDefaultBrowserSize();
    RECT GetDevToolsRectangle(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight);
    RECT GetToolboxRectangle(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight);
    RECT GetBrowserRectangle(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight);
    RECT GetBrowserOuterRectangle(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight);
    RECT GetStateIndicatorRectangle(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight);
    RECT GetLabelRectangle(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight);

    //Helpers
    HWND GetDevToolsHandle();


};

#endif // MAINLAYOUT_H

