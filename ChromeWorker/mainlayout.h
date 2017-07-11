#ifndef MAINLAYOUT_H
#define MAINLAYOUT_H

#include <windows.h>
#include <vector>
#include <functional>


class MainLayout
{
    void MoveDevTools();
    void CalculateAllSize(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight, RECT& DevToolsRectangle, RECT& ToolboxRectangle, RECT& BrowserRectangle);
    bool DevToolsTab;

    long long LastTimeChangedHoldPicture;
    int HoldAnimation;
    bool IsRenderEmpty;


public:

    enum StateClass{Ready,Hold,Finished}State;

    bool IsRecord;
    bool IsCentralShown;
    bool IsSettingsShown;
    bool IsNoDataShown;

    int DevToolsRectWidth;
    int ToolBoxRectHeight;

    //Minimize/Maximize
    bool IsMinimized;
    bool IsToolboxMaximized;
    HBITMAP ButtonMinimize, ButtonMaximize;
    HBITMAP BHold,BHold90;
    HWND HButtonMinimizeMaximize;
    LONG SavelStyle,SavelExStyle;


    //Buttons
    HWND HButtonUp,HButtonDown,HButtonLeft,HButtonRight;
    HWND HButtonUpUp,HButtonDownDown,HButtonLeftLeft,HButtonRightRight;
    HWND HButtonDevTools,HButtonScenario;
    HWND HButtonSettings;

    //Cursors
    HCURSOR hcSizeNS, hcSizeEW, hcArrow;

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
    bool DrawImageSelect(HDC hdc);
    void UpdateTabs(bool DevToolsTab);
    bool IsDevToolsTab();
    void UpdateTabs();
    void UpdateState(StateClass State);
    void SetIsRenderEmpty(bool IsRenderEmpty);
    bool GetIsRenderEmpty();
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

    //Splitter
    int DevToolsRectWidthStart;
    int ToolBoxRectHeightStart;
    bool IsInsideScrollVertical;
    bool IsInsideScrollHorizontal;
    bool IsMoveScrollVertical;
    bool IsMoveScrollHorizontal;
    int SplitterX;
    int SplitterY;
    bool OnMouseMove(int x, int y, int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight);
    bool OnMouseUp();
    bool OnMouseLeave();
    bool OnMouseDown(int x, int y, int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight);
    void SplitterSetCursor();
    void SplitterHideInterface();
    void SplitterShowInterface();
    bool SplitterIsChangingSize();

    //Image select
    bool GetIsImageSelect();
    bool IsImageSelect;
    int ImageSelectStartX;
    int ImageSelectStartY;
    int ImageSelectEndX;
    int ImageSelectEndY;

    std::vector<std::function<void()> > EventLoadNoDataPage;



};

#endif // MAINLAYOUT_H

