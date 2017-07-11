#include "inspectresult.h"
#include "log.h"
#include "picojson.h"

void InspectResult::Paint(HDC hdc, int BrowserRealWidth, int BrowserRealHeight, int BrowserDrawWidth, int BrowserDrawHeight, int BrowserScrollX, int BrowserScrollY, int BrowserLeft, int BrowserTop)
{

    if(!active)
        return;

    POINT pt;
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, RGB(255,0,0));

    int     x1 = (float)x * (float)BrowserDrawWidth / (float)BrowserRealWidth
            ,y1 = (float)y * (float)BrowserDrawHeight / (float)BrowserRealHeight
            ,width1 = (float)width* (float)BrowserDrawWidth / (float)BrowserRealWidth
            ,height1 = (float)height* (float)BrowserDrawHeight / (float)BrowserRealHeight;

    if(x1<=0)
    {
       width1 += x1;
       x1 = 1;
    }

    if(y1<=0)
    {
       height1 += y1;
       y1 = 1;
    }

    if(x1 + width1 >= BrowserDrawWidth)
       width1 = BrowserDrawWidth - x1 - 1;

    if(y1 + height1 >= BrowserDrawHeight)
       height1 = BrowserDrawHeight - y1 - 1;

    //WORKER_LOG(std::string("Paint<<") + std::to_string(x1) + std::string("<<") + std::to_string(y1)+ std::string("<<") + std::to_string(width1)+ std::string("<<") + std::to_string(height1));

    MoveToEx(hdc, BrowserLeft + x1, BrowserTop + y1, &pt);
    LineTo(hdc, BrowserLeft + x1, BrowserTop + y1 + height1);

    MoveToEx(hdc, BrowserLeft + x1, BrowserTop + y1, &pt);
    LineTo(hdc, BrowserLeft + x1 + width1, BrowserTop + y1);

    MoveToEx(hdc, BrowserLeft + x1, BrowserTop + y1 + height1, &pt);
    LineTo(hdc, BrowserLeft + x1 + width1, BrowserTop + y1 + height1);

    MoveToEx(hdc, BrowserLeft + x1 + width1, BrowserTop + y1, &pt);
    LineTo(hdc, BrowserLeft + x1 + width1, BrowserTop + y1 + height1);

    /*MoveToEx(hdc, 0, 30, &pt);
    LineTo(hdc, 500, 30);

    MoveToEx(hdc, 502, 221, &pt);
    LineTo(hdc, WindowWidth, 221);*/
}

std::string InspectResult::Serialize()
{
    picojson::value::object res;

    if(isimage)
    {
        std::string res = imagedata;
        res.insert(res.begin(),'"');
        res.push_back('"');
        imagedata.clear();
        return res;
    }else
    {
        res["css"] = picojson::value(css);
        res["css1"] = picojson::value(css);
        if(css2 != css)
            res["css2"] = picojson::value(css2);
        if(css3 != css && css3 != css2)
            res["css3"] = picojson::value(css3);
        res["match"] = picojson::value(match);
        res["xpath"] = picojson::value(xpath);
        res["mousex"] = picojson::value(std::to_string(mousex));
        res["mousey"] = picojson::value(std::to_string(mousey));

        return picojson::value(res).serialize();
    }
}
