#include "highlightresult.h"
#include "log.h"


BOOL FillAlphaRect(HDC hdc, const RECT* lpcrect, HBRUSH brush, BYTE alpha)
{
    SIZE_T bmWidth = lpcrect->right - lpcrect->left;
    SIZE_T bmHeight = lpcrect->bottom - lpcrect->top;
    SIZE_T byteCount = bmWidth * bmHeight * 4;
    BITMAPINFO bmi;
    void* pvBits;

    ZeroMemory(&bmi, 0);
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = bmWidth;
    bmi.bmiHeader.biHeight = bmHeight;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage = byteCount;

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP memBM = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &pvBits, NULL, 0x0);
    HBITMAP oldBM = (HBITMAP)SelectObject(memDC, memBM);

    for (SIZE_T i = 0, size = bmWidth * bmHeight; i < size; ++i)
        ((UINT32*)pvBits)[i] = 0xff000000;

    SetBkMode(memDC, GetBkMode(hdc));
    SetBkColor(memDC, GetBkColor(hdc));
    HBRUSH oldBrush = (HBRUSH)SelectObject(memDC, brush);
    HPEN oldPen = (HPEN)SelectObject(memDC, GetStockObject(NULL_PEN));
    Rectangle(memDC, 0, 0, bmWidth, bmHeight);
    SelectObject(memDC, oldBrush);
    SelectObject(memDC, oldPen);

    for (SIZE_T i = 3; i < byteCount; i += 4)
            ((BYTE*)pvBits)[i] = 0xff - ((BYTE*)pvBits)[i];

    BLENDFUNCTION bf;
    bf.BlendOp = AC_SRC_OVER;
    bf.BlendFlags = 0;
    bf.SourceConstantAlpha = alpha;
    bf.AlphaFormat = AC_SRC_ALPHA;
    BOOL res = AlphaBlend(
        hdc,
        lpcrect->left,
        lpcrect->top,
        bmWidth,
        bmHeight,
        memDC,
        0,
        0,
        bmWidth,
        bmHeight,
        bf);

    SelectObject(memDC, oldBM);
    DeleteDC(memDC);
    DeleteObject(memBM);
    return res;
}


void HighlightResult::Paint(HDC hdc, int BrowserRealWidth, int BrowserRealHeight, int BrowserDrawWidth, int BrowserDrawHeight, int BrowserScrollX, int BrowserScrollY, int BrowserLeft, int BrowserTop, int FrameOffsetX, int FrameOffsetY, bool IsInsideFrame)
{

    for(rect& r: highlights)
    {
        int x = r.x + FrameOffsetX;
        int y = r.y + FrameOffsetY;
        if(IsInsideFrame)
        {
            x -= BrowserScrollX;
            y -= BrowserScrollY;
        }
        int x1 = (float)(x) * (float)BrowserDrawWidth / (float)BrowserRealWidth + 1
            ,y1 = (float)(y) * (float)BrowserDrawHeight / (float)BrowserRealHeight + 1
            ,width1 = (float)r.width* (float)BrowserDrawWidth / (float)BrowserRealWidth + 1
            ,height1 = (float)r.height* (float)BrowserDrawHeight / (float)BrowserRealHeight + 1;

        if(x1 + width1 <=0 || width1<=1)
        {
            continue;
        }

        if(x1<=0)
        {
           width1 += x1;
           x1 = 1;
        }

        if(y1 + height1 <=0 || height1<=1)
        {
            continue;
        }

        if(y1<=0)
        {
           height1 += y1;
           y1 = 1;
        }

        if(x1 >= BrowserDrawWidth)
        {
            continue;
        }

        if(x1 + width1 >= BrowserDrawWidth)
           width1 = BrowserDrawWidth - x1 - 1;

        if(y1 >= BrowserDrawHeight)
        {
            continue;
        }

        if(y1 + height1 >= BrowserDrawHeight)
           height1 = BrowserDrawHeight - y1 - 1;

        /*POINT pt;
        SelectObject(hdc, GetStockObject(DC_PEN));
        SetDCPenColor(hdc, RGB(0,153,204));

        MoveToEx(hdc, BrowserLeft + x1, BrowserTop + y1, &pt);
        LineTo(hdc, BrowserLeft + x1, BrowserTop + y1 + height1);

        MoveToEx(hdc, BrowserLeft + x1, BrowserTop + y1, &pt);
        LineTo(hdc, BrowserLeft + x1 + width1, BrowserTop + y1);

        MoveToEx(hdc, BrowserLeft + x1, BrowserTop + y1 + height1, &pt);
        LineTo(hdc, BrowserLeft + x1 + width1, BrowserTop + y1 + height1);

        MoveToEx(hdc, BrowserLeft + x1 + width1, BrowserTop + y1, &pt);
        LineTo(hdc, BrowserLeft + x1 + width1, BrowserTop + y1 + height1);*/

        RECT r;
        r.top = BrowserTop + y1;
        r.bottom = BrowserTop + y1 + height1;

        r.left = BrowserLeft + x1;
        r.right = BrowserLeft + x1 + width1;

        HBRUSH brush = CreateSolidBrush(RGB(0, 153, 204));

        FillAlphaRect(hdc,&r,brush,100);

        DeleteObject(brush);
    }

}
