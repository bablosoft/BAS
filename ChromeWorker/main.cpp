#include <windows.h>
#include <thread>
#include "converter.h"
#include "mainapp.h"
#include "include/cef_app.h"
#include "pipesclient.h"
#include "commandparser.h"
#include "log.h"
#include "processcheck.h"
#include "browserdata.h"
#include "resource.h"
#include "mainlayout.h"
#include "settings.h"
#include "translate.h"
#include "opensslmultithreaded.h"
#include "multithreading.h"
#include "modulesdata.h"
#include "fontreplace.h"
#include "postmanager.h"

#if defined(BAS_DEBUG)
    #include "CrashHandler.h"
#endif

int pid = -1;
CefRefPtr<MainApp> app;
PipesClient *Client;
CommandParser *Parser;
HWND MousePositionMouseHandle,hwnd,HButtonUp,HButtonDown,HButtonLeft,HButtonRight,HButtonDevTools,HButtonScenario,HTextHold,HTextFinished;
HWND HButtonUpUp,HButtonDownDown,HButtonLeftLeft,HButtonRightRight;
enum{IDButtonTerminate = 1000,IDButtonQuit,IDButtonUp,IDButtonDown,IDButtonLeft,IDButtonRight,IDButtonUpUp,IDButtonDownDown,IDButtonLeftLeft,IDButtonRightRight,IDButtonMinimizeMaximize,IDButtonDevTools,IDButtonScenario,IDButtonSettings,IDTextHold,IDTextFinished,IDClick,IDMove,IDNone,IDMoveAndClick,IDDrag,IDDrop,IDDragElement,IDDropElement,IDInspect,IDXml,IDText,IDScript,IDClickElement,IDMoveElement,IDMoveAndClickElement,IDClear,IDType,IDExists,IDStyle,IDCheck,IDScreenshot,IDCoordinates,IDFocus,IDSet,IDSetInteger,IDSetRandom,IDGetAttr,IDSetAttr,IDCaptcha,IDLength,IDWaitElement,
    IDLoop,IDXmlLoop,IDTextLoop,IDScriptLoop,IDClickElementLoop,IDMoveElementLoop,IDMoveAndClickElementLoop,IDClearLoop,IDTypeLoop,IDExistsLoop,IDStyleLoop,IDCheckLoop,IDScreenshotLoop,IDCoordinatesLoop,IDFocusLoop,IDSetLoop,IDSetIntegerLoop,IDSetRandomLoop,IDGetAttrLoop,IDSetAttrLoop,IDCaptchaLoop,IDCustom = 30000,IDCustomForeach = 40000,IDCustomPopups = 50000};
HBITMAP BReady,BFinished;
HCURSOR HCursor;
using namespace std::placeholders;
HMENU hPopupMenu = 0;
HMENU hForEachMenu = 0;
HMENU hTabsMenu = 0;
HINSTANCE hInst;
MainLayout *Layout;
int MouseMenuPositionX,MouseMenuPositionY;
int InspectLastX = -1;
int InspectLastY = -1;
std::string LastLabel;
settings Settings;
int TimerLoop = 0;

void check_pid()
{
    while(true)
    {
        if(!isRunning(pid))
        {
            exit(0);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    }
}

void RepositionInterface(int x, int y)
{
    if(x>0 && y>0)
    {
        app->GetData()->WidthBrowser = x;
        app->GetData()->HeightBrowser = y;
    }
    Layout->Update(app->GetData()->WidthBrowser,app->GetData()->HeightBrowser,app->GetData()->WidthAll,app->GetData()->HeightAll);
}

void RestoreOriginalStage()
{
    Layout->DevToolsRectWidth = 500;
    Layout->ToolBoxRectHeight = 300;
    Layout->Update(app->GetData()->WidthBrowser,app->GetData()->HeightBrowser,app->GetData()->WidthAll,app->GetData()->HeightAll);
    InvalidateRect(Layout->MainWindowHandle,NULL,true);

    Settings.SetToolboxHeight(Layout->ToolBoxRectHeight);
    Settings.SetScenarioWidth(Layout->DevToolsRectWidth);
    Settings.SaveToFile();
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
        {
            Layout->hcSizeNS = LoadCursor(NULL, IDC_SIZENS);
            Layout->hcSizeEW = LoadCursor(NULL, IDC_SIZEWE);
            Layout->hcArrow = LoadCursor(NULL, IDC_ARROW);

            HICON hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_LOGO));
            SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);

            BReady = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCEW(IDB_READY), IMAGE_BITMAP, 0, 0, 0);
            Layout->BHold = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCEW(IDB_HOLD), IMAGE_BITMAP, 0, 0, 0);
            Layout->BHold90 = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCEW(IDB_HOLD90), IMAGE_BITMAP, 0, 0, 0);
            BFinished = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCEW(IDB_FINISHED), IMAGE_BITMAP, 0, 0, 0);
            HButtonUp = CreateWindow(L"BUTTON", NULL, BS_BITMAP|WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON, 0, 0, 20, 20, hwnd, (HMENU)IDButtonUp, hInst, NULL);
            Layout->HButtonUp = HButtonUp;
            {
                HBITMAP bitmap = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCEW(IDB_UP), IMAGE_BITMAP, 0, 0, 0);
                SendMessage(HButtonUp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)bitmap);
            }
            HButtonDown = CreateWindow(L"BUTTON", NULL, BS_BITMAP|WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON, 0,0 , 20, 20, hwnd, (HMENU)IDButtonDown, hInst, NULL);
            Layout->HButtonDown = HButtonDown;
            {
                HBITMAP bitmap = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCEW(IDB_DOWN), IMAGE_BITMAP, 0, 0, 0);
                SendMessage(HButtonDown, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)bitmap);
            }
            HButtonLeft = CreateWindow(L"BUTTON", NULL, BS_BITMAP|WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON, 0,0 , 20, 20, hwnd, (HMENU)IDButtonLeft, hInst, NULL);
            Layout->HButtonLeft = HButtonLeft;
            {
                HBITMAP bitmap = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCEW(IDB_LEFT), IMAGE_BITMAP, 0, 0, 0);
                SendMessage(HButtonLeft, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)bitmap);
            }
            HButtonRight = CreateWindow(L"BUTTON", NULL, BS_BITMAP|WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON, 0,0 , 20, 20, hwnd, (HMENU)IDButtonRight, hInst, NULL);
            Layout->HButtonRight = HButtonRight;
            {
                HBITMAP bitmap = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCEW(IDB_RIGHT), IMAGE_BITMAP, 0, 0, 0);
                SendMessage(HButtonRight, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)bitmap);
            }

            HButtonUpUp = CreateWindow(L"BUTTON", NULL, BS_BITMAP|WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON, 0, 0, 20, 20, hwnd, (HMENU)IDButtonUpUp, hInst, NULL);
            Layout->HButtonUpUp = HButtonUpUp;
            {
                HBITMAP bitmap = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCEW(IDB_UPUP), IMAGE_BITMAP, 0, 0, 0);
                SendMessage(HButtonUpUp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)bitmap);
            }
            HButtonDownDown = CreateWindow(L"BUTTON", NULL, BS_BITMAP|WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON, 0,0 , 20, 20, hwnd, (HMENU)IDButtonDownDown, hInst, NULL);
            Layout->HButtonDownDown = HButtonDownDown;
            {
                HBITMAP bitmap = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCEW(IDB_DOWNDOWN), IMAGE_BITMAP, 0, 0, 0);
                SendMessage(HButtonDownDown, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)bitmap);
            }
            HButtonLeftLeft = CreateWindow(L"BUTTON", NULL, BS_BITMAP|WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON, 0,0 , 20, 20, hwnd, (HMENU)IDButtonLeftLeft, hInst, NULL);
            Layout->HButtonLeftLeft = HButtonLeftLeft;
            {
                HBITMAP bitmap = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCEW(IDB_LEFTLEFT), IMAGE_BITMAP, 0, 0, 0);
                SendMessage(HButtonLeftLeft, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)bitmap);
            }
            HButtonRightRight = CreateWindow(L"BUTTON", NULL, BS_BITMAP|WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON, 0,0 , 20, 20, hwnd, (HMENU)IDButtonRightRight, hInst, NULL);
            Layout->HButtonRightRight = HButtonRightRight;
            {
                HBITMAP bitmap = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCEW(IDB_RIGHTRIGHT), IMAGE_BITMAP, 0, 0, 0);
                SendMessage(HButtonRightRight, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)bitmap);
            }


            HButtonDevTools = CreateWindow(L"BUTTON", NULL, BS_BITMAP|WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON, 0,0, 20, 20, hwnd, (HMENU)IDButtonDevTools, hInst, NULL);
            Layout->HButtonDevTools = HButtonDevTools;
            {
                Layout->ButtonDevToolsBitmap = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCEW(IDB_DEVTOOLS), IMAGE_BITMAP, 0, 0, 0);
                Layout->ButtonDevToolsBitmapGray = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCEW(IDB_DEVTOOLSGRAY), IMAGE_BITMAP, 0, 0, 0);
            }
            HButtonScenario = CreateWindow(L"BUTTON", NULL, BS_BITMAP|WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON, 0,0, 20, 20, hwnd, (HMENU)IDButtonScenario, hInst, NULL);
            Layout->HButtonScenario = HButtonScenario;
            {
                Layout->ButtonScenarioBitmap = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCEW(IDB_SCENARIO), IMAGE_BITMAP, 0, 0, 0);
                Layout->ButtonScenarioBitmapGray = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCEW(IDB_SCENARIOGRAY), IMAGE_BITMAP, 0, 0, 0);
            }

            Layout->HButtonSettings = CreateWindow(L"BUTTON", NULL, BS_BITMAP|WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON, 0,0, 20, 20, hwnd, (HMENU)IDButtonSettings, hInst, NULL);
            {
                HBITMAP bitmap = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCEW(IDB_SETTINGS), IMAGE_BITMAP, 0, 0, 0);
                SendMessage(Layout->HButtonSettings, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)bitmap);
            }

            Layout->ButtonMinimize = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCEW(IDB_MINIMIZE), IMAGE_BITMAP, 0, 0, 0);
            Layout->ButtonMaximize = (HBITMAP)LoadImage(hInst, MAKEINTRESOURCEW(IDB_MAXIMIZE), IMAGE_BITMAP, 0, 0, 0);
            Layout->HButtonMinimizeMaximize = CreateWindow(L"BUTTON", NULL, BS_BITMAP|WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON, 0,0, 20, 20, hwnd, (HMENU)IDButtonMinimizeMaximize, hInst, NULL);


            HCursor = LoadCursor(NULL, IDC_ARROW);

            HTextHold = CreateWindow(L"STATIC", L"Command is executing", WS_CHILD | WS_VISIBLE | SS_RIGHT, 0, 0, 100, 30, hwnd, (HMENU)IDTextHold, hInst, NULL);
            Layout->HTextHold = HTextHold;
            HTextFinished = CreateWindow(L"STATIC", L"Script is finished", WS_CHILD | WS_VISIBLE | SS_RIGHT, 0, 0, 100, 30, hwnd, (HMENU)IDTextFinished, hInst, NULL);
            Layout->HTextFinished = HTextFinished;

            RepositionInterface(0,0);
        }
        break;
        case WM_CTLCOLORSTATIC:
        {
            HDC hdcStatic = (HDC) wParam;
            SetBkColor(hdcStatic, RGB(255,255,255));
        }
        break;
        case WM_LBUTTONUP:
        {
            bool IsImageSelect = Layout->GetIsImageSelect();
            std::string imagedata;
            if(IsImageSelect)
            {
                RECT r = Layout->GetBrowserRectangle(app->GetData()->WidthBrowser,app->GetData()->HeightBrowser,app->GetData()->WidthAll,app->GetData()->HeightAll);

                float kx = (float)(app->GetData()->WidthBrowser) / (float)(r.right - r.left);
                float ky = (float)(app->GetData()->HeightBrowser) / (float)(r.bottom - r.top);
                imagedata = app->GetSubImageDataBase64(Layout->ImageSelectStartX * kx,Layout->ImageSelectStartY*ky,Layout->ImageSelectEndX * kx,Layout->ImageSelectEndY*ky);
            }



            if(Layout->OnMouseUp())
            {
                Layout->Update(app->GetData()->WidthBrowser,app->GetData()->HeightBrowser,app->GetData()->WidthAll,app->GetData()->HeightAll);
                Settings.SetToolboxHeight(Layout->ToolBoxRectHeight);
                Settings.SetScenarioWidth(Layout->DevToolsRectWidth);
                Settings.SaveToFile();
            }

            if(!Layout->IsToolboxMaximized && !Layout->IsCentralShown)
            {
                int xPos = LOWORD(lParam);
                int yPos = HIWORD(lParam);
                RECT r = Layout->GetBrowserRectangle(app->GetData()->WidthBrowser,app->GetData()->HeightBrowser,app->GetData()->WidthAll,app->GetData()->HeightAll);

                if(hPopupMenu)
                {
                    DestroyMenu(hPopupMenu);
                    hPopupMenu = 0;
                }
                if(hForEachMenu)
                {
                    DestroyMenu(hForEachMenu);
                    hForEachMenu = 0;
                }
                if(hTabsMenu)
                {
                    DestroyMenu(hTabsMenu);
                    hTabsMenu = 0;
                }

                if(xPos >= r.left && xPos <= r.right && yPos >= r.top && yPos <= r.bottom && Layout->State == MainLayout::Ready)
                {
                    {
                        LOCK_BROWSER_DATA
                        app->GetData()->_Inspect.isimage = IsImageSelect;
                        app->GetData()->_Inspect.imagedata = imagedata;
                    }

                    POINT p;
                    GetCursorPos(&p);

                    hPopupMenu = CreatePopupMenu();
                    if(!IsImageSelect)
                        hForEachMenu = CreatePopupMenu();
                    hTabsMenu = CreatePopupMenu();
                    MouseMenuPositionX = (float)(xPos - r.left) * (float)(app->GetData()->WidthBrowser) / (float)(r.right - r.left),MouseMenuPositionY = (float)(yPos - r.top) * (float)(app->GetData()->HeightBrowser) / (float)(r.bottom - r.top);
                    InspectLastX = MouseMenuPositionX + app->GetData()->ScrollX;
                    InspectLastY = MouseMenuPositionY + app->GetData()->ScrollY;

                    MouseMenuPositionX += app->GetData()->ScrollX;
                    MouseMenuPositionY += app->GetData()->ScrollY;
                    std::string Position = std::string("(") + std::to_string(MouseMenuPositionX) + std::string(",") + std::to_string(MouseMenuPositionY) + std::string(")");
                    std::wstring Click = Translate::Tr(L"Click") + s2ws(std::string(" ") + Position);
                    std::wstring Move = Translate::Tr(L"Move") + s2ws(std::string(" ") + Position);
                    std::wstring Drag = Translate::Tr(L"Drag") + s2ws(std::string(" ") + Position);
                    std::wstring Drop = Translate::Tr(L"Drop") + s2ws(std::string(" ") + Position);
                    std::wstring MoveAndClick = Translate::Tr(L"Move And Click") + s2ws(std::string(" ") + Position);
                    if(!IsImageSelect)
                        InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING | MF_DISABLED, IDNone, Translate::Tr(L"Use drag to find by image").c_str());
                    else
                        InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING | MF_DISABLED, IDNone, Translate::Tr(L"Use click to find by selector").c_str());

                    if(!IsImageSelect)
                    {
                        InsertMenu(hPopupMenu, 1, MF_BYPOSITION | MF_STRING, IDMoveAndClick, MoveAndClick.c_str());
                        InsertMenu(hPopupMenu, 2, MF_BYPOSITION | MF_STRING, IDClick, Click.c_str());
                        InsertMenu(hPopupMenu, 3, MF_BYPOSITION | MF_STRING, IDMove, Move.c_str());
                        InsertMenu(hPopupMenu, 4, MF_BYPOSITION | MF_STRING, IDDrag, Drag.c_str());
                        InsertMenu(hPopupMenu, 5, MF_BYPOSITION | MF_STRING, IDDrop, Drop.c_str());
                        InsertMenu(hPopupMenu, 6, MF_SEPARATOR, 0, NULL);
                        InsertMenu(hPopupMenu, 7, MF_BYPOSITION | MF_STRING, IDInspect, Translate::Tr(L"Inspect").c_str());
                    }

                    InsertMenu(hPopupMenu, 8, MF_SEPARATOR, 0, NULL);
                    InsertMenu(hPopupMenu, 9, MF_POPUP | MF_STRING, (UINT_PTR)hTabsMenu, Translate::Tr(L"Tabs").c_str());
                    {
                        int iterator = 0;
                        int IdIterator = IDCustomPopups;

                        InsertMenu(hTabsMenu, iterator++, MF_BYPOSITION | MF_STRING, IdIterator++, Translate::Tr(L"Add New Tab").c_str());

                        bool first = true;

                        for(std::string url:app->GetAllPopupsUrls())
                        {
                            InsertMenu(hTabsMenu, iterator++, MF_SEPARATOR, 0, NULL);
                            std::string miniurl = (url.length()>30) ? (url.substr(0,26) + " ...") : url;
                            InsertMenu(hTabsMenu, iterator++, MF_BYPOSITION | MF_STRING, IdIterator++, (Translate::Tr(L"Select Tab (") + s2ws(miniurl) + L")").c_str());
                            if(!first)
                            {
                                InsertMenu(hTabsMenu, iterator++, MF_BYPOSITION | MF_STRING, IdIterator++, (Translate::Tr(L"Remove Tab (") + s2ws(miniurl) + L")").c_str());
                            }
                            first = false;

                        }
                    }

                    InsertMenu(hPopupMenu, 10, MF_SEPARATOR, 0, NULL);
                    if(!IsImageSelect)
                    {
                        InsertMenu(hPopupMenu, 11, MF_BYPOSITION | MF_STRING, IDXml, Translate::Tr(L"Get Element Content").c_str());
                        InsertMenu(hPopupMenu, 12, MF_BYPOSITION | MF_STRING, IDText, Translate::Tr(L"Get Element Text").c_str());
                        InsertMenu(hPopupMenu, 13, MF_BYPOSITION | MF_STRING, IDScript, Translate::Tr(L"Execute Javascript On Element").c_str());
                    }
                    InsertMenu(hPopupMenu, 14, MF_BYPOSITION | MF_STRING, IDClickElement, Translate::Tr(L"Click On Element").c_str());
                    InsertMenu(hPopupMenu, 15, MF_BYPOSITION | MF_STRING, IDMoveElement, Translate::Tr(L"Move On Element").c_str());
                    InsertMenu(hPopupMenu, 16, MF_BYPOSITION | MF_STRING, IDMoveAndClickElement, Translate::Tr(L"Move And Click On Element").c_str());
                    InsertMenu(hPopupMenu, 17, MF_BYPOSITION | MF_STRING, IDDragElement, Translate::Tr(L"Drag On Element").c_str());
                    InsertMenu(hPopupMenu, 18, MF_BYPOSITION | MF_STRING, IDDropElement, Translate::Tr(L"Drop On Element").c_str());
                    InsertMenu(hPopupMenu, 19, MF_BYPOSITION | MF_STRING, IDClear, Translate::Tr(L"Clear Edit").c_str());
                    InsertMenu(hPopupMenu, 20, MF_BYPOSITION | MF_STRING, IDType, Translate::Tr(L"Type Text").c_str());
                    InsertMenu(hPopupMenu, 21, MF_BYPOSITION | MF_STRING, IDExists, Translate::Tr(L"Is Element Exists").c_str());
                    if(!IsImageSelect)
                    {
                        InsertMenu(hPopupMenu, 22, MF_BYPOSITION | MF_STRING, IDStyle, Translate::Tr(L"Get Element Style").c_str());
                    }
                    InsertMenu(hPopupMenu, 23, MF_BYPOSITION | MF_STRING, IDWaitElement, Translate::Tr(L"Wait While Element Exists").c_str());
                    if(!IsImageSelect)
                    {
                        InsertMenu(hPopupMenu, 24, MF_BYPOSITION | MF_STRING, IDScreenshot, Translate::Tr(L"Screenshot").c_str());
                        InsertMenu(hPopupMenu, 25, MF_BYPOSITION | MF_STRING, IDFocus, Translate::Tr(L"Scroll To Element").c_str());
                    }
                    InsertMenu(hPopupMenu, 26, MF_BYPOSITION | MF_STRING, IDCoordinates, Translate::Tr(L"Get Coordinates").c_str());
                    if(!IsImageSelect)
                    {
                        InsertMenu(hPopupMenu, 27, MF_BYPOSITION | MF_STRING, IDSet, Translate::Tr(L"Set Combobox Value").c_str());
                        InsertMenu(hPopupMenu, 28, MF_BYPOSITION | MF_STRING, IDSetInteger, Translate::Tr(L"Set Combobox Index").c_str());
                        InsertMenu(hPopupMenu, 29, MF_BYPOSITION | MF_STRING, IDSetRandom, Translate::Tr(L"Set Combobox To Random").c_str());
                        InsertMenu(hPopupMenu, 30, MF_BYPOSITION | MF_STRING, IDGetAttr, Translate::Tr(L"Get Element Attribute").c_str());
                        InsertMenu(hPopupMenu, 31, MF_BYPOSITION | MF_STRING, IDSetAttr, Translate::Tr(L"Set Element Attribute").c_str());
                        InsertMenu(hPopupMenu, 32, MF_BYPOSITION | MF_STRING, IDCaptcha, Translate::Tr(L"Solve Captcha").c_str());
                        InsertMenu(hPopupMenu, 33, MF_BYPOSITION | MF_STRING, IDLength, Translate::Tr(L"Get Element Count").c_str());

                        int iterator = 34;
                        int IdIterator = IDCustom;
                        for(ModulesData Module:app->GetData()->_ModulesData)
                        {
                            for(ActionData Action:Module->Actions)
                            {
                                if(Action->IsElement)
                                {
                                    IdIterator++;
                                    InsertMenu(hPopupMenu, iterator++, MF_BYPOSITION | MF_STRING, IdIterator, s2ws(Action->Description).c_str());
                                }
                            }
                        }

                        InsertMenu(hPopupMenu, iterator, MF_POPUP | MF_STRING, (UINT_PTR)hForEachMenu, Translate::Tr(L"For Each Element").c_str());


                        InsertMenu(hForEachMenu, 25, MF_BYPOSITION | MF_STRING, IDLoop, Translate::Tr(L"Start Loop").c_str());
                        InsertMenu(hForEachMenu, 26, MF_SEPARATOR, 0, NULL);
                        InsertMenu(hForEachMenu, 27, MF_BYPOSITION | MF_STRING, IDXmlLoop, Translate::Tr(L"Get Element Content").c_str());
                        InsertMenu(hForEachMenu, 28, MF_BYPOSITION | MF_STRING, IDTextLoop, Translate::Tr(L"Get Element Text").c_str());
                        InsertMenu(hForEachMenu, 29, MF_BYPOSITION | MF_STRING, IDScriptLoop, Translate::Tr(L"Execute Javascript On Element").c_str());
                        InsertMenu(hForEachMenu, 30, MF_BYPOSITION | MF_STRING, IDClickElementLoop, Translate::Tr(L"Click On Element").c_str());
                        InsertMenu(hForEachMenu, 31, MF_BYPOSITION | MF_STRING, IDMoveElementLoop, Translate::Tr(L"Move On Element").c_str());
                        InsertMenu(hForEachMenu, 32, MF_BYPOSITION | MF_STRING, IDMoveAndClickElementLoop, Translate::Tr(L"Move And Click On Element").c_str());
                        InsertMenu(hForEachMenu, 33, MF_BYPOSITION | MF_STRING, IDClearLoop, Translate::Tr(L"Clear Edit").c_str());
                        InsertMenu(hForEachMenu, 34, MF_BYPOSITION | MF_STRING, IDTypeLoop, Translate::Tr(L"Type Text").c_str());
                        InsertMenu(hForEachMenu, 35, MF_BYPOSITION | MF_STRING, IDExistsLoop, Translate::Tr(L"Is Element Exists").c_str());
                        InsertMenu(hForEachMenu, 36, MF_BYPOSITION | MF_STRING, IDStyleLoop, Translate::Tr(L"Get Element Style").c_str());
                        InsertMenu(hForEachMenu, 38, MF_BYPOSITION | MF_STRING, IDScreenshotLoop, Translate::Tr(L"Screenshot").c_str());
                        InsertMenu(hForEachMenu, 39, MF_BYPOSITION | MF_STRING, IDFocusLoop, Translate::Tr(L"Scroll To Element").c_str());
                        InsertMenu(hForEachMenu, 40, MF_BYPOSITION | MF_STRING, IDCoordinatesLoop, Translate::Tr(L"Get Coordinates").c_str());

                        InsertMenu(hForEachMenu, 41, MF_BYPOSITION | MF_STRING, IDSetLoop, Translate::Tr(L"Set Combobox Value").c_str());
                        InsertMenu(hForEachMenu, 42, MF_BYPOSITION | MF_STRING, IDSetIntegerLoop, Translate::Tr(L"Set Combobox Index").c_str());
                        InsertMenu(hForEachMenu, 43, MF_BYPOSITION | MF_STRING, IDSetRandomLoop, Translate::Tr(L"Set Combobox To Random").c_str());
                        InsertMenu(hForEachMenu, 44, MF_BYPOSITION | MF_STRING, IDGetAttrLoop, Translate::Tr(L"Get Element Attribute").c_str());
                        InsertMenu(hForEachMenu, 45, MF_BYPOSITION | MF_STRING, IDSetAttrLoop, Translate::Tr(L"Set Element Attribute").c_str());
                        InsertMenu(hForEachMenu, 46, MF_BYPOSITION | MF_STRING, IDCaptchaLoop, Translate::Tr(L"Solve Captcha").c_str());

                        iterator = 46;
                        IdIterator = IDCustomForeach;
                        for(ModulesData Module:app->GetData()->_ModulesData)
                        {
                            for(ActionData Action:Module->Actions)
                            {
                                if(Action->IsElement)
                                {
                                    IdIterator++;
                                    InsertMenu(hForEachMenu, iterator++, MF_BYPOSITION | MF_STRING, IdIterator, s2ws(Action->Description).c_str());
                                }
                            }
                        }
                    }

                    TrackPopupMenu(hPopupMenu, TPM_TOPALIGN | TPM_LEFTALIGN, p.x, p.y, 0, hwnd, NULL);
                    hPopupMenu = 0;

                    app->MouseLeave();
                }
            }
        }
        break;

        case WM_MOUSEMOVE:
        {
            int xPos = LOWORD(lParam);
            int yPos = HIWORD(lParam);

            if(Layout->OnMouseMove(xPos,yPos,app->GetData()->WidthBrowser,app->GetData()->HeightBrowser,app->GetData()->WidthAll,app->GetData()->HeightAll))
            {
                Layout->Update(app->GetData()->WidthBrowser,app->GetData()->HeightBrowser,app->GetData()->WidthAll,app->GetData()->HeightAll);
                InvalidateRect(Layout->MainWindowHandle,NULL,true);
                Settings.SetToolboxHeight(Layout->ToolBoxRectHeight);
                Settings.SetScenarioWidth(Layout->DevToolsRectWidth);
                Settings.SaveToFile();
            }

            if(!Layout->IsToolboxMaximized && !Layout->IsCentralShown)
            {
                RECT r = Layout->GetBrowserRectangle(app->GetData()->WidthBrowser,app->GetData()->HeightBrowser,app->GetData()->WidthAll,app->GetData()->HeightAll);

                if(xPos >= r.left && xPos <= r.right && yPos >= r.top && yPos <= r.bottom && !hPopupMenu && Layout->State == MainLayout::Ready )
                {
                    int MousePositionX = (float)(xPos - r.left) * (float)(app->GetData()->WidthBrowser) / (float)(r.right - r.left),MousePositionY = (float)(yPos - r.top) * (float)(app->GetData()->HeightBrowser) / (float)(r.bottom - r.top);

                    app->MouseMoveAt(MousePositionX,MousePositionY);
                }else
                {
                    app->MouseLeave();
                }
            }
        }
        break;
        /*case WM_SETFOCUS:
        if(app->GetData()->IsRecord)
        {
            Client->Write("<MaximizeWindow></MaximizeWindow>");
        }
        break;*/
        case WM_LBUTTONDOWN:
        {
            int xPos = LOWORD(lParam);
            int yPos = HIWORD(lParam);
            if(Layout->OnMouseDown(xPos,yPos,app->GetData()->WidthBrowser,app->GetData()->HeightBrowser,app->GetData()->WidthAll,app->GetData()->HeightAll))
            {
                Layout->Update(app->GetData()->WidthBrowser,app->GetData()->HeightBrowser,app->GetData()->WidthAll,app->GetData()->HeightAll);
                Settings.SetToolboxHeight(Layout->ToolBoxRectHeight);
                Settings.SetScenarioWidth(Layout->DevToolsRectWidth);
                Settings.SaveToFile();
            }

        }
        break;
        case WM_CLOSE:
        {
            WORKER_LOG("Minimized");
            app->Hide();
            Client->Write("<Minimized>1</Minimized>");
        }
        break;
        case WM_DESTROY:
           //PostQuitMessage(0);
        break;
        case WM_SIZE:
        {
            RECT rect;
            GetClientRect(hwnd,&rect);
            app->GetData()->WidthAll = rect.right - rect.left;
            app->GetData()->HeightAll = rect.bottom - rect.top;
            Layout->Update(app->GetData()->WidthBrowser,app->GetData()->HeightBrowser,app->GetData()->WidthAll,app->GetData()->HeightAll);
        }
        break;
        case WM_COMMAND:
            WORKER_LOG(std::string("WM_COMMAND<<") + std::to_string((int)LOWORD(wParam)));
            {
                WORD Command = LOWORD(wParam);
                int IdIterator = IDCustom;
                int IdIteratorForeach = IDCustomForeach;
                for(ModulesData Module:app->GetData()->_ModulesData)
                {
                    for(ActionData Action:Module->Actions)
                    {
                        if(Action->IsElement)
                        {
                            IdIterator ++;
                            IdIteratorForeach ++;
                             if(Command == IdIteratorForeach)
                             {
                                 if(Layout->State == MainLayout::Ready)
                                 {
                                    app->ExecuteElementLoopFunction(Action->Name);
                                 }
                             }else if(Command == IdIterator)
                             {
                                 if(Layout->State == MainLayout::Ready)
                                 {
                                    app->ExecuteElementFunction(Action->Name);
                                 }
                             }
                        }
                    }
                }

                if(Command >= IDCustomPopups)
                {
                    int diff = Command - IDCustomPopups;

                    if(diff == 0)
                        app->AddTab();
                    else if(diff == 1)
                        app->SelectTab(0);
                    else
                    {
                        if(diff % 2 == 0)
                            app->SelectTab(diff / 2);
                        if(diff % 2 == 1)
                            app->CloseTab(diff / 2);
                    }
                }

                switch(Command)
                {
                    case IDButtonTerminate:
                        app->Terminate();
                        return 0;
                    break;
                    case IDButtonQuit:
                        app->Hide();
                        Client->Write("<Minimized>1</Minimized>");
                        return 0;
                    break;
                    case IDButtonUp:
                        app->ScrollUp();
                    break;
                    case IDButtonDown:
                        app->ScrollDown();
                    break;
                    case IDButtonRight:
                        app->ScrollRight();
                    break;
                    case IDButtonLeft:
                        app->ScrollLeft();
                    break;
                    case IDButtonUpUp:
                        app->ScrollUpUp();
                    break;
                    case IDButtonDownDown:
                        app->ScrollDownDown();
                    break;
                    case IDButtonRightRight:
                        app->ScrollRightRight();
                    break;
                    case IDButtonLeftLeft:
                        app->ScrollLeftLeft();
                    break;
                    case IDButtonMinimizeMaximize:
                        Layout->MinimizeOrMaximize(hwnd,app->GetData()->_ParentWindowHandle);
                        app->ForceUpdateWindowPositionWithParent();
                        Settings.SetMaximized(!Layout->IsMinimized);
                    break;
                    case IDButtonDevTools:
                        Layout->UpdateTabs(true);
                        app->ToggleDevTools();
                    break;
                    case IDButtonScenario:
                        Layout->UpdateTabs(false);
                    break;
                    case IDButtonSettings:
                        app->LoadSettingsPage();
                        {
                            LOCK_BROWSER_DATA
                            app->GetData()->_Inspect.label.clear();
                        }
                    break;
                    case IDClick:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->EmulateClick(MouseMenuPositionX,MouseMenuPositionY);
                            return 0;
                        }
                    break;
                    case IDMove:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->EmulateMove(MouseMenuPositionX,MouseMenuPositionY);
                            return 0;
                        }
                    break;
                    case IDDrag:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->EmulateDrag(MouseMenuPositionX,MouseMenuPositionY);
                            return 0;
                        }
                    break;
                    case IDDrop:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->EmulateDrop(MouseMenuPositionX,MouseMenuPositionY);
                            return 0;
                        }
                    break;
                    case IDMoveAndClick:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->EmulateMoveAndClick(MouseMenuPositionX,MouseMenuPositionY);
                            return 0;
                        }
                    break;
                    case IDInspect:
                        Layout->UpdateTabs(true);
                        if(InspectLastX >= 0 && InspectLastY >= 0)
                        {
                            app->InspectAt(MouseMenuPositionX - app->GetData()->ScrollX,MouseMenuPositionY - app->GetData()->ScrollY);
                            InspectLastX = -1;
                            InspectLastY = -1;
                        }
                    break;
                    case IDXml:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("GetXml");
                        }
                    break;
                    case IDText:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("GetText");
                        }
                    break;
                    case IDScript:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("ExecuteScript");
                        }
                    break;

                    case IDClickElement:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("ClickElement");
                        }
                    break;
                    case IDMoveElement:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("MoveElement");
                        }
                    break;
                    case IDDragElement:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("DragElement");
                        }
                    break;
                    case IDDropElement:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("DropElement");
                        }
                    break;
                    case IDMoveAndClickElement:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("MoveAndClickElement");
                        }
                    break;
                    case IDClear:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("Clear");
                        }
                    break;
                    case IDType:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("Type");
                        }
                    break;
                    case IDExists:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("Exists");
                        }
                    break;
                    case IDStyle:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("Style");
                        }
                    break;
                    case IDCheck:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("Check");
                        }
                    break;
                    case IDScreenshot:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("Screenshot");
                        }
                    break;
                    case IDCoordinates:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("GetCoordinates");
                        }
                    break;
                    case IDFocus:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("Focus");
                        }
                    break;
                    case IDSet:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("Set");
                        }
                    break;
                    case IDSetInteger:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("SetInteger");
                        }
                    break;
                    case IDSetRandom:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("SetRandom");
                        }
                    break;
                    case IDGetAttr:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("GetAttr");
                        }
                    break;
                    case IDSetAttr:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("SetAttr");
                        }
                    break;
                    case IDCaptcha:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("Captcha");
                        }
                    break;
                    case IDWaitElement:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("Wait");
                        }
                    break;
                    case IDLength:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("Length");
                        }
                    break;
                    case IDLoop:
                        if(Layout->State == MainLayout::Ready)
                        {
                            app->ExecuteElementFunction("LoopElement");
                        }
                    break;
                case IDXmlLoop:
                    if(Layout->State == MainLayout::Ready)
                    {
                        app->ExecuteElementLoopFunction("GetXml");
                    }
                break;
                case IDTextLoop:
                    if(Layout->State == MainLayout::Ready)
                    {
                        app->ExecuteElementLoopFunction("GetText");
                    }
                break;
                case IDScriptLoop:
                    if(Layout->State == MainLayout::Ready)
                    {
                        app->ExecuteElementLoopFunction("ExecuteScript");
                    }
                break;

                case IDClickElementLoop:
                    if(Layout->State == MainLayout::Ready)
                    {
                        app->ExecuteElementLoopFunction("ClickElement");
                    }
                break;
                case IDMoveElementLoop:
                    if(Layout->State == MainLayout::Ready)
                    {
                        app->ExecuteElementLoopFunction("MoveElement");
                    }
                break;
                case IDMoveAndClickElementLoop:
                    if(Layout->State == MainLayout::Ready)
                    {
                        app->ExecuteElementLoopFunction("MoveAndClickElement");
                    }
                break;
                case IDClearLoop:
                    if(Layout->State == MainLayout::Ready)
                    {
                        app->ExecuteElementLoopFunction("Clear");
                    }
                break;
                case IDTypeLoop:
                    if(Layout->State == MainLayout::Ready)
                    {
                        app->ExecuteElementLoopFunction("Type");
                    }
                break;
                case IDExistsLoop:
                    if(Layout->State == MainLayout::Ready)
                    {
                        app->ExecuteElementLoopFunction("Exists");
                    }
                break;
                case IDStyleLoop:
                    if(Layout->State == MainLayout::Ready)
                    {
                        app->ExecuteElementLoopFunction("Style");
                    }
                break;
                case IDCheckLoop:
                    if(Layout->State == MainLayout::Ready)
                    {
                        app->ExecuteElementLoopFunction("Check");
                    }
                break;
                case IDFocusLoop:
                    if(Layout->State == MainLayout::Ready)
                    {
                        app->ExecuteElementLoopFunction("Focus");
                    }
                break;
                case IDSetLoop:
                    if(Layout->State == MainLayout::Ready)
                    {
                        app->ExecuteElementLoopFunction("Set");
                    }
                break;
                case IDSetIntegerLoop:
                    if(Layout->State == MainLayout::Ready)
                    {
                        app->ExecuteElementLoopFunction("SetInteger");
                    }
                break;
                case IDSetRandomLoop:
                    if(Layout->State == MainLayout::Ready)
                    {
                        app->ExecuteElementLoopFunction("SetRandom");
                    }
                break;
                case IDGetAttrLoop:
                    if(Layout->State == MainLayout::Ready)
                    {
                        app->ExecuteElementLoopFunction("GetAttr");
                    }
                break;
                case IDSetAttrLoop:
                    if(Layout->State == MainLayout::Ready)
                    {
                        app->ExecuteElementLoopFunction("SetAttr");
                    }
                break;
                case IDCaptchaLoop:
                    if(Layout->State == MainLayout::Ready)
                    {
                        app->ExecuteElementLoopFunction("Captcha");
                    }
                break;
                case IDScreenshotLoop:
                    if(Layout->State == MainLayout::Ready)
                    {
                        app->ExecuteElementLoopFunction("Screenshot");
                    }
                break;
                case IDCoordinatesLoop:
                    if(Layout->State == MainLayout::Ready)
                    {
                        app->ExecuteElementLoopFunction("GetCoordinates");
                    }
                break;




                }
            }
            SetFocus(NULL);
        break;
        case WM_TIMER:
            {
                if(!app->GetData()->IsRecord)
                {
                    TimerLoop++;
                    TimerLoop %= Settings.SkipFrames();
                    if(TimerLoop == 0)
                    {
                        CefDoMessageLoopWork();
                        app->CefMessageLoop();
                    }
                }else
                {
                    CefDoMessageLoopWork();
                    app->CefMessageLoop();
                }

                if(app->IsNeedQuit())
                    PostQuitMessage(0);
                std::string Xml = Client->Read();
                if(!Xml.empty())
                {
                    /*if(Xml.find("<Visible") == std::string::npos && Xml.find("<SetWindow") == std::string::npos)
                        app->ClearElementCommand();*/
                    Parser->Parse(Xml);
                }

                app->Timer();

                Layout->Timer(app->GetData()->WidthBrowser,app->GetData()->HeightBrowser,app->GetData()->WidthAll,app->GetData()->HeightAll);

            }
        break;
        case WM_PAINT:

            {
                if(!Layout->IsToolboxMaximized)
                {
                    PAINTSTRUCT ps;
                    HDC hdc = BeginPaint(hwnd, &ps);

                    RECT br = Layout->GetBrowserRectangle(app->GetData()->WidthBrowser,app->GetData()->HeightBrowser,app->GetData()->WidthAll,app->GetData()->HeightAll);

                    Layout->CustomDraw(hdc,app->GetData()->WidthBrowser,app->GetData()->HeightBrowser,app->GetData()->WidthAll,app->GetData()->HeightAll);
                    if(!Layout->SplitterIsChangingSize())
                    {

                        std::pair<int, int> size = app->GetImageSize();

                        if(size.first > 0 && size.second > 0 && !Layout->IsCentralShown)
                        {
                            char * data = app->GetImageData();

                            BITMAPINFO info;
                            ZeroMemory(&info, sizeof(BITMAPINFO));
                            info.bmiHeader.biBitCount = 32;
                            info.bmiHeader.biWidth = size.first;
                            info.bmiHeader.biHeight = size.second;
                            info.bmiHeader.biPlanes = 1;
                            info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
                            info.bmiHeader.biSizeImage = size.first * size.second * 4;
                            info.bmiHeader.biCompression = BI_RGB;

                            if(br.right > br.left && br.bottom > br.top)
                            {
                                if(!app->GetData()->IsRecord)
                                {
                                    StretchDIBits(hdc, br.left, br.bottom, br.right - br.left, br.top - br.bottom, 0, 0, size.first, size.second, data, &info, DIB_RGB_COLORS, SRCCOPY);
                                }else
                                {

                                    HDC hdcTemp = CreateCompatibleDC(hdc);
                                    HBITMAP hbmMem = CreateCompatibleBitmap(hdc, br.right - br.left, br.bottom - br.top);
                                    HANDLE hOld   = SelectObject(hdcTemp, hbmMem);

                                    StretchDIBits(hdcTemp, 0, br.bottom - br.top, br.right - br.left, br.top - br.bottom, 0, 0, size.first, size.second, data, &info, DIB_RGB_COLORS, SRCCOPY);

                                    {
                                        LOCK_BROWSER_DATA
                                        app->GetData()->_Highlight.Paint(hdcTemp,app->GetData()->WidthBrowser,app->GetData()->HeightBrowser,br.right - br.left,br.bottom - br.top,app->GetData()->ScrollX,app->GetData()->ScrollY,0,0,app->GetHighlightOffsetX(),app->GetHighlightOffsetY(),app->GetHighlightFrameId() >= 0);
                                    }

                                    bool ImageSelect = Layout->DrawImageSelect(hdcTemp);

                                    if(!hPopupMenu && !ImageSelect)
                                    {
                                        LOCK_BROWSER_DATA
                                        app->GetData()->_Inspect.Paint(hdcTemp,app->GetData()->WidthBrowser,app->GetData()->HeightBrowser,br.right - br.left,br.bottom - br.top,app->GetData()->ScrollX,app->GetData()->ScrollY,0,0);
                                    }

                                    BitBlt(hdc, br.left, br.top, br.right - br.left, br.bottom - br.top, hdcTemp, 0, 0, SRCCOPY);

                                    SelectObject(hdcTemp, hOld);
                                    DeleteObject(hbmMem);
                                    DeleteDC(hdcTemp);

                                }


                            }
                        }

                        if(app->GetData()->IsRecord)
                        {
                            RECT r = Layout->GetStateIndicatorRectangle(app->GetData()->WidthBrowser,app->GetData()->HeightBrowser,app->GetData()->WidthAll,app->GetData()->HeightAll);
                            BITMAP bitmap;
                            HBITMAP b;
                            switch(Layout->State)
                            {
                                case MainLayout::Ready: b = BReady; break;
                                case MainLayout::Hold: b = Layout->GetHoldAnimationButton(); break;
                                case MainLayout::Finished: b = BFinished; break;
                            }
                            HDC hdcMem = CreateCompatibleDC(hdc);
                            HGDIOBJ oldBitmap = SelectObject(hdcMem, b);
                            GetObject(b, sizeof(bitmap), &bitmap);
                            BitBlt(hdc, r.left, r.top, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
                            SelectObject(hdcMem, oldBitmap);
                            DeleteDC(hdcMem);
                        }

                        if(!Layout->IsCentralShown)
                        {
                            LOCK_BROWSER_DATA
                            BrowserData * d = app->GetData();
                            if(d->CursorX >= 0 && d->CursorX <= d->WidthBrowser && d->CursorY >= 0 && d->CursorY <= d->HeightBrowser)
                                DrawIcon(hdc, br.left + (float)(d->CursorX) * (float)(br.right - br.left) / (float)(d->WidthBrowser) , br.top + (float)(d->CursorY) * (float)(br.bottom - br.top) / (float)(d->HeightBrowser), HCursor);
                        }

                        if(!Layout->IsCentralShown)
                        {
                            std::string label;
                            {
                                LOCK_BROWSER_DATA
                                label = app->GetData()->_Inspect.label;
                            }


                            if(LastLabel != label)
                            {
                                RECT r = Layout->GetLabelRectangle(app->GetData()->WidthBrowser,app->GetData()->HeightBrowser,app->GetData()->WidthAll,app->GetData()->HeightAll);
                                std::string NewLabel = label;
                                std::wstring txt = s2ws(NewLabel);
                                FillRect(hdc,&r,(HBRUSH) (COLOR_WINDOW+1));
                                DrawText(hdc,txt.c_str(),txt.length(),&r,DT_VCENTER | DT_SINGLELINE);
                                LastLabel = NewLabel;
                            }
                        }

                    }



                    EndPaint(hwnd, &ps);
                }


                return DefWindowProc(hwnd, msg, wParam, lParam);
            }
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    #if defined(BAS_DEBUG)
        CCrashHandler ch;
        ch.SetProcessExceptionHandlers();
        ch.SetThreadExceptionHandlers();
    #else
        SetErrorMode(SetErrorMode(0) | SEM_NOGPFAULTERRORBOX);
    #endif

    std::srand(std::time(0));

    //Parse command line
    std::vector<std::wstring> Arguments;
    {
        int NumberArgs;
        LPWSTR *Arglist;
        Arglist = CommandLineToArgvW(GetCommandLineW(), &NumberArgs);
        for(int i = 0;i<NumberArgs;i++)
        {
            Arguments.push_back(Arglist[i]);
        }
        LocalFree(Arglist);
    }

    Settings.ParseCommandLine(Arguments);


    Layout = new MainLayout(Settings.ToolboxHeight(),Settings.ScenarioWidth());
    hInst = hInstance;

    CefMainArgs main_args(hInstance);
    app = new MainApp();
    app->SetSettings(&Settings);
    app->SetLayout(Layout);
    BrowserData * Data = new BrowserData();
    PostManager * _PostManager = new PostManager();

    {
        Data->IsRecord = Arguments.size() == 6;
        Layout->IsRecord = Data->IsRecord;
        worker_log_init(Data->IsRecord);
    }

    FontReplace::GetInstance().Initialize();

    WORKER_LOG(std::string("IsRecord<<") + std::to_string(Data->IsRecord));

    Data->OldestRequestTime = 0;
    Data->_MainWindowHandle = 0;
    Data->_ParentWindowHandle = 0;
    Data->CursorX = 0;
    Data->CursorY = 0;
    Data->ScrollX = 0;
    Data->ScrollY = 0;
    Data->_Inspect.active = false;
    Data->IsReset = false;
    Data->IsAboutBlankLoaded = false;
    Data->TimezoneSelected = false;
    Data->GeolocationSelected = false;
    Data->NeedClear = false;
    Data->IsDrag = false;
    Data->IsMousePress = false;
    Data->AllowPopups = true;
    Data->AllowDownloads = true;

    app->SetData(Data);
    app->SetPostManager(_PostManager);

    int exit_code = CefExecuteProcess(main_args, app.get(), NULL);

    if (exit_code >= 0)
      return exit_code;

    CefSettings settings;
    settings.no_sandbox = true;
    settings.ignore_certificate_errors = true;
    if(Data->IsRecord)
    {
        settings.log_severity = LOGSEVERITY_VERBOSE;
    }else
    {
        settings.log_severity = LOGSEVERITY_DISABLE;
    }
    settings.windowless_rendering_enabled = true;
    settings.multi_threaded_message_loop = false;
    settings.persist_user_preferences = 0;
    settings.persist_session_cookies = 0;


    Client = new PipesClient();
    Parser = new CommandParser();
    int NumberArgs = Arguments.size();
    std::string Lang = ws2s(Arguments[1]);

    Translate::SetLanguage(Lang);
    app->GetData()->_ModulesData = LoadModulesData(Lang);
    app->SetInitialStateCallback(Lang);

    std::string Key = ws2s(Arguments[2]);
    std::string Pid;
    if(NumberArgs>4)
    {
        Pid = ws2s(Arguments[4]);
        WORKER_LOG(std::string("Pid : ") + Pid);
        pid = std::stoi(Pid);
        new std::thread(check_pid);
    }
    WORKER_LOG(Key);
    Arguments.clear();

    Client->Start(Key,Pid);
    Layout->EventLoadNoDataPage.push_back(std::bind(&MainApp::LoadNoDataCallback,app.get()));
    Parser->EventLoad.push_back(std::bind(&MainApp::LoadCallback,app.get(),_1));
    Parser->EventVisible.push_back(std::bind(&MainApp::VisibleCallback,app.get(),_1));
    Parser->EventSetProxy.push_back(std::bind(&MainApp::SetProxyCallback,app.get(),_1,_2,_3,_4,_5,_6));
    Parser->EventAddHeader.push_back(std::bind(&MainApp::AddHeaderCallback,app.get(),_1,_2,_3));
    Parser->EventSetHeaderList.push_back(std::bind(&MainApp::SetHeaderListCallback,app.get(),_1));
    Parser->EventCleanHeader.push_back(std::bind(&MainApp::CleanHeaderCallback,app.get()));
    Parser->EventSetUserAgent.push_back(std::bind(&MainApp::SetUserAgentCallback,app.get(),_1));
    Parser->EventGetUrl.push_back(std::bind(&MainApp::GetUrlCallback,app.get()));
    Parser->EventResize.push_back(RepositionInterface);
    Parser->EventResize.push_back(std::bind(&MainApp::ResizeCallback,app.get(),_1,_2));
    Parser->EventTimezone.push_back(std::bind(&MainApp::TimezoneCallback,app.get(),_1));
    Parser->EventGeolocation.push_back(std::bind(&MainApp::GeolocationCallback,app.get(),_1,_2));
    Parser->EventSetWindow.push_back(std::bind(&MainApp::SetWindowCallback,app.get(),_1));
    Parser->EventHighlightAction.push_back(std::bind(&MainApp::HighlightActionCallback,app.get(),_1));
    Parser->EventMouseClick.push_back(std::bind(&MainApp::MouseClickCallback,app.get(),_1,_2));
    Parser->EventMouseClickUp.push_back(std::bind(&MainApp::MouseClickUpCallback,app.get(),_1,_2));
    Parser->EventMouseClickDown.push_back(std::bind(&MainApp::MouseClickDownCallback,app.get(),_1,_2));
    Parser->EventPopupClose.push_back(std::bind(&MainApp::PopupCloseCallback,app.get(),_1));
    Parser->EventPopupSelect.push_back(std::bind(&MainApp::PopupSelectCallback,app.get(),_1));
    Parser->EventMouseMove.push_back(std::bind(&MainApp::MouseMoveCallback,app.get(),_1,_2,_3,_4,_5));
    Parser->EventScroll.push_back(std::bind(&MainApp::ScrollCallback,app.get(),_1,_2));
    Parser->EventRender.push_back(std::bind(&MainApp::RenderCallback,app.get(),_1,_2,_3,_4));
    Parser->EventSetOpenFileName.push_back(std::bind(&MainApp::SetOpenFileNameCallback,app.get(),_1));
    Parser->EventSetStartupScript.push_back(std::bind(&MainApp::SetStartupScriptCallback,app.get(),_1,_2,_3));
    Parser->EventSendWorkerSettings.push_back(std::bind(&MainApp::SetWorkerSettingsCallback,app.get(),_1,_2,_3));

    Parser->EventSetPromptResult.push_back(std::bind(&MainApp::SetPromptResultCallback,app.get(),_1));
    Parser->EventSetHttpAuthResult.push_back(std::bind(&MainApp::SetHttpAuthResultCallback,app.get(),_1,_2));
    Parser->EventGetCookiesForUrl.push_back(std::bind(&MainApp::GetCookiesForUrlCallback,app.get(),_1));
    Parser->EventSaveCookies.push_back(std::bind(&MainApp::SaveCookiesCallback,app.get()));
    Parser->EventRestoreCookies.push_back(std::bind(&MainApp::RestoreCookiesCallback,app.get(),_1));
    Parser->EventRestoreLocalStorage.push_back(std::bind(&MainApp::RestoreLocalStorageCallback,app.get(),_1));
    Parser->EventWaitCode.push_back(std::bind(&MainApp::WaitCodeCallback,app.get()));
    Parser->EventStartSection.push_back(std::bind(&MainApp::StartSectionCallback,app.get(),_1));
    Parser->EventSetFontList.push_back(std::bind(&MainApp::SetFontListCallback,app.get(),_1));
    Parser->EventScriptFinished.push_back(std::bind(&MainApp::ScriptFinishedCallback,app.get()));
    Parser->EventSetCode.push_back(std::bind(&MainApp::SetCodeCallback,app.get(),_1,_2));
    Parser->EventSetResources.push_back(std::bind(&MainApp::SetResourceCallback,app.get(),_1));
    Parser->EventReset.push_back(std::bind(&MainApp::ResetCallback,app.get()));
    Parser->EventIsChanged.push_back(std::bind(&MainApp::IsChangedCallback,app.get()));
    Parser->EventSetNextAction.push_back(std::bind(&MainApp::SetNextActionCallback,app.get(),_1));
    Parser->EventCrush.push_back(std::bind(&MainApp::CrushCallback,app.get()));


    Parser->EventAddCacheMaskAllow.push_back(std::bind(&MainApp::AddCacheMaskAllowCallback,app.get(),_1));
    Parser->EventAddCacheMaskDeny.push_back(std::bind(&MainApp::AddCacheMaskDenyCallback,app.get(),_1));
    Parser->EventAddRequestMaskAllow.push_back(std::bind(&MainApp::AddRequestMaskAllowCallback,app.get(),_1));
    Parser->EventAddRequestMaskDeny.push_back(std::bind(&MainApp::AddRequestMaskDenyCallback,app.get(),_1));
    Parser->EventClearCacheMask.push_back(std::bind(&MainApp::ClearCacheMaskCallback,app.get()));
    Parser->EventClearRequestMask.push_back(std::bind(&MainApp::ClearRequestMaskCallback,app.get()));
    Parser->EventAllowPopups.push_back(std::bind(&MainApp::AllowPopups,app.get()));
    Parser->EventRestrictPopups.push_back(std::bind(&MainApp::RestrictPopups,app.get()));
    Parser->EventAllowDownloads.push_back(std::bind(&MainApp::AllowDownloads,app.get()));
    Parser->EventRestrictDownloads.push_back(std::bind(&MainApp::RestrictDownloads,app.get()));
    Parser->EventClearLoadedUrl.push_back(std::bind(&MainApp::ClearLoadedUrlCallback,app.get()));
    Parser->EventClearCachedData.push_back(std::bind(&MainApp::ClearCachedDataCallback,app.get()));
    Parser->EventClearAll.push_back(std::bind(&MainApp::ClearAllCallback,app.get()));
    Parser->EventClearMasks.push_back(std::bind(&MainApp::ClearMasksCallback,app.get()));
    Parser->EventClearData.push_back(std::bind(&MainApp::ClearDataCallback,app.get()));
    Parser->EventFindCacheByMaskBase64.push_back(std::bind(&MainApp::FindCacheByMaskBase64Callback,app.get(),_1));
    Parser->EventFindStatusByMask.push_back(std::bind(&MainApp::FindStatusByMaskCallback,app.get(),_1));
    Parser->EventFindCacheByMaskString.push_back(std::bind(&MainApp::FindCacheByMaskStringCallback,app.get(),_1));
    Parser->EventIsUrlLoadedByMask.push_back(std::bind(&MainApp::IsUrlLoadedByMaskCallback,app.get(),_1));
    Parser->EventGetLoadStats.push_back(std::bind(&MainApp::GetLoadStatsCallback,app.get()));
    Parser->EventElementCommand.push_back(std::bind(&MainApp::ElementCommandCallback,app.get(),_1));
    Parser->EventDebugVariablesResult.push_back(std::bind(&MainApp::DebugVariablesResultCallback,app.get(),_1));
    Parser->EventRestoreOriginalStage.push_back(RestoreOriginalStage);

    Parser->EventClearImageData.push_back(std::bind(&MainApp::ClearImageDataCallback,app.get()));
    Parser->EventSetImageData.push_back(std::bind(&MainApp::SetImageDataCallback,app.get(),_1));
    Parser->EventFindImage.push_back(std::bind(&MainApp::FindImageCallback,app.get()));

    app->EventSendTextResponce.push_back(std::bind(&PipesClient::Write,Client,_1));


    WORKER_LOG("Start Main Loop");

    WNDCLASSEX wc;
    MSG Msg;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = L"WorkerWindowClass";
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
        return 0;

    std::pair<int,int> BrowserSize = Layout->GetDefaultBrowserSize();
    std::pair<int,int> WindowSize = Layout->GetDefaultWindowSize();
    Data->WidthBrowser = BrowserSize.first;
    Data->HeightBrowser = BrowserSize.second;
    Data->WidthAll = WindowSize.first;
    Data->HeightAll = WindowSize.second;

    hwnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        L"WorkerWindowClass",
        L"about:blank",
        WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,
        //WS_POPUP,
        0, 0, Data->WidthAll, Data->HeightAll,
        NULL, NULL, hInstance, NULL);
    if(hwnd == NULL)
        return 0;

    Data->_MainWindowHandle = hwnd;
    Layout->MainWindowHandle = hwnd;

    SetTimer(hwnd, 0, 15, (TIMERPROC) NULL);

    ShowWindow(hwnd, SW_HIDE);
    UpdateWindow(hwnd);

    CefInitialize(main_args, settings, app.get(), NULL);

    thread_setup();

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    thread_cleanup();

    WORKER_LOG("End Main Loop");

    CefShutdown();

    WORKER_LOG("Exit");

    FontReplace::GetInstance().Uninitialize();

    return Msg.wParam;
}

