#include "browsereventsemulator.h"
#include <windows.h>
#include <bitset>
#include "converter.h"
#include "include/cef_app.h"
#include "log.h"
#include <math.h>



CefBrowserHost::DragOperationsMask allowedops;


KeyState::KeyState()
{
    Clear();
}

void KeyState::Clear()
{
    IsShift = false;
    IsAlt = false;
    IsCtrl = false;
}

bool KeyState::IsClear()
{
    return !IsShift && !IsAlt && !IsCtrl;
}

void BrowserEventsEmulator::StartDrag(CefRefPtr<CefBrowser> Browser, CefRefPtr<CefDragData> drag_data,CefBrowserHost::DragOperationsMask allowed_ops, int x, int y)
{
    CefMouseEvent e;
    e.modifiers = EVENTFLAG_LEFT_MOUSE_BUTTON;

    e.x = x;
    e.y = y;
    allowedops = allowed_ops;
    Browser->GetHost()->DragTargetDragEnter(drag_data,e,allowed_ops);
    Browser->GetHost()->DragTargetDragOver(e,allowedops);

}


BrowserEventsEmulator::BrowserEventsEmulator()
{

}

void BrowserEventsEmulator::SetFocus(CefRefPtr<CefBrowser> Browser)
{
    if(Browser)
        Browser->GetHost()->SendFocusEvent(true);
}

bool BrowserEventsEmulator::IsPointOnScreen(int PointX, int PointY, int ScrollX, int ScrollY, int BrowserWidth, int BrowserHeight)
{
    WORKER_LOG(
                std::string("IsPointOnScreen<<PointX") + std::to_string(PointX)
                + std::string("<<PointY") + std::to_string(PointY)
                + std::string("<<ScrollX") + std::to_string(ScrollX)
                + std::string("<<ScrollY") + std::to_string(ScrollY)
                +std::string("<<BrowserWidth") + std::to_string(BrowserWidth)
                + std::string("<<BrowserHeight") + std::to_string(BrowserHeight)
                );
    return PointX>=ScrollX && PointX<=ScrollX + BrowserWidth && PointY>=ScrollY && PointY<=ScrollY + BrowserHeight;
}

int random(int max)
{
    if(max <= 0)
        return 0;
    return rand() % (max);
}

void BrowserEventsEmulator::MouseMoveLine(CefRefPtr<CefBrowser> Browser, bool & IsMouseMoveSimulation, int MouseStartX, int MouseStartY, int MouseEndX, int MouseEndY , int& MouseCurrentX, int& MouseCurrentY, float Speed, int BrowserWidth, int BrowserHeight, bool IsMousePress, bool IsDrag)
{
    if(!IsMouseMoveSimulation)
        return;

    float DistanceSquareAll = (MouseStartX - MouseEndX) * (MouseStartX - MouseEndX) + (MouseStartY - MouseEndY) * (MouseStartY - MouseEndY);
    float DistanceSquareCurrent = (MouseStartX - MouseCurrentX) * (MouseStartX - MouseCurrentX) + (MouseStartY - MouseCurrentY) * (MouseStartY - MouseCurrentY);

    float DistanceAll = sqrtf(DistanceSquareAll);
    float DistanceCurrent = sqrtf(DistanceSquareCurrent);

    DistanceCurrent += (Speed * 15.0) / 100.0;

    if(DistanceCurrent >= DistanceAll)
    {
        IsMouseMoveSimulation = false;
        MouseCurrentX = MouseEndX;
        MouseCurrentY = MouseEndY;
        if(MouseCurrentX >= 0 && MouseCurrentX <= BrowserWidth && MouseCurrentY >= 0 && MouseCurrentY <= BrowserHeight)
        {
            CefMouseEvent e;
            if(IsMousePress)
                e.modifiers = EVENTFLAG_LEFT_MOUSE_BUTTON;

            e.x = MouseCurrentX;
            e.y = MouseCurrentY;

            Browser->GetHost()->SendMouseMoveEvent(e,false);
            if(IsDrag)
            {
                Browser->GetHost()->DragTargetDragOver(e,allowedops);
            }

        }
        return;
    }

    float k = DistanceCurrent / (DistanceAll - DistanceCurrent);

    MouseCurrentX = ((float)MouseStartX + k * (float)MouseEndX) / (1.0 + k);
    MouseCurrentY = ((float)MouseStartY + k * (float)MouseEndY) / (1.0 + k);


    if(MouseCurrentX >= 0 && MouseCurrentX <= BrowserWidth && MouseCurrentY >= 0 && MouseCurrentY <= BrowserHeight)
    {
        CefMouseEvent e;
        if(IsMousePress)
            e.modifiers = EVENTFLAG_LEFT_MOUSE_BUTTON;

        e.x = MouseCurrentX;
        e.y = MouseCurrentY;

        Browser->GetHost()->SendMouseMoveEvent(e,false);
        if(IsDrag)
        {
            Browser->GetHost()->DragTargetDragOver(e,allowedops);
        }

    }


}

void BrowserEventsEmulator::MouseMove(CefRefPtr<CefBrowser> Browser,
                                      bool & IsMouseMoveSimulation,
                                      int MouseStartX, int MouseStartY,
                                      int MouseEndX, int MouseEndY,
                                      int& MouseCurrentX, int& MouseCurrentY,
                                      float Speed,
                                      int BrowserWidth, int BrowserHeight,
                                      float Gravity, float Wind, float TargetArea,
                                      bool IsInit, bool IsDouble, bool IsMousePress, bool IsDrag)
{
    static float veloX,veloY,windX,windY,veloMag,dist,randomDist,lastDist,D;
    static int lastX,lastY,MSP,W,TDist;
    static int T;
    static float sqrt2,sqrt3,sqrt5,PDist,maxStep,dModA,dModB,nModA,nModB;

    if(IsInit)
    {
        veloX = 0;
        veloY = 0;
        windX = 0;
        windY = 0;
        veloMag = 0;
        dist = 0;
        randomDist = 0;
        lastDist = 0;
        D = 0;
        lastX = 0;
        lastY = 0;
        MSP = 0;
        W = 0;
        TDist = 0;
        T = 0;
        PDist = 0;
        maxStep = 0;

        MSP = 20;
        sqrt2 = sqrtf(2.0f);
        sqrt3 = sqrtf(3.0f);
        sqrt5 = sqrt(5.0f);

        TDist = hypot(MouseStartX-MouseEndX, MouseStartY-MouseEndY);
        if (TDist < 1)
            TDist = 1;

        dModA = 0.88;
        dModB = 0.95;

        if(TDist > 220)
        {
            nModA = 0.08;
            nModB = 0.04;
        }else
        {
            nModA = 0.20;
            nModB = 0.10;
        }
    }else
    {
        //WORKER_LOG(std::to_string(hypot(MouseCurrentX-MouseEndX, MouseCurrentY-MouseEndY)));

        //WORKER_LOG(std::to_string(MouseCurrentX-MouseEndX));
        //WORKER_LOG(std::to_string(MouseCurrentY-MouseEndY));

        if(hypot(MouseCurrentX-MouseEndX, MouseCurrentY-MouseEndY) <= 3)
        {
            IsMouseMoveSimulation = false;
            MouseCurrentX = MouseEndX;
            MouseCurrentY = MouseEndY;

            if(MouseCurrentX >= 0 && MouseCurrentX <= BrowserWidth && MouseCurrentY >= 0 && MouseCurrentY <= BrowserHeight)
            {
                CefMouseEvent e;
                if(IsMousePress)
                    e.modifiers = EVENTFLAG_LEFT_MOUSE_BUTTON;

                e.x = MouseCurrentX;
                e.y = MouseCurrentY;

                Browser->GetHost()->SendMouseMoveEvent(e,false);
                if(IsDrag)
                {
                    Browser->GetHost()->DragTargetDragOver(e,allowedops);
                }

            }
            return;
        }

        dist = hypot(MouseCurrentX-MouseEndX, MouseCurrentY-MouseEndY);

        if(Wind > dist)
            Wind = dist;

        if(dist < 1)
        {
            dist = 1;
        }

        PDist = dist/TDist;
        if (PDist < 0.01)
        {
            PDist = 0.01;
        }

        if(IsDouble)
        {
            if (PDist <= dModA)
            {
                D = (round((round(dist)*0.3))/5);
                if (D < ((TDist > 220) ? 20 : 3))
                    D = ((TDist > 220) ? 20 : 3);

            } else if (PDist > dModA)
            {
                if (PDist < dModB)
                {
                    D = 5 + rand() % 4;
                }else if (PDist >= dModB)
                {
                    D = 3 + rand() % 2;
                }
            }
        }

        if (PDist >= nModA)
        {
            D = (round((round(dist)*0.3))/5);
            if (D < ((TDist > 220) ? 15 : 3))
            {
                D = ((TDist > 220) ? 15 : 3);
            }
        }else if (PDist < nModA)
        {
            if (PDist >= nModB)
            {
                D = 5 + rand() % 4;
            }
            else if (PDist < nModB)
            {
                D = 3 + rand() % 2;
            }
        }

        D *= Speed/100.0;
        if(D<3)
            D = 5;

        if (D <= round(dist))
            maxStep = D;
        else
            maxStep = round(dist);

        //maxStep = 4;

        if(dist >= TargetArea)
        {
            windX = windX / sqrt3 + (random((int)round(Wind) * 2 + 1) - Wind) / sqrt5;
            windY = windY / sqrt3 + (random((int)round(Wind) * 2 + 1) - Wind) / sqrt5;
        }else
        {
            windX = windX / sqrt2;
            windY = windY / sqrt2;
        }

        veloX = veloX + windX;
        veloY = veloY + windY;
        veloX = veloX + Gravity * (MouseEndX - MouseCurrentX) / dist;
        veloY = veloY + Gravity * (MouseEndY - MouseCurrentY) / dist;

        if (hypot(veloX, veloY) > maxStep)
        {
            randomDist = maxStep / 2.0 + random((int)round(maxStep) / 2);
            veloMag = sqrtf(veloX * veloX + veloY * veloY);
            veloX = (veloX / veloMag) * randomDist;
            veloY = (veloY / veloMag) * randomDist;
        }

        lastX = round(MouseCurrentX);
        lastY = round(MouseCurrentY);
        MouseCurrentX += veloX;
        MouseCurrentY += veloY;

        if((lastX != round(MouseCurrentX)) || (lastY != round(MouseCurrentY)))
        {
            if(MouseCurrentX >= 0 && MouseCurrentX <= BrowserWidth && MouseCurrentY >= 0 && MouseCurrentY <= BrowserHeight)
            {
                CefMouseEvent e;
                if(IsMousePress)
                    e.modifiers = EVENTFLAG_LEFT_MOUSE_BUTTON;

                e.x = MouseCurrentX;
                e.y = MouseCurrentY;

                Browser->GetHost()->SendMouseMoveEvent(e,false);
                if(IsDrag)
                {
                    Browser->GetHost()->DragTargetDragOver(e,allowedops);
                }

            }
        }

        W = (random((int)round(100/MSP)))*6;
        if (W < 5)
        {
            W = 5;
        }

        if(IsDouble)
        {
            if (PDist > dModA)
                W = round(W*2.5);
        }else
        {
            W = round(W*1.2);
        }

        lastDist = dist;

    }

    /*if(!IsMouseMoveSimulation)
        return;

    float DistanceSquareAll = (MouseStartX - MouseEndX) * (MouseStartX - MouseEndX) + (MouseStartY - MouseEndY) * (MouseStartY - MouseEndY);
    float DistanceSquareCurrent = (MouseStartX - MouseCurrentX) * (MouseStartX - MouseCurrentX) + (MouseStartY - MouseCurrentY) * (MouseStartY - MouseCurrentY);

    float DistanceAll = sqrtf(DistanceSquareAll);
    float DistanceCurrent = sqrtf(DistanceSquareCurrent);

    DistanceCurrent += Speed;

    if(DistanceCurrent >= DistanceAll)
    {
        IsMouseMoveSimulation = false;
        MouseCurrentX = MouseEndX;
        MouseCurrentY = MouseEndY;
        return;
    }

    float k = DistanceCurrent / (DistanceAll - DistanceCurrent);

    MouseCurrentX = ((float)MouseStartX + k * (float)MouseEndX) / (1.0 + k);
    MouseCurrentY = ((float)MouseStartY + k * (float)MouseEndY) / (1.0 + k);


    if(MouseCurrentX >= 0 && MouseCurrentX <= BrowserWidth && MouseCurrentY >= 0 && MouseCurrentY <= BrowserHeight)
    {
        CefMouseEvent e;
        e.x = MouseCurrentX;
        e.y = MouseCurrentY;

        Browser->GetHost()->SendMouseMoveEvent(e,false);
    }*/


}

void BrowserEventsEmulator::MouseClick(CefRefPtr<CefBrowser> Browser, int x, int y, const std::pair<int,int> scroll, int type, bool& IsMousePress, bool& IsDrag)
{
    if(!Browser)
        return;

    CefMouseEvent event;
    event.modifiers = EVENTFLAG_LEFT_MOUSE_BUTTON;
    event.x = x - scroll.first;
    event.y = y - scroll.second;
    WORKER_LOG(std::string("BrowserEventsEmulator::MouseClick<<") + std::to_string(x) + std::string("<<") + std::to_string(y) + std::string("<<") + std::to_string(type));

    if(type == 2)
    {
        IsMousePress = true;
    }

    if(type == 1)
    {
        IsMousePress = false;
    }

    if(type == 1 && IsDrag)
    {
        Browser->GetHost()->DragTargetDragOver(event,allowedops);
        Browser->GetHost()->DragSourceEndedAt(event.x,event.y,allowedops);


        Browser->GetHost()->DragTargetDrop(event);
        Browser->GetHost()->DragSourceSystemDragEnded();
        IsDrag = false;
    }


    if(type != 1)
    {
        Browser->GetHost()->SendMouseClickEvent(event,MBT_LEFT,false,1);
        WORKER_LOG(std::string("BrowserEventsEmulator::MouseClickDown<<"));
    }

    if(type != 2)
    {
        Browser->GetHost()->SendMouseClickEvent(event,MBT_LEFT,true,1);
        WORKER_LOG(std::string("BrowserEventsEmulator::MouseClickUp<<"));
    }
}

void BrowserEventsEmulator::Key(CefRefPtr<CefBrowser> Browser, std::string & text, KeyState& State, int mousex, int mousey)
{
    if(!Browser)
        return;

    bool AdditionalIsShift = false;
    bool AdditionalIsAlt = false;
    bool AdditionalIsCtrl = false;

    std::string text_copy = text;
    while(true)
    {
        if(text_copy.rfind("<SHIFT>", 0) == 0)
        {
            AdditionalIsShift = true;
            text_copy.erase(text_copy.begin(),text_copy.begin() + 7);
            continue;
        }
        if(text_copy.rfind("<MENU>", 0) == 0)
        {
            AdditionalIsAlt = true;
            text_copy.erase(text_copy.begin(),text_copy.begin() + 5);
            continue;
        }
        if(text_copy.rfind("<CONTROL>", 0) == 0)
        {
            AdditionalIsCtrl = true;
            text_copy.erase(text_copy.begin(),text_copy.begin() + 9);
            continue;
        }
        break;
    }

    if(text_copy.empty() && State.IsClear())
        return;

    std::wstring text_whcar = s2ws(text_copy);
    if(text_whcar.empty() && State.IsClear())
        return;

    char key = -1;
    char state = -1;
    wchar_t letter_wchar;
    bool ismouse = false;
    bool ismouseup = false;
    bool is_special_letter = true;
    int character_length = 1;

    if(!text_whcar.empty())
    {
        std::wstring CANCEL = L"<CANCEL>";
        std::wstring BACK = L"<BACK>";
        std::wstring TAB = L"<TAB>";
        std::wstring CLEAR = L"<CLEAR>";
        std::wstring RETURN = L"<RETURN>";
        std::wstring CAPITAL = L"<CAPITAL>";
        std::wstring ESCAPE = L"<ESCAPE>";
        std::wstring PRIOR = L"<PRIOR>";
        std::wstring NEXT = L"<NEXT>";
        std::wstring END = L"<END>";
        std::wstring HOME = L"<HOME>";
        std::wstring LEFT = L"<LEFT>";
        std::wstring UP = L"<UP>";
        std::wstring RIGHT = L"<RIGHT>";
        std::wstring DOWN = L"<DOWN>";
        std::wstring SELECT = L"<SELECT>";
        std::wstring PRINT = L"<PRINT>";
        std::wstring EXECUTE = L"<EXECUTE>";
        std::wstring SNAPSHOT = L"<SNAPSHOT>";
        std::wstring INSERT = L"<INSERT>";
        std::wstring _DELETE = L"<DELETE>";
        std::wstring MOUSESCROLLUP = L"<MOUSESCROLLUP>";
        std::wstring MOUSESCROLLDOWN = L"<MOUSESCROLLDOWN>";

        if(text_whcar.rfind(MOUSESCROLLUP, 0) == 0)
        {
            character_length = MOUSESCROLLUP.length();
            ismouse = true;
            ismouseup = true;
        }else if(text_whcar.rfind(MOUSESCROLLDOWN, 0) == 0)
        {
            character_length = MOUSESCROLLDOWN.length();
            ismouse = true;
            ismouseup = false;
        }else if(text_whcar.rfind(CANCEL, 0) == 0)
        {
            character_length = CANCEL.length();
            letter_wchar = key = VK_CANCEL;
        }else if(text_whcar.rfind(BACK, 0) == 0)
        {
            character_length = BACK.length();
            letter_wchar = key = VK_BACK;
        }else if(text_whcar.rfind(TAB, 0) == 0)
        {
            character_length = TAB.length();
            letter_wchar = key = VK_TAB;
        }else if(text_whcar.rfind(CLEAR, 0) == 0)
        {
            character_length = CLEAR.length();
            letter_wchar = key = VK_CLEAR;
        }else if(text_whcar.rfind(RETURN, 0) == 0)
        {
            character_length = RETURN.length();
            letter_wchar = key = VK_RETURN;
            is_special_letter = false;
        }else if(text_whcar.rfind(CAPITAL, 0) == 0)
        {
            character_length = CAPITAL.length();
            letter_wchar = key = VK_CAPITAL;
        }else if(text_whcar.rfind(ESCAPE, 0) == 0)
        {
            character_length = ESCAPE.length();
            letter_wchar = key = VK_ESCAPE;
        }else if(text_whcar.rfind(PRIOR, 0) == 0)
        {
            character_length = PRIOR.length();
            letter_wchar = key = VK_PRIOR;
        }else if(text_whcar.rfind(NEXT, 0) == 0)
        {
            character_length = NEXT.length();
            letter_wchar = key = VK_NEXT;
        }else if(text_whcar.rfind(END, 0) == 0)
        {
            character_length = END.length();
            letter_wchar = key = VK_END;
        }else if(text_whcar.rfind(HOME, 0) == 0)
        {
            character_length = HOME.length();
            letter_wchar = key = VK_HOME;
        }else if(text_whcar.rfind(LEFT, 0) == 0)
        {
            character_length = LEFT.length();
            letter_wchar = key = VK_LEFT;
        }else if(text_whcar.rfind(UP, 0) == 0)
        {
            character_length = UP.length();
            letter_wchar = key = VK_UP;
        }else if(text_whcar.rfind(RIGHT, 0) == 0)
        {
            character_length = RIGHT.length();
            letter_wchar = key = VK_RIGHT;
        }else if(text_whcar.rfind(DOWN, 0) == 0)
        {
            character_length = DOWN.length();
            letter_wchar = key = VK_DOWN;
        }else if(text_whcar.rfind(SELECT, 0) == 0)
        {
            character_length = SELECT.length();
            letter_wchar = key = VK_SELECT;
        }else if(text_whcar.rfind(PRINT, 0) == 0)
        {
            character_length = PRINT.length();
            letter_wchar = key = VK_PRINT;
        }else if(text_whcar.rfind(EXECUTE, 0) == 0)
        {
            character_length = EXECUTE.length();
            letter_wchar = key = VK_EXECUTE;
        }else if(text_whcar.rfind(SNAPSHOT, 0) == 0)
        {
            character_length = SNAPSHOT.length();
            letter_wchar = key = VK_SNAPSHOT;
        }else if(text_whcar.rfind(INSERT, 0) == 0)
        {
            character_length = INSERT.length();
            letter_wchar = key = VK_INSERT;
        }else if(text_whcar.rfind(_DELETE, 0) == 0)
        {
            character_length = _DELETE.length();
            letter_wchar = key = VK_DELETE;
        }else
        {
            is_special_letter = false;
            letter_wchar = text_whcar.at(0);
            std::vector<HKL> Locales;
            int max_locales = 300;
            Locales.resize(max_locales);
            max_locales = GetKeyboardLayoutList(max_locales,Locales.data());

            int index = 0;
            while((key == -1 || state == -1) && index < max_locales)
            {
                short c = VkKeyScanEx(letter_wchar,Locales[index]);
                key = c & 0xFF;
                state = c >> 8;
                index ++;
            }
        }
    }

    bool IsShift = false;
    bool IsAlt = false;
    bool IsCtrl = false;

    if(state != -1)
    {
        IsShift = state&1;
        IsCtrl = state&2;
        IsAlt = state&4;
    }

    if(AdditionalIsShift)
        IsShift = true;

    if(AdditionalIsAlt)
        IsAlt = true;

    if(AdditionalIsCtrl)
        IsCtrl = true;

    if(!ismouse)
    {
        if(IsShift != State.IsShift)
        {
            State.IsShift = IsShift;
            CefKeyEvent event;
            event.type = (IsShift) ? KEYEVENT_KEYDOWN : KEYEVENT_KEYUP;
            event.modifiers = ((State.IsShift) ? EVENTFLAG_SHIFT_DOWN : EVENTFLAG_NONE)  | ((State.IsAlt) ? EVENTFLAG_ALT_DOWN : EVENTFLAG_NONE) | ((State.IsCtrl) ? EVENTFLAG_CONTROL_DOWN : EVENTFLAG_NONE);
            event.windows_key_code = VK_SHIFT;
            event.native_key_code = (IsShift) ? 1 : -1073741823;
            event.is_system_key = false;
            event.character = VK_SHIFT;
            event.unmodified_character = VK_SHIFT;
            event.focus_on_editable_field = true;
            Browser->GetHost()->SendKeyEvent(event);
            return;
        }

        if(IsAlt != State.IsAlt)
        {
            State.IsAlt = IsAlt;
            CefKeyEvent event;
            event.type = (IsAlt) ? KEYEVENT_KEYDOWN : KEYEVENT_KEYUP;
            event.modifiers = ((State.IsShift) ? EVENTFLAG_SHIFT_DOWN : EVENTFLAG_NONE)  | ((State.IsAlt) ? EVENTFLAG_ALT_DOWN : EVENTFLAG_NONE) | ((State.IsCtrl) ? EVENTFLAG_CONTROL_DOWN : EVENTFLAG_NONE);
            event.windows_key_code = VK_MENU;
            event.native_key_code = (IsAlt) ? 1 : -1073741823;
            event.is_system_key = false;
            event.character = VK_MENU;
            event.unmodified_character = VK_MENU;
            event.focus_on_editable_field = true;
            Browser->GetHost()->SendKeyEvent(event);
            return;
        }

        if(IsCtrl != State.IsCtrl)
        {
            State.IsCtrl = IsCtrl;
            CefKeyEvent event;
            event.type = (IsCtrl) ? KEYEVENT_KEYDOWN : KEYEVENT_KEYUP;
            event.modifiers = ((State.IsShift) ? EVENTFLAG_SHIFT_DOWN : EVENTFLAG_NONE)  | ((State.IsAlt) ? EVENTFLAG_ALT_DOWN : EVENTFLAG_NONE) | ((State.IsCtrl) ? EVENTFLAG_CONTROL_DOWN : EVENTFLAG_NONE);
            event.windows_key_code = VK_CONTROL;
            event.native_key_code = (IsCtrl) ? 1 : -1073741823;
            event.is_system_key = false;
            event.character = VK_CONTROL;
            event.unmodified_character = VK_CONTROL;
            event.focus_on_editable_field = true;
            Browser->GetHost()->SendKeyEvent(event);
            return;
        }

        //Main key down
        {
            CefKeyEvent event;
            event.type = KEYEVENT_KEYDOWN;
            event.modifiers = ((IsShift) ? EVENTFLAG_SHIFT_DOWN : EVENTFLAG_NONE)  | ((IsAlt) ? EVENTFLAG_ALT_DOWN : EVENTFLAG_NONE) | ((IsCtrl) ? EVENTFLAG_CONTROL_DOWN : EVENTFLAG_NONE);
            event.windows_key_code = key;
            event.native_key_code = 1;
            event.is_system_key = false;
            event.character = letter_wchar;
            event.unmodified_character = letter_wchar;
            event.focus_on_editable_field = true;
            Browser->GetHost()->SendKeyEvent(event);
        }
        //Main key press
        if(!is_special_letter)
        {
            CefKeyEvent event;
            event.type = KEYEVENT_CHAR;
            event.modifiers = ((IsShift) ? EVENTFLAG_SHIFT_DOWN : EVENTFLAG_NONE)  | ((IsAlt) ? EVENTFLAG_ALT_DOWN : EVENTFLAG_NONE) | ((IsCtrl) ? EVENTFLAG_CONTROL_DOWN : EVENTFLAG_NONE);
            event.windows_key_code = letter_wchar;
            event.native_key_code = 0;
            event.is_system_key = false;
            event.character = letter_wchar;
            event.unmodified_character = letter_wchar;
            event.focus_on_editable_field = true;
            Browser->GetHost()->SendKeyEvent(event);
        }
        //Main key up
        {
            CefKeyEvent event;
            event.type = KEYEVENT_KEYUP;
            event.modifiers = ((IsShift) ? EVENTFLAG_SHIFT_DOWN : EVENTFLAG_NONE)  | ((IsAlt) ? EVENTFLAG_ALT_DOWN : EVENTFLAG_NONE) | ((IsCtrl) ? EVENTFLAG_CONTROL_DOWN : EVENTFLAG_NONE);
            event.windows_key_code = key;
            event.native_key_code = -1073741823;
            event.is_system_key = false;
            event.character = letter_wchar;
            event.unmodified_character = letter_wchar;
            event.focus_on_editable_field = true;
            Browser->GetHost()->SendKeyEvent(event);
        }
    }
    else
    {
        CefMouseEvent e;
        e.x = mousex;
        e.y = mousey;
        int deltay = (ismouseup) ? 100 : -100;
        Browser->GetHost()->SendMouseWheelEvent(e,0,deltay);
    }

    text_whcar.erase(text_whcar.begin(),text_whcar.begin() + character_length);
    text = ws2s(text_whcar);
}

