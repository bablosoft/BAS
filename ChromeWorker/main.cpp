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

int pid = -1;
CefRefPtr<MainApp> app;
PipesClient *Client;
CommandParser *Parser;
HWND MousePositionMouseHandle,hwnd,HButtonUp,HButtonDown,HButtonLeft,HButtonRight,HButtonDevTools,HButtonScenario,HTextHold,HTextFinished;
enum{IDButtonTerminate = 1000,IDButtonQuit,IDButtonUp,IDButtonDown,IDButtonLeft,IDButtonRight,IDButtonMinimizeMaximize,IDButtonDevTools,IDButtonScenario,IDButtonSettings,IDTextHold,IDTextFinished,IDClick,IDMove,IDMoveAndClick,IDInspect,IDXml,IDText,IDScript,IDClickElement,IDMoveElement,IDMoveAndClickElement,IDClear,IDType,IDExists,IDStyle,IDCheck,IDFocus,IDSet,IDSetInteger,IDSetRandom,IDGetAttr,IDSetAttr,IDCaptcha,IDLength,IDWaitElement,
    IDLoop,IDXmlLoop,IDTextLoop,IDScriptLoop,IDClickElementLoop,IDMoveElementLoop,IDMoveAndClickElementLoop,IDClearLoop,IDTypeLoop,IDExistsLoop,IDStyleLoop,IDCheckLoop,IDFocusLoop,IDSetLoop,IDSetIntegerLoop,IDSetRandomLoop,IDGetAttrLoop,IDSetAttrLoop,IDCaptchaLoop,IDCustom = 30000,IDCustomForeach = 40000};
HBITMAP BReady,BFinished;
HCURSOR HCursor;
using namespace std::placeholders;
HMENU hPopupMenu = 0;
HMENU hForEachMenu = 0;
HINSTANCE hInst;
MainLayout *Layout;
int MouseMenuPositionX,MouseMenuPositionY;
int InspectLastX = -1;
int InspectLastY = -1;
std::string LastLabel;
settings Settings;
int TimerLoop = 0;
int SkipFrames = 1;

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

void SetLang(std::string Lang, int)
{
    Translate::SetLanguage(Lang);
}

void LoadAllModules(std::string Lang, int)
{
    app->GetData()->_ModulesData = LoadModulesData(Lang);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
        {
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
        case WM_MOUSEMOVE:
        {
            if(!Layout->IsToolboxMaximized && !Layout->IsCentralShown)
            {
                int xPos = LOWORD(lParam);
                int yPos = HIWORD(lParam);
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
        case WM_LBUTTONDOWN:
        {
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

                if(xPos >= r.left && xPos <= r.right && yPos >= r.top && yPos <= r.bottom && Layout->State == MainLayout::Ready)
                {
                    POINT p;
                    GetCursorPos(&p);
                    hPopupMenu = CreatePopupMenu();
                    hForEachMenu = CreatePopupMenu();
                    MouseMenuPositionX = (float)(xPos - r.left) * (float)(app->GetData()->WidthBrowser) / (float)(r.right - r.left),MouseMenuPositionY = (float)(yPos - r.top) * (float)(app->GetData()->HeightBrowser) / (float)(r.bottom - r.top);
                    InspectLastX = MouseMenuPositionX + app->GetData()->ScrollX;
                    InspectLastY = MouseMenuPositionY + app->GetData()->ScrollY;

                    MouseMenuPositionX += app->GetData()->ScrollX;
                    MouseMenuPositionY += app->GetData()->ScrollY;
                    std::string Position = std::string("(") + std::to_string(MouseMenuPositionX) + std::string(",") + std::to_string(MouseMenuPositionY) + std::string(")");
                    std::wstring Click = Translate::Tr(L"Click") + s2ws(std::string(" ") + Position);
                    std::wstring Move = Translate::Tr(L"Move") + s2ws(std::string(" ") + Position);
                    std::wstring MoveAndClick = Translate::Tr(L"Move And Click") + s2ws(std::string(" ") + Position);
                    InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, IDMoveAndClick, MoveAndClick.c_str());
                    InsertMenu(hPopupMenu, 1, MF_BYPOSITION | MF_STRING, IDClick, Click.c_str());
                    InsertMenu(hPopupMenu, 2, MF_BYPOSITION | MF_STRING, IDMove, Move.c_str());
                    InsertMenu(hPopupMenu, 3, MF_SEPARATOR, 0, NULL);
                    InsertMenu(hPopupMenu, 4, MF_BYPOSITION | MF_STRING, IDInspect, Translate::Tr(L"Inspect").c_str());
                    InsertMenu(hPopupMenu, 5, MF_SEPARATOR, 0, NULL);
                    InsertMenu(hPopupMenu, 6, MF_BYPOSITION | MF_STRING, IDXml, Translate::Tr(L"Get Element Content").c_str());
                    InsertMenu(hPopupMenu, 7, MF_BYPOSITION | MF_STRING, IDText, Translate::Tr(L"Get Element Text").c_str());
                    InsertMenu(hPopupMenu, 8, MF_BYPOSITION | MF_STRING, IDScript, Translate::Tr(L"Execute Javascript On Element").c_str());
                    InsertMenu(hPopupMenu, 9, MF_BYPOSITION | MF_STRING, IDClickElement, Translate::Tr(L"Click On Element").c_str());
                    InsertMenu(hPopupMenu, 10, MF_BYPOSITION | MF_STRING, IDMoveElement, Translate::Tr(L"Move On Element").c_str());
                    InsertMenu(hPopupMenu, 11, MF_BYPOSITION | MF_STRING, IDMoveAndClickElement, Translate::Tr(L"Move And Click On Element").c_str());
                    InsertMenu(hPopupMenu, 12, MF_BYPOSITION | MF_STRING, IDClear, Translate::Tr(L"Clear Edit").c_str());
                    InsertMenu(hPopupMenu, 13, MF_BYPOSITION | MF_STRING, IDType, Translate::Tr(L"Type Text").c_str());
                    InsertMenu(hPopupMenu, 14, MF_BYPOSITION | MF_STRING, IDExists, Translate::Tr(L"Is Element Exists").c_str());
                    InsertMenu(hPopupMenu, 15, MF_BYPOSITION | MF_STRING, IDStyle, Translate::Tr(L"Get Element Style").c_str());
                    InsertMenu(hPopupMenu, 16, MF_BYPOSITION | MF_STRING, IDWaitElement, Translate::Tr(L"Wait While Element Exists").c_str());
                    InsertMenu(hPopupMenu, 17, MF_BYPOSITION | MF_STRING, IDCheck, Translate::Tr(L"Set Checkbox").c_str());
                    InsertMenu(hPopupMenu, 18, MF_BYPOSITION | MF_STRING, IDFocus, Translate::Tr(L"Scroll To Element").c_str());
                    InsertMenu(hPopupMenu, 19, MF_BYPOSITION | MF_STRING, IDSet, Translate::Tr(L"Set Combobox Value").c_str());
                    InsertMenu(hPopupMenu, 20, MF_BYPOSITION | MF_STRING, IDSetInteger, Translate::Tr(L"Set Combobox Index").c_str());
                    InsertMenu(hPopupMenu, 21, MF_BYPOSITION | MF_STRING, IDSetRandom, Translate::Tr(L"Set Combobox To Random").c_str());
                    InsertMenu(hPopupMenu, 22, MF_BYPOSITION | MF_STRING, IDGetAttr, Translate::Tr(L"Get Element Attribute").c_str());
                    InsertMenu(hPopupMenu, 23, MF_BYPOSITION | MF_STRING, IDSetAttr, Translate::Tr(L"Set Element Attribute").c_str());
                    InsertMenu(hPopupMenu, 24, MF_BYPOSITION | MF_STRING, IDCaptcha, Translate::Tr(L"Solve Captcha").c_str());
                    InsertMenu(hPopupMenu, 25, MF_BYPOSITION | MF_STRING, IDLength, Translate::Tr(L"Get Element Count").c_str());

                    int iterator = 26;
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
                    InsertMenu(hForEachMenu, 38, MF_BYPOSITION | MF_STRING, IDCheckLoop, Translate::Tr(L"Set Checkbox").c_str());
                    InsertMenu(hForEachMenu, 39, MF_BYPOSITION | MF_STRING, IDFocusLoop, Translate::Tr(L"Scroll To Element").c_str());
                    InsertMenu(hForEachMenu, 40, MF_BYPOSITION | MF_STRING, IDSetLoop, Translate::Tr(L"Set Combobox Value").c_str());
                    InsertMenu(hForEachMenu, 41, MF_BYPOSITION | MF_STRING, IDSetIntegerLoop, Translate::Tr(L"Set Combobox Index").c_str());
                    InsertMenu(hForEachMenu, 42, MF_BYPOSITION | MF_STRING, IDSetRandomLoop, Translate::Tr(L"Set Combobox To Random").c_str());
                    InsertMenu(hForEachMenu, 43, MF_BYPOSITION | MF_STRING, IDGetAttrLoop, Translate::Tr(L"Get Element Attribute").c_str());
                    InsertMenu(hForEachMenu, 44, MF_BYPOSITION | MF_STRING, IDSetAttrLoop, Translate::Tr(L"Set Element Attribute").c_str());
                    InsertMenu(hForEachMenu, 45, MF_BYPOSITION | MF_STRING, IDCaptchaLoop, Translate::Tr(L"Solve Captcha").c_str());

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

                    TrackPopupMenu(hPopupMenu, TPM_TOPALIGN | TPM_LEFTALIGN, p.x, p.y, 0, hwnd, NULL);
                    hPopupMenu = 0;
                    app->MouseLeave();
                }
            }
        }
        break;
        case WM_CLOSE:
        {
            worker_log("Minimized");
            app->Hide();
            Client->Write("<Messages><Minimized>1</Minimized></Messages>");
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
            worker_log(std::string("WM_COMMAND<<") + std::to_string((int)LOWORD(wParam)));
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

                switch(Command)
                {
                    case IDButtonTerminate:
                        app->Terminate();
                        return 0;
                    break;
                    case IDButtonQuit:
                        app->Hide();
                        Client->Write("<Messages><Minimized>1</Minimized></Messages>");
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




                }
            }
            SetFocus(NULL);
        break;
        case WM_TIMER:
            {
                if(!app->GetData()->IsRecord)
                {
                    TimerLoop++;
                    TimerLoop %= SkipFrames;
                    if(TimerLoop == 0)
                        CefDoMessageLoopWork();
                }else
                {
                    CefDoMessageLoopWork();
                }

                if(app->IsNeedQuit())
                    PostQuitMessage(0);
                std::string Xml = Client->Read();
                if(!Xml.empty())
                    Parser->Parse(Xml);

                app->Timer();

                Layout->Timer(app->GetData()->WidthBrowser,app->GetData()->HeightBrowser,app->GetData()->WidthAll,app->GetData()->HeightAll);

            }
        break;
        case WM_PAINT:
            {
                if(!Layout->IsToolboxMaximized)
                {
                    HDC hdc;
                    PAINTSTRUCT ps;
                    hdc = BeginPaint(hwnd, &ps);

                    RECT br = Layout->GetBrowserRectangle(app->GetData()->WidthBrowser,app->GetData()->HeightBrowser,app->GetData()->WidthAll,app->GetData()->HeightAll);

                    Layout->CustomDraw(hdc,app->GetData()->WidthBrowser,app->GetData()->HeightBrowser,app->GetData()->WidthAll,app->GetData()->HeightAll);

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
                            StretchDIBits(hdc, br.left, br.bottom, br.right - br.left, br.top - br.bottom, 0, 0, size.first, size.second, data, &info, DIB_RGB_COLORS, SRCCOPY);
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
                        if(d->CursorX >= d->ScrollX && d->CursorX <= d->ScrollX + d->WidthBrowser && d->CursorY >= d->ScrollY && d->CursorY <= d->ScrollY + d->HeightBrowser)
                            DrawIcon(hdc, br.left + (float)(d->CursorX - d->ScrollX) * (float)(br.right - br.left) / (float)(d->WidthBrowser) , br.top + (float)(d->CursorY - d->ScrollY) * (float)(br.bottom - br.top) / (float)(d->HeightBrowser), HCursor);
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

                    if(!hPopupMenu)
                    {
                        LOCK_BROWSER_DATA
                        app->GetData()->_Inspect.Paint(hdc,app->GetData()->WidthBrowser,app->GetData()->HeightBrowser,br.right - br.left,br.bottom - br.top,app->GetData()->ScrollX,app->GetData()->ScrollY,br.left,br.top);
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

    SetErrorMode(SetErrorMode(0) | SEM_NOGPFAULTERRORBOX);

    worker_log("------------------------Initialize-----------------------");
    std::srand(std::time(0));
    SkipFrames = Settings.SkipFrames();
    Layout = new MainLayout(Settings.ToolboxHeight(),Settings.ScenarioWidth());
    hInst = hInstance;

    CefMainArgs main_args(hInstance);
    app = new MainApp();
    app->SetSettings(&Settings);
    app->SetLayout(Layout);
    BrowserData * Data = new BrowserData();

    {
        LPWSTR *szArgList;
        int argCount;
        szArgList = CommandLineToArgvW(GetCommandLine(), &argCount);
        LocalFree(szArgList);
        Data->IsRecord = argCount == 5;
        Layout->IsRecord = Data->IsRecord;
        worker_log_init(Data->IsRecord);
    }

    worker_log(std::string("IsRecord<<") + std::to_string(Data->IsRecord));

    Data->OldestRequestTime = 0;
    Data->_MainWindowHandle = 0;
    Data->_ParentWindowHandle = 0;
    Data->CursorX = 0;
    Data->CursorY = 0;
    Data->_Inspect.active = false;
    Data->IsReset = false;
    Data->IsAboutBlankLoaded = false;

    app->SetData(Data);

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
    int NumberArgs;
    LPWSTR *Arglist;
    Arglist = CommandLineToArgvW(GetCommandLineW(), &NumberArgs);
    std::string Key = ws2s(Arglist[1]);
    std::string Pid;
    if(NumberArgs>3)
    {
        Pid = ws2s(Arglist[3]);
        worker_log(std::string("Pid : ") + Pid);
        pid = std::stoi(Pid);
        new std::thread(check_pid);
    }
    worker_log(Key);
    Client->Start(Key,Pid);
    Parser->EventLoad.push_back(std::bind(&MainApp::LoadCallback,app.get(),_1));
    Parser->EventVisible.push_back(std::bind(&MainApp::VisibleCallback,app.get(),_1));
    Parser->EventSetProxy.push_back(std::bind(&MainApp::SetProxyCallback,app.get(),_1,_2,_3,_4,_5));
    Parser->EventAddHeader.push_back(std::bind(&MainApp::AddHeaderCallback,app.get(),_1,_2));
    Parser->EventCleanHeader.push_back(std::bind(&MainApp::CleanHeaderCallback,app.get()));
    Parser->EventSetUserAgent.push_back(std::bind(&MainApp::SetUserAgentCallback,app.get(),_1));
    Parser->EventGetUrl.push_back(std::bind(&MainApp::GetUrlCallback,app.get()));
    Parser->EventResize.push_back(RepositionInterface);
    Parser->EventResize.push_back(std::bind(&MainApp::ResizeCallback,app.get(),_1,_2));
    Parser->EventSetWindow.push_back(std::bind(&MainApp::SetWindowCallback,app.get(),_1));
    Parser->EventMouseClick.push_back(std::bind(&MainApp::MouseClickCallback,app.get(),_1,_2));
    Parser->EventMouseMove.push_back(std::bind(&MainApp::MouseMoveCallback,app.get(),_1,_2));
    Parser->EventScroll.push_back(std::bind(&MainApp::ScrollCallback,app.get(),_1,_2));
    Parser->EventRender.push_back(std::bind(&MainApp::RenderCallback,app.get(),_1,_2,_3,_4));
    Parser->EventSetOpenFileName.push_back(std::bind(&MainApp::SetOpenFileNameCallback,app.get(),_1));
    Parser->EventSetPromptResult.push_back(std::bind(&MainApp::SetPromptResultCallback,app.get(),_1));
    Parser->EventSetHttpAuthResult.push_back(std::bind(&MainApp::SetHttpAuthResultCallback,app.get(),_1,_2));
    Parser->EventGetCookiesForUrl.push_back(std::bind(&MainApp::GetCookiesForUrlCallback,app.get(),_1));
    Parser->EventSaveCookies.push_back(std::bind(&MainApp::SaveCookiesCallback,app.get()));
    Parser->EventRestoreCookies.push_back(std::bind(&MainApp::RestoreCookiesCallback,app.get(),_1));
    Parser->EventWaitCode.push_back(std::bind(&MainApp::WaitCodeCallback,app.get()));
    Parser->EventStartSection.push_back(std::bind(&MainApp::StartSectionCallback,app.get(),_1));
    Parser->EventScriptFinished.push_back(std::bind(&MainApp::ScriptFinishedCallback,app.get()));
    Parser->EventSetCode.push_back(std::bind(&MainApp::SetCodeCallback,app.get(),_1));
    Parser->EventSetResources.push_back(std::bind(&MainApp::SetResourceCallback,app.get(),_1));
    Parser->EventReset.push_back(std::bind(&MainApp::ResetCallback,app.get()));
    Parser->EventIsChanged.push_back(std::bind(&MainApp::IsChangedCallback,app.get()));
    Parser->EventSetInitialState.push_back(std::bind(SetLang,_1,_2));
    Parser->EventSetInitialState.push_back(std::bind(LoadAllModules,_1,_2));
    Parser->EventSetInitialState.push_back(std::bind(&MainApp::SetInitialStateCallback,app.get(),_1,_2));


    Parser->EventAddCacheMaskAllow.push_back(std::bind(&MainApp::AddCacheMaskAllowCallback,app.get(),_1));
    Parser->EventAddCacheMaskDeny.push_back(std::bind(&MainApp::AddCacheMaskDenyCallback,app.get(),_1));
    Parser->EventAddRequestMaskAllow.push_back(std::bind(&MainApp::AddRequestMaskAllowCallback,app.get(),_1));
    Parser->EventAddRequestMaskDeny.push_back(std::bind(&MainApp::AddRequestMaskDenyCallback,app.get(),_1));
    Parser->EventClearCacheMask.push_back(std::bind(&MainApp::ClearCacheMaskCallback,app.get()));
    Parser->EventClearRequestMask.push_back(std::bind(&MainApp::ClearRequestMaskCallback,app.get()));
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


    app->EventSendTextResponce.push_back(std::bind(&PipesClient::Write,Client,_1));


    worker_log("Start Main Loop");

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

    worker_log("End Main Loop");

    CefShutdown();

    worker_log("Exit");

    return Msg.wParam;
}

