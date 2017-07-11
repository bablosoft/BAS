#include "mainlayout.h"
#include "log.h"
#include <chrono>

using namespace std::chrono;
MainLayout* _Layout;

MainLayout::MainLayout(int ToolboxHeight, int ScenarioWidth)
{
    IsRecord = false;

    HButtonUp = 0;
    HButtonDown = 0;
    HButtonLeft = 0;
    HButtonRight = 0;
    HButtonUpUp = 0;
    HButtonDownDown = 0;
    HButtonLeftLeft = 0;
    HButtonRightRight = 0;
    HButtonDevTools = 0;
    HButtonScenario = 0;
    HButtonSettings = 0;

    IsMinimized = false;
    IsToolboxMaximized = false;
    IsCentralShown = false;
    IsSettingsShown = false;
    IsNoDataShown = false;
    HButtonMinimizeMaximize = 0;
    ButtonMinimize = 0;
    ButtonMaximize = 0;

    //Browsers
    BrowserHandle = 0;
    ToolBoxHandle = 0;
    CentralHandle = 0;
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

    DevToolsRectWidth = (ScenarioWidth == 0)?500:ScenarioWidth;
    ToolBoxRectHeight = (ToolboxHeight == 0)?300:ToolboxHeight;

    LastTimeChangedHoldPicture = 0;
    HoldAnimation = 0;

    //Splitter
    IsInsideScrollVertical = false;
    IsInsideScrollHorizontal = false;
    IsMoveScrollVertical = false;
    IsMoveScrollHorizontal = false;


    /*int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);


    if(DevToolsRectWidth > ScreenWidth - 600)
        DevToolsRectWidth = ScreenWidth - 600;

    if(ToolBoxRectHeight > ScreenHeight - 600)
        ToolBoxRectHeight = ScreenHeight - 600;*/

    //Is image select
    IsImageSelect = false;
    ImageSelectStartX = -1;
    ImageSelectStartY = -1;

    IsRenderEmpty = true;

}

void MainLayout::ShowCentralBrowser(bool IsSettings)
{
    if(CentralHandle)
    {
        IsSettingsShown = IsSettings;
        IsCentralShown = true;
        IsNoDataShown = false;
        ShowWindow(HButtonUp,SW_HIDE);
        ShowWindow(HButtonDown,SW_HIDE);
        ShowWindow(HButtonLeft,SW_HIDE);
        ShowWindow(HButtonRight,SW_HIDE);
        ShowWindow(CentralHandle,SW_SHOW);
        ShowWindow(HButtonUpUp,SW_HIDE);
        ShowWindow(HButtonDownDown,SW_HIDE);
        ShowWindow(HButtonLeftLeft,SW_HIDE);
        ShowWindow(HButtonRightRight,SW_HIDE);
    }

}
void MainLayout::HideCentralBrowser()
{
    if(CentralHandle)
    {
        if((IsNoDataShown || IsRenderEmpty) && IsRecord)
        {
            IsNoDataShown = true;
            IsCentralShown = false;
            IsCentralShown = true;
            for(auto f:EventLoadNoDataPage)
                f();
            return;
        }

        IsSettingsShown = false;
        IsCentralShown = false;
        IsNoDataShown = false;


        ShowWindow(HButtonUp,SW_SHOW);
        ShowWindow(HButtonDown,SW_SHOW);
        ShowWindow(HButtonLeft,SW_SHOW);
        ShowWindow(HButtonRight,SW_SHOW);
        ShowWindow(HButtonUpUp,SW_SHOW);
        ShowWindow(HButtonDownDown,SW_SHOW);
        ShowWindow(HButtonLeftLeft,SW_SHOW);
        ShowWindow(HButtonRightRight,SW_SHOW);
        ShowWindow(CentralHandle,SW_HIDE);
    }
}

void MainLayout::MaximizeToolbox(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight)
{
    if(ToolBoxHandle)
    {
        MoveWindow(ToolBoxHandle,0,0,WindowWidth,WindowHeight,true);
        ShowWindow(HButtonUp,SW_HIDE);
        ShowWindow(HButtonDown,SW_HIDE);
        ShowWindow(HButtonLeft,SW_HIDE);
        ShowWindow(HButtonRight,SW_HIDE);
        ShowWindow(HButtonUpUp,SW_HIDE);
        ShowWindow(HButtonDownDown,SW_HIDE);
        ShowWindow(HButtonLeftLeft,SW_HIDE);
        ShowWindow(HButtonRightRight,SW_HIDE);
        ShowWindow(HButtonDevTools,SW_HIDE);
        ShowWindow(HButtonScenario,SW_HIDE);
        ShowWindow(HButtonMinimizeMaximize,SW_HIDE);
        ShowWindow(HButtonSettings,SW_HIDE);

        IsToolboxMaximized = true;
    }

}
void MainLayout::MinimizeToolbox(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight)
{
    if(ToolBoxHandle)
    {
        RECT r = GetToolboxRectangle(BrowserWidth,BrowserHeight,WindowWidth,WindowHeight);
        MoveWindow(ToolBoxHandle,r.left,r.top,r.right - r.left,r.bottom - r.top,true);
        ShowWindow(HButtonUp,SW_SHOW);
        ShowWindow(HButtonDown,SW_SHOW);
        ShowWindow(HButtonLeft,SW_SHOW);
        ShowWindow(HButtonRight,SW_SHOW);
        ShowWindow(HButtonUpUp,SW_SHOW);
        ShowWindow(HButtonDownDown,SW_SHOW);
        ShowWindow(HButtonLeftLeft,SW_SHOW);
        ShowWindow(HButtonRightRight,SW_SHOW);
        ShowWindow(HButtonDevTools,SW_SHOW);
        ShowWindow(HButtonScenario,SW_SHOW);
        ShowWindow(HButtonMinimizeMaximize,SW_SHOW);
        ShowWindow(HButtonSettings,SW_SHOW);
        IsToolboxMaximized = false;
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
        //lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
        lStyle &= ~(WS_CAPTION | WS_THICKFRAME);
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
    InvalidateRect(MainWindowHandle,NULL,false);

}


void MainLayout::CalculateAllSize(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight, RECT& DevToolsRectangle, RECT& ToolboxRectangle, RECT& BrowserRectangle)
{
    DevToolsRectangle.left = 0;
    DevToolsRectangle.right = DevToolsRectWidth-3;
    DevToolsRectangle.top = 31;
    DevToolsRectangle.bottom = WindowHeight;

    ToolboxRectangle.left = DevToolsRectWidth+6;
    ToolboxRectangle.right = WindowWidth;
    ToolboxRectangle.top = 0;
    ToolboxRectangle.bottom = ToolBoxRectHeight - 4;

    if(IsRecord)
    {
        BrowserRectangle.left = DevToolsRectWidth+5;
        BrowserRectangle.right = WindowWidth-31;
        BrowserRectangle.top = ToolBoxRectHeight + 4;
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
        if(res && std::wstring(data,res) == CefBrowserWindow && (!_Layout->ToolBoxHandle || _Layout->ToolBoxHandle != hwnd)&& (!_Layout->ScenarioHandle || _Layout->ScenarioHandle != hwnd)&& (!_Layout->CentralHandle || _Layout->CentralHandle != hwnd))
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
    if(!SplitterIsChangingSize())
    {
        HWND DevToolsHandle = GetDevToolsHandle();
        if(DevToolsHandle)
            ShowWindow(DevToolsHandle,(DevToolsTab)?SW_SHOW:SW_HIDE);
        if(ScenarioHandle)
            ShowWindow(ScenarioHandle,(DevToolsTab)?SW_HIDE:SW_SHOW);
    }

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
        StateClass OldState = this->State;
        this->State = State;
        //EnableWindow(ToolBoxHandle,State == Ready);

        ShowWindow(HTextHold,(State == Hold)?SW_SHOW:SW_HIDE);
        ShowWindow(HTextFinished,(State == Finished)?SW_SHOW:SW_HIDE);
        RECT r = GetStateIndicatorRectangle(_Layout->BrowserWidth, _Layout->BrowserHeight, _Layout->WindowWidth, _Layout->WindowHeight);
        InvalidateRect(MainWindowHandle,&r,true);

        if((State == Hold || State == Finished) && !IsSettingsShown)
            HideCentralBrowser();

        if(State == Hold && OldState != Hold)
        {
            LastTimeChangedHoldPicture = duration_cast< milliseconds >( system_clock::now().time_since_epoch() ).count();
        }
    }
}

bool MainLayout::GetIsRenderEmpty()
{
    return IsRenderEmpty;
}

void MainLayout::SetIsRenderEmpty(bool IsRenderEmpty)
{
    if(IsRecord)
    {
        if(this->IsRenderEmpty && !IsRenderEmpty && IsNoDataShown)
        {
            this->IsRenderEmpty = IsRenderEmpty;
            IsNoDataShown = false;

            HideCentralBrowser();
        }else if(!this->IsRenderEmpty && IsRenderEmpty && !IsCentralShown)
        {
            this->IsRenderEmpty = IsRenderEmpty;

            ShowCentralBrowser(false);
            IsNoDataShown = true;
            IsCentralShown = true;
            IsSettingsShown = false;
            for(auto f:EventLoadNoDataPage)
                f();
        }
        else
        {
            this->IsRenderEmpty = IsRenderEmpty;
        }
    }
}

void MainLayout::CustomDraw(HDC hdc,int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight)
{
    if(!IsRecord)
        return;

    if(IsToolboxMaximized)
        return;
    if(!SplitterIsChangingSize())
    {
        POINT pt;
        SelectObject(hdc, GetStockObject(DC_PEN));
        SetDCPenColor(hdc, RGB(125,125,125));

        MoveToEx(hdc, 0, 30, &pt);
        LineTo(hdc, DevToolsRectWidth - 3, 30);
    }

    RECT rect;
    HBRUSH brush = CreateSolidBrush(RGB(225, 225, 225));

    rect.left = DevToolsRectWidth - 2;
    rect.right = DevToolsRectWidth + 5;
    rect.top = 0;
    rect.bottom = WindowHeight;

    FillRect(hdc, &rect, brush);


    rect.left = DevToolsRectWidth + 5;
    rect.right = WindowWidth;
    rect.top = ToolBoxRectHeight-3;
    rect.bottom = ToolBoxRectHeight+3;

    FillRect(hdc, &rect, brush);
    DeleteObject(brush);

}

bool MainLayout::DrawImageSelect(HDC hdc)
{
    if(!GetIsImageSelect())
    {
        return false;
    }
    POINT pt;
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, RGB(0,255,0));

    MoveToEx(hdc, ImageSelectStartX, ImageSelectStartY, &pt);
    LineTo(hdc, ImageSelectStartX, ImageSelectEndY);

    MoveToEx(hdc, ImageSelectStartX, ImageSelectEndY, &pt);
    LineTo(hdc, ImageSelectEndX, ImageSelectEndY);

    MoveToEx(hdc, ImageSelectEndX, ImageSelectEndY, &pt);
    LineTo(hdc, ImageSelectEndX, ImageSelectStartY);

    MoveToEx(hdc, ImageSelectEndX, ImageSelectStartY, &pt);
    LineTo(hdc, ImageSelectStartX, ImageSelectStartY);
    return true;
}

bool MainLayout::GetIsImageSelect()
{
    return IsImageSelect && std::abs(ImageSelectStartX - ImageSelectEndX) > 5 && std::abs(ImageSelectStartY - ImageSelectEndY) > 5;
}

RECT MainLayout::GetBrowserOuterRectangle(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight)
{
    RECT r;
    r.left = DevToolsRectWidth + 5;
    r.top = ToolBoxRectHeight + 3;
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
        ShowWindow(HButtonUpUp,SW_HIDE);
        ShowWindow(HButtonDownDown,SW_HIDE);
        ShowWindow(HButtonLeftLeft,SW_HIDE);
        ShowWindow(HButtonRightRight,SW_HIDE);
        ShowWindow(HButtonDevTools,SW_HIDE);
        ShowWindow(HButtonScenario,SW_HIDE);
        ShowWindow(HButtonSettings,SW_HIDE);
        ShowWindow(HTextHold,SW_HIDE);
        ShowWindow(HTextFinished,SW_HIDE);
    }



    UpdateState(State);
    UpdateTabs();

    RECT r = GetBrowserOuterRectangle(BrowserWidth, BrowserHeight, WindowWidth, WindowHeight);
    if(!IsCentralShown)
        InvalidateRect(MainWindowHandle,&r,true);

    this->BrowserWidth = BrowserWidth;
    this->BrowserHeight = BrowserHeight;
    this->WindowWidth = WindowWidth;
    this->WindowHeight = WindowHeight;
    RECT ToolboxRectangle = GetToolboxRectangle(BrowserWidth, BrowserHeight, WindowWidth, WindowHeight);
    RECT BrowserRectangle = GetBrowserRectangle(BrowserWidth, BrowserHeight, WindowWidth, WindowHeight);


    if(IsToolboxMaximized)
    {
        MoveWindow(ToolBoxHandle,0,0,WindowWidth,WindowHeight,true);
    }else
    {
        MoveWindow(ToolBoxHandle,ToolboxRectangle.left,ToolboxRectangle.top,ToolboxRectangle.right - ToolboxRectangle.left,ToolboxRectangle.bottom - ToolboxRectangle.top,true);
    }

    if(CentralHandle)
    {
        RECT CentralRectangle = GetCentralRectangle(BrowserWidth, BrowserHeight, WindowWidth, WindowHeight);
        MoveWindow(CentralHandle,CentralRectangle.left,CentralRectangle.top,CentralRectangle.right - CentralRectangle.left,CentralRectangle.bottom - CentralRectangle.top,true);
    }

    MoveDevTools();

    MoveWindow(HButtonUpUp,BrowserRectangle.right + 5, BrowserRectangle.bottom - 111,20,20,true);
    MoveWindow(HButtonUp,BrowserRectangle.right + 5,BrowserRectangle.bottom - 90,20,20,true);
    MoveWindow(HButtonDown,BrowserRectangle.right + 5, BrowserRectangle.bottom - 60,20,20,true);
    MoveWindow(HButtonDownDown,BrowserRectangle.right + 5, BrowserRectangle.bottom - 39,20,20,true);

    MoveWindow(HButtonLeftLeft,BrowserRectangle.right - 111, BrowserRectangle.bottom + 5,20,20,true);
    MoveWindow(HButtonLeft,BrowserRectangle.right - 90, BrowserRectangle.bottom + 5,20,20,true);
    MoveWindow(HButtonRight,BrowserRectangle.right - 60, BrowserRectangle.bottom + 5,20,20,true);
    MoveWindow(HButtonRightRight,BrowserRectangle.right - 39, BrowserRectangle.bottom + 5,20,20,true);

    MoveWindow(HButtonSettings,BrowserRectangle.right + 5, BrowserRectangle.top + 21,20,20,true);

    MoveWindow(HButtonMinimizeMaximize,BrowserRectangle.right + 5,BrowserRectangle.top,20,20,true);

    MoveWindow(HButtonDevTools,5,5,20,20,true);
    MoveWindow(HButtonScenario,35,5,20,20,true);
    MoveWindow(HTextHold,70,7,DevToolsRectWidth - 100,23,true);
    MoveWindow(HTextFinished,70,7,DevToolsRectWidth - 100,23,true);


}

std::pair<int,int> MainLayout::GetDefaultWindowSize()
{
    std::pair<int,int> res;
    res.first = 1024 + DevToolsRectWidth + 30 + 70 + 3;
    res.second = 600 + ToolBoxRectHeight - 4 + 30 + 120;
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

RECT MainLayout::GetCentralRectangle(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight)
{
    RECT DevToolsRectangle, ToolboxRectangle, BrowserRectangle;
    CalculateAllSize(BrowserWidth,BrowserHeight,WindowWidth,WindowHeight,DevToolsRectangle, ToolboxRectangle, BrowserRectangle);
    BrowserRectangle.bottom += 30;
    return BrowserRectangle;
}

RECT MainLayout::GetLabelRectangle(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight)
{
    RECT DevToolsRectangle, ToolboxRectangle, BrowserRectangle;
    CalculateAllSize(BrowserWidth,BrowserHeight,WindowWidth,WindowHeight,DevToolsRectangle, ToolboxRectangle, BrowserRectangle);
    RECT res;
    res.left = BrowserRectangle.left;
    res.right = BrowserRectangle.right - 121;
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

void MainLayout::Timer(int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight)
{
    //Hold Animation
    if(IsRecord && State == MainLayout::Hold)
    {
        long long now = duration_cast< milliseconds >( system_clock::now().time_since_epoch() ).count();
        long long delta = now - LastTimeChangedHoldPicture;
        bool res = delta > 850;

        if(res)
        {
            LastTimeChangedHoldPicture += (delta / 850) * 850;
            HoldAnimation += (delta / 850);
            HoldAnimation %=2;

            RECT r = GetStateIndicatorRectangle(BrowserWidth,BrowserHeight,WindowWidth,WindowHeight);
            InvalidateRect(MainWindowHandle,&r,false);
        }
    }
}

HBITMAP MainLayout::GetHoldAnimationButton()
{
    switch(HoldAnimation)
    {
        case 0:return BHold;
        case 1:return BHold90;
    }
}

//Splitter

void MainLayout::SplitterSetCursor()
{
    if(IsMoveScrollVertical || IsInsideScrollVertical)
    {
        SetCursor(hcSizeNS);


    }else if(IsMoveScrollHorizontal || IsInsideScrollHorizontal)
    {
        SetCursor(hcSizeEW);
    }
    else
    {
        SetCursor(hcArrow);
    }

}

bool MainLayout::OnMouseMove(int x, int y, int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight)
{
    if(!IsRecord)
        return false;

    if(!IsImageSelect)
    {
        RECT r = GetBrowserRectangle(BrowserWidth,BrowserHeight,WindowWidth,WindowHeight);

        ImageSelectEndX = -1;
        ImageSelectEndY = -1;

        if(x > r.left && x < r.right && y > r.top && y < r.bottom)
        {
            ImageSelectStartX = x - r.left;
            ImageSelectStartY = y - r.top;
        }else
        {
            ImageSelectStartX = -1;
            ImageSelectStartY = -1;
        }

    }else
    {

        RECT r = GetBrowserRectangle(BrowserWidth,BrowserHeight,WindowWidth,WindowHeight);
        if(x > r.left && x < r.right && y > r.top && y < r.bottom)
        {
            ImageSelectEndX = x - r.left;
            ImageSelectEndY = y - r.top;
        }else
        {
            IsImageSelect = false;
            ImageSelectStartX = -1;
            ImageSelectStartY = -1;
            ImageSelectEndX = -1;
            ImageSelectEndY = -1;
        }
    }

    SplitterX = x;
    SplitterY = y;

    if(x > WindowWidth - 20 || y > WindowHeight - 20 || x < 20 || y < 20)
    {
        return OnMouseLeave();
    }

    if(IsMoveScrollVertical)
    {
        ToolBoxRectHeight = y;
        if(MainWindowHandle)
            InvalidateRect(MainWindowHandle,NULL,true);
    }

    if(IsMoveScrollHorizontal)
    {
        DevToolsRectWidth = x;
        if(MainWindowHandle)
            InvalidateRect(MainWindowHandle,NULL,true);

    }

    if(x >= DevToolsRectWidth - 2 && x <= DevToolsRectWidth + 5)
    {
        IsInsideScrollHorizontal = true;
        IsInsideScrollVertical = false;
    }else if(y >= ToolBoxRectHeight - 3 && y <= ToolBoxRectHeight + 3 && x > DevToolsRectWidth - 2)
    {
        IsInsideScrollHorizontal = false;
        IsInsideScrollVertical = true;
    }
    else
    {
        IsInsideScrollHorizontal = false;
        IsInsideScrollVertical = false;
    }
    SplitterSetCursor();
    return false;
}

bool MainLayout::OnMouseLeave()
{
    if(!IsRecord)
        return false;

    IsImageSelect = false;

    if(!IsMoveScrollVertical && !IsMoveScrollHorizontal)
        return false;
    if(IsMoveScrollHorizontal)
        DevToolsRectWidth = DevToolsRectWidthStart;
    if(IsMoveScrollVertical)
        ToolBoxRectHeight = ToolBoxRectHeightStart;
    return OnMouseUp();

}

bool MainLayout::OnMouseUp()
{
    if(!IsRecord)
        return false;

    IsImageSelect = false;
    ImageSelectStartX = -1;
    ImageSelectStartY = -1;

    if(!IsMoveScrollVertical && !IsMoveScrollHorizontal)
        return false;

    bool NeedUpdate = SplitterIsChangingSize();
    IsMoveScrollHorizontal = false;
    IsMoveScrollVertical = false;
    SplitterShowInterface();

    SplitterSetCursor();

    return NeedUpdate;
}
bool MainLayout::OnMouseDown(int x, int y, int BrowserWidth,int BrowserHeight,int WindowWidth,int WindowHeight)
{
    if(!IsRecord)
        return false;
    if(IsInsideScrollHorizontal)
    {
        IsMoveScrollHorizontal = true;
        DevToolsRectWidthStart = DevToolsRectWidth;
        SplitterHideInterface();

    }

    if(IsInsideScrollVertical)
    {
        IsMoveScrollVertical = true;
        ToolBoxRectHeightStart = ToolBoxRectHeight;
        SplitterHideInterface();

    }
    SplitterSetCursor();

    if(!IsImageSelect)
    {
        RECT r = GetBrowserRectangle(BrowserWidth,BrowserHeight,WindowWidth,WindowHeight);

        ImageSelectEndX = -1;
        ImageSelectEndY = -1;

        if(x > r.left && x < r.right && y > r.top && y < r.bottom)
        {
            ImageSelectStartX = x - r.left;
            ImageSelectStartY = y - r.top;
        }else
        {
            ImageSelectStartX = -1;
            ImageSelectStartY = -1;
        }

        if(ImageSelectStartX >= 0 && ImageSelectStartY >= 0)
        {
            IsImageSelect = true;
            ImageSelectEndX = ImageSelectStartX;
            ImageSelectEndY = ImageSelectStartY;
        }
    }

    return false;
}

void MainLayout::SplitterHideInterface()
{
    if(ToolBoxHandle)
        ShowWindow(ToolBoxHandle,SW_HIDE);

    if(ScenarioHandle)
        ShowWindow(ScenarioHandle,SW_HIDE);

    if(CentralHandle)
        ShowWindow(CentralHandle,SW_HIDE);

    GetDevToolsHandle();
    if(DevToolsHandle)
        ShowWindow(DevToolsHandle,SW_HIDE);


    if(HButtonSettings)
        ShowWindow(HButtonSettings,SW_HIDE);
    if(HButtonScenario)
        ShowWindow(HButtonScenario,SW_HIDE);
    if(HButtonDevTools)
        ShowWindow(HButtonDevTools,SW_HIDE);


    if(HButtonUp)
        ShowWindow(HButtonUp,SW_HIDE);
    if(HButtonDown)
        ShowWindow(HButtonDown,SW_HIDE);
    if(HButtonLeft)
        ShowWindow(HButtonLeft,SW_HIDE);
    if(HButtonRight)
        ShowWindow(HButtonRight,SW_HIDE);

    if(HButtonUpUp)
        ShowWindow(HButtonUpUp,SW_HIDE);
    if(HButtonDownDown)
        ShowWindow(HButtonDownDown,SW_HIDE);
    if(HButtonLeftLeft)
        ShowWindow(HButtonLeftLeft,SW_HIDE);
    if(HButtonRightRight)
        ShowWindow(HButtonRightRight,SW_HIDE);

    if(HButtonMinimizeMaximize)
        ShowWindow(HButtonMinimizeMaximize,SW_HIDE);

    if(HTextHold)
        ShowWindow(HTextHold,SW_HIDE);

    if(HTextFinished)
        ShowWindow(HTextFinished,SW_HIDE);

    if(MainWindowHandle)
        InvalidateRect(MainWindowHandle,NULL,true);
}

void MainLayout::SplitterShowInterface()
{
    if(ToolBoxHandle)
        ShowWindow(ToolBoxHandle,SW_SHOW);

    if(ScenarioHandle)
        ShowWindow(ScenarioHandle,(DevToolsTab)?SW_HIDE:SW_SHOW);

    if(CentralHandle)
        ShowWindow(CentralHandle,(IsCentralShown)?SW_SHOW:SW_HIDE);

    GetDevToolsHandle();
    if(DevToolsHandle)
        ShowWindow(DevToolsHandle,(DevToolsTab)?SW_SHOW:SW_HIDE);


    if(HButtonUp)
        ShowWindow(HButtonUp,(!IsCentralShown && !IsSettingsShown)?SW_SHOW:SW_HIDE);
    if(HButtonDown)
        ShowWindow(HButtonDown,(!IsCentralShown && !IsSettingsShown)?SW_SHOW:SW_HIDE);
    if(HButtonLeft)
        ShowWindow(HButtonLeft,(!IsCentralShown && !IsSettingsShown)?SW_SHOW:SW_HIDE);
    if(HButtonRight)
        ShowWindow(HButtonRight,(!IsCentralShown && !IsSettingsShown)?SW_SHOW:SW_HIDE);

    if(HButtonUpUp)
        ShowWindow(HButtonUpUp,(!IsCentralShown && !IsSettingsShown)?SW_SHOW:SW_HIDE);
    if(HButtonDownDown)
        ShowWindow(HButtonDownDown,(!IsCentralShown && !IsSettingsShown)?SW_SHOW:SW_HIDE);
    if(HButtonLeftLeft)
        ShowWindow(HButtonLeftLeft,(!IsCentralShown && !IsSettingsShown)?SW_SHOW:SW_HIDE);
    if(HButtonRightRight)
        ShowWindow(HButtonRightRight,(!IsCentralShown && !IsSettingsShown)?SW_SHOW:SW_HIDE);


    if(HButtonSettings)
        ShowWindow(HButtonSettings,SW_SHOW);
    if(HButtonScenario)
        ShowWindow(HButtonScenario,SW_SHOW);
    if(HButtonDevTools)
        ShowWindow(HButtonDevTools,SW_SHOW);

    if(HButtonMinimizeMaximize)
        ShowWindow(HButtonMinimizeMaximize,SW_SHOW);


    if(HTextHold)
        ShowWindow(HTextHold,(State == Hold)?SW_SHOW:SW_HIDE);

    if(HTextFinished)
        ShowWindow(HTextFinished,(State == Finished)?SW_SHOW:SW_HIDE);

    if(MainWindowHandle)
        InvalidateRect(MainWindowHandle,NULL,true);


}

bool MainLayout::SplitterIsChangingSize()
{
    return IsMoveScrollVertical || IsMoveScrollHorizontal;
}

