#ifndef HIGHLIGHTRESULT_H
#define HIGHLIGHTRESULT_H

#include <vector>
#include <windows.h>


struct HighlightResult
{
    struct rect
    {
        int x;
        int y;
        int width;
        int height;
    };

    std::vector<rect> highlights;

    void Paint(HDC hdc, int BrowserRealWidth, int BrowserRealHeight, int BrowserDrawWidth, int BrowserDrawHeight, int BrowserScrollX, int BrowserScrollY, int BrowserLeft, int BrowserTop, int FrameOffsetX, int FrameOffsetY, bool IsInsideFrame);

};

#endif // HIGHLIGHTRESULT_H
