#include "mainlayout.h"
MainLayout* _Layout;


MainLayout::MainLayout()
{
    IsRecord = false;

    HButtonUp = 0;
    HButtonDown = 0;
    HButtonLeft = 0;
    HButtonRight = 0;
    HButtonDevTools = 0;
    HButtonScenario = 0;

    IsMinimized = false;
    HButtonMinimizeMaximize = 0;
    ButtonMinimize = 0;
    ButtonMaximize = 0;

    //Browsers
    BrowserHandle = 0;
    ToolBoxHandle = 0;
    ScenarioHandle = 0;
    DevToolsHandle = 0;

    //Mainwindow
    MainWindowHandle = 0;

    //Images
    ButtonDevToolsBitmap = 0;
    ButtonDevToolsBitmapGray = 0;
    ButtonScenarioBitmap = 0;
    ButtonScenarioBitmapGray = 0;

    DevToolsTab = false;

    _Layout = this;

    State = Hold;


    int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);

    DevToolsRectWidth = 500;
    if(DevToolsRectWidth + 850 > ScreenWidth)
    {
        DevToolsRectWidth = ScreenWidth - 850;
    }
}

void MainLayout::MinimizeOrMaximize(HWND MainWindow, HWND ParentWindow)
{
    IsMinimized = !IsMinimized;
    if(!MainWindow || !ParentWindow || !HButtonMinimizeMaximize || !ButtonMinimize || !ButtonMaximize)
        return;
    if(IsMinimized)
    {
        SetParent(MainWindow,ParentWindow);

        LONG lStyle = GetWindowLong( MainWindow, GWL_STYLE );
        SavelStyle = lStyle;
        lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
        SetWindowLong( MainWindow, GWL_STYLE, lStyle);
        LONG lExStyle = GetWindowLong( MainWindow, GWL_EXSTYLE );
        SavelExStyle = lExStyle;
        lExStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
        SetWindowLong( MainWindow, GWL_EXSTYLE, lExStyle );

        SendMessage(HButtonMinimizeMaximize, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)ButtonMaximize);

    }else
    {
        SetParent(MainWindow,0);

        SetWindowLong( MainWindow, GWL_STYLE, SavelStyle );
        SetWindowLong( MainWindow, GWL_EXSTYLE, SavelExStyle );

        ShowWindow(MainWindow,SW_SHOWMAXIMIZED);
        SetForegroundWindow(MainWindow);
        SetActiveWindow(MainWindow);
        FlashWindow(MainWindow,true);
        SendMessage(HButtonMinimizeMaximize, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)ButtonMinimize);
    }
}


void MainLayout::CalculateAllSize(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight, RECT& DevToolsRectangle, RECT& ToolboxRectangle, RECT& BrowserRectangle)
{
    DevToolsRectangle.left = 0;
    DevToolsRectangle.right = DevToolsRectWidth;
    DevToolsRectangle.top = 31;
    DevToolsRectangle.bottom = WindowHeight;

    ToolboxRectangle.left = DevToolsRectWidth+2;
    ToolboxRectangle.right = WindowWidth;
    ToolboxRectangle.top = 0;
    ToolboxRectangle.bottom = 220;

    if(IsRecord)
    {
        BrowserRectangle.left = DevToolsRectWidth+2;
        BrowserRectangle.right = WindowWidth-31;
        BrowserRectangle.top = 222;
        BrowserRectangle.bottom = WindowHeight-31;
    }else
    {
        BrowserRectangle.left = 0;
        BrowserRectangle.right = WindowWidth;
        BrowserRectangle.top = 0;
        BrowserRectangle.bottom = WindowHeight;
    }

    int AvailableWidth = BrowserRectangle.right - BrowserRectangle.left;
    int AvailableHeight = BrowserRectangle.bottom - BrowserRectangle.top;

    int ResultWidth = BrowserWidth, ResultHeight = BrowserHeight;
    if(AvailableWidth < ResultWidth)
    {
        ResultWidth = AvailableWidth;
        ResultHeight = (float)(BrowserHeight * ResultWidth) / (float)BrowserWidth;
    }

    if(AvailableHeight < ResultHeight)
    {
        ResultHeight = AvailableHeight;
        ResultWidth = (float)(BrowserWidth * ResultHeight) / (float)BrowserHeight;
    }

    BrowserRectangle.left = BrowserRectangle.left + (AvailableWidth - ResultWidth) / 2;
    BrowserRectangle.top = BrowserRectangle.top + (AvailableHeight - ResultHeight) / 2;
    BrowserRectangle.right = BrowserRectangle.left + ResultWidth;
    BrowserRectangle.bottom = BrowserRectangle.top + ResultHeight;

}


BOOL CALLBACK FindDevToolsIteration(HWND hwnd, LPARAM lParam)
{
    if(GetParent(hwnd) == _Layout->MainWindowHandle)
    {
        std::wstring CefBrowserWindow = L"CefBrowserWindow";
        wchar_t data[256];
        int res = GetClassName(hwnd,data,256);
        if(res && std::wstring(data,res) == CefBrowserWindow && (!_Layout->ToolBoxHandle || _Layout->ToolBoxHandle != hwnd)&& (!_Layout->ScenarioHandle || _Layout->ScenarioHandle != hwnd))
        {
            _Layout->DevToolsHandle = hwnd;
            return false;
        }
    }
    return true;
}

HWND MainLayout::GetDevToolsHandle()
{
    DevToolsHandle = 0;
    if(MainWindowHandle)
        EnumChildWindows(MainWindowHandle,FindDevToolsIteration,NULL);
    return DevToolsHandle;
}

void MainLayout::MoveDevTools()
{
    HWND DevToolsHandle = GetDevToolsHandle();
    if(DevToolsHandle)
    {
        RECT DevToolsRectangle = _Layout->GetDevToolsRectangle(_Layout->BrowserWidth, _Layout->BrowserHeight, _Layout->WindowWidth, _Layout->WindowHeight);
        MoveWindow(DevToolsHandle,DevToolsRectangle.left,DevToolsRectangle.top,DevToolsRectangle.right - DevToolsRectangle.left,DevToolsRectangle.bottom - DevToolsRectangle.top,true);
    }

    if(ScenarioHandle)
    {
        RECT Rectangle = _Layout->GetDevToolsRectangle(_Layout->BrowserWidth, _Layout->BrowserHeight, _Layout->WindowWidth, _Layout->WindowHeight);
        MoveWindow(ScenarioHandle,Rectangle.left,Rectangle.top,Rectangle.right - Rectangle.left,Rectangle.bottom - Rectangle.top,true);
    }
}

void MainLayout::UpdateTabs()
{
    UpdateTabs(DevToolsTab);
}

void MainLayout::UpdateTabs(bool DevToolsTab)
{
    this->DevToolsTab = DevToolsTab;
    HWND DevToolsHandle = GetDevToolsHandle();
    if(DevToolsHandle)
        ShowWindow(DevToolsHandle,(DevToolsTab)?SW_SHOW:SW_HIDE);
    if(ScenarioHandle)
        ShowWindow(ScenarioHandle,(DevToolsTab)?SW_HIDE:SW_SHOW);

    if(DevToolsTab)
    {
        if(HButtonDevTools && ButtonDevToolsBitmap && ButtonDevToolsBitmapGray)
        {
            SendMessage(HButtonDevTools, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)ButtonDevToolsBitmap);
        }

        if(HButtonScenario && ButtonScenarioBitmap && ButtonScenarioBitmapGray)
        {
            SendMessage(HButtonScenario, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)ButtonScenarioBitmapGray);
        }
    }else
    {
        if(HButtonDevTools && ButtonDevToolsBitmap && ButtonDevToolsBitmapGray)
        {
            SendMessage(HButtonDevTools, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)ButtonDevToolsBitmapGray);
        }

        if(HButtonScenario && ButtonScenarioBitmap && ButtonScenarioBitmapGray)
        {
            SendMessage(HButtonScenario, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)ButtonScenarioBitmap);
        }

    }
}

bool MainLayout::IsDevToolsTab()
{
    return DevToolsTab;
}

void MainLayout::UpdateState(StateClass State)
{
    if(IsRecord)
    {
        this->State = State;
        EnableWindow(ToolBoxHandle,State == Ready);

        ShowWindow(HTextHold,(State == Hold)?SW_SHOW:SW_HIDE);
        ShowWindow(HTextFinished,(State == Finished)?SW_SHOW:SW_HIDE);
        RECT r = GetStateIndicatorRectangle(_Layout->BrowserWidth, _Layout->BrowserHeight, _Layout->WindowWidth, _Layout->WindowHeight);
        InvalidateRect(MainWindowHandle,&r,true);
    }
}

void MainLayout::CustomDraw(HDC hdc,int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight)
{
    if(!IsRecord)
        return;
    POINT pt;
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, RGB(125,125,125));

    MoveToEx(hdc, DevToolsRectWidth + 1, 0, &pt);
    LineTo(hdc, DevToolsRectWidth + 1, WindowHeight);

    MoveToEx(hdc, 0, 30, &pt);
    LineTo(hdc, DevToolsRectWidth, 30);

    MoveToEx(hdc, DevToolsRectWidth + 2, 221, &pt);
    LineTo(hdc, WindowWidth, 221);

}

RECT MainLayout::GetBrowserOuterRectangle(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight)
{
    RECT r;
    r.left = DevToolsRectWidth + 2;
    r.top = 221;
    if(!IsRecord)
    {
        r.left = 0;
        r.top = 0;
    }
    r.right = WindowWidth;

    r.bottom = WindowHeight;
    return r;
}

void MainLayout::Update(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight)
{
    if(!IsRecord)
    {
        ShowWindow(HButtonMinimizeMaximize,SW_HIDE);
        ShowWindow(HButtonUp,SW_HIDE);
        ShowWindow(HButtonDown,SW_HIDE);
        ShowWindow(HButtonLeft,SW_HIDE);
        ShowWindow(HButtonRight,SW_HIDE);
        ShowWindow(HButtonDevTools,SW_HIDE);
        ShowWindow(HButtonScenario,SW_HIDE);
        ShowWindow(HTextHold,SW_HIDE);
        ShowWindow(HTextFinished,SW_HIDE);
    }

    UpdateState(State);
    UpdateTabs();

    RECT r = GetBrowserOuterRectangle(BrowserWidth, BrowserHeight, WindowWidth, WindowHeight);
    InvalidateRect(MainWindowHandle,&r,true);

    this->BrowserWidth = BrowserWidth;
    this->BrowserHeight = BrowserHeight;
    this->WindowWidth = WindowWidth;
    this->WindowHeight = WindowHeight;
    RECT ToolboxRectangle = GetToolboxRectangle(BrowserWidth, BrowserHeight, WindowWidth, WindowHeight);
    RECT BrowserRectangle = GetBrowserRectangle(BrowserWidth, BrowserHeight, WindowWidth, WindowHeight);


    MoveWindow(ToolBoxHandle,ToolboxRectangle.left,ToolboxRectangle.top,ToolboxRectangle.right - ToolboxRectangle.left,ToolboxRectangle.bottom - ToolboxRectangle.top,true);
    MoveDevTools();

    MoveWindow(HButtonUp,BrowserRectangle.right + 5,BrowserRectangle.bottom - 90,20,20,true);
    MoveWindow(HButtonDown,BrowserRectangle.right + 5, BrowserRectangle.bottom - 60,20,20,true);
    MoveWindow(HButtonLeft,BrowserRectangle.right - 90, BrowserRectangle.bottom + 5,20,20,true);
    MoveWindow(HButtonRight,BrowserRectangle.right - 60, BrowserRectangle.bottom + 5,20,20,true);

    MoveWindow(HButtonMinimizeMaximize,BrowserRectangle.right + 5,BrowserRectangle.top + 5,20,20,true);

    MoveWindow(HButtonDevTools,5,5,20,20,true);
    MoveWindow(HButtonScenario,35,5,20,20,true);
    MoveWindow(HTextHold,70,7,DevToolsRectWidth - 100,23,true);
    MoveWindow(HTextFinished,70,7,DevToolsRectWidth - 100,23,true);

}

std::pair<int,int> MainLayout::GetDefaultWindowSize()
{
    std::pair<int,int> res;
    res.first = 1024 + DevToolsRectWidth + 30 + 70;
    res.second = 600 + 220 + 30 + 120;
    return res;
}

std::pair<int,int> MainLayout::GetDefaultBrowserSize()
{
    std::pair<int,int> res;
    res.first = 1024;
    res.second = 600;
    return res;
}


RECT MainLayout::GetDevToolsRectangle(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight)
{
    RECT DevToolsRectangle, ToolboxRectangle, BrowserRectangle;
    CalculateAllSize(BrowserWidth,BrowserHeight,WindowWidth,WindowHeight,DevToolsRectangle, ToolboxRectangle, BrowserRectangle);
    return DevToolsRectangle;
}

RECT MainLayout::GetToolboxRectangle(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight)
{
    RECT DevToolsRectangle, ToolboxRectangle, BrowserRectangle;
    CalculateAllSize(BrowserWidth,BrowserHeight,WindowWidth,WindowHeight,DevToolsRectangle, ToolboxRectangle, BrowserRectangle);
    return ToolboxRectangle;
}

RECT MainLayout::GetBrowserRectangle(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight)
{
    RECT DevToolsRectangle, ToolboxRectangle, BrowserRectangle;
    CalculateAllSize(BrowserWidth,BrowserHeight,WindowWidth,WindowHeight,DevToolsRectangle, ToolboxRectangle, BrowserRectangle);
    return BrowserRectangle;
}

RECT MainLayout::GetLabelRectangle(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight)
{
    RECT DevToolsRectangle, ToolboxRectangle, BrowserRectangle;
    CalculateAllSize(BrowserWidth,BrowserHeight,WindowWidth,WindowHeight,DevToolsRectangle, ToolboxRectangle, BrowserRectangle);
    RECT res;
    res.left = BrowserRectangle.left;
    res.right = BrowserRectangle.right - 100;
    res.top = BrowserRectangle.bottom + 3;
    res.bottom = BrowserRectangle.bottom + 20;
    return res;
}

RECT MainLayout::GetStateIndicatorRectangle(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight)
{
    RECT r;
    r.top = 5;
    r.left = DevToolsRectWidth-5-20;
    r.right = DevToolsRectWidth-5;
    r.bottom = 25;
    return r;
}

