#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

#include <windows.h>
#include <vector>

class MainLayout
{
    int DevToolsRectWidth;
    int ToolBoxRectHeight;
    void MoveDevTools();
    void CalculateAllSize(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight, RECT& DevToolsRectangle, RECT& ToolboxRectangle, RECT& BrowserRectangle);
    bool DevToolsTab;

    long long LastTimeChangedHoldPicture;
    int HoldAnimation;

public:

    enum StateClass{Ready,Hold,Finished}State;

    bool IsRecord;
    bool IsCentralShown;
    bool IsSettingsShown;

    //Minimize/Maximize
    bool IsMinimized;
    bool IsToolboxMaximized;
    HBITMAP ButtonMinimize, ButtonMaximize;
    HBITMAP BHold,BHold90;
    HWND HButtonMinimizeMaximize;
    LONG SavelStyle,SavelExStyle;


    //Buttons
    HWND HButtonUp,HButtonDown,HButtonLeft,HButtonRight;
    HWND HButtonDevTools,HButtonScenario;
    HWND HButtonSettings;


    //Browsers
    HWND BrowserHandle;
    HWND ToolBoxHandle;
    HWND ScenarioHandle;
    HWND CentralHandle;
    HWND DevToolsHandle;

    //Mainwindow
    HWND MainWindowHandle;

    //States
    HWND HTextHold,HTextFinished;

    //Images
    HBITMAP ButtonDevToolsBitmap, ButtonDevToolsBitmapGray, ButtonScenarioBitmap, ButtonScenarioBitmapGray;


    int BrowserWidth, BrowserHeight, WindowWidth, WindowHeight;

    MainLayout(int ToolboxHeight, int ScenarioWidth);
    void MinimizeOrMaximize(HWND MainWindow, HWND ParentWindow);

    void Update(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight);
    void CustomDraw(HDC hdc,int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight);
    void UpdateTabs(bool DevToolsTab);
    bool IsDevToolsTab();
    void UpdateTabs();
    void UpdateState(StateClass State);
    void MaximizeToolbox(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight);
    void MinimizeToolbox(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight);
    void ShowCentralBrowser(bool IsSettings);
    void HideCentralBrowser();
    std::pair<int,int> GetDefaultWindowSize();
    std::pair<int,int> GetDefaultBrowserSize();
    RECT GetDevToolsRectangle(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight);
    RECT GetToolboxRectangle(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight);
    RECT GetBrowserRectangle(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight);
    RECT GetBrowserOuterRectangle(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight);
    RECT GetStateIndicatorRectangle(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight);
    RECT GetLabelRectangle(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight);
    RECT GetCentralRectangle(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight);

    //Helpers
    HWND GetDevToolsHandle();

    void Timer(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight);
    HBITMAP GetHoldAnimationButton();


};

#endif // MAINLAYOUT_H

