#ifndef INSPECTRESULT
#define INSPECTRESULT

#include <string>
#include <vector>
#include <windows.h>

struct FrameInspectResult
{
    bool is_frame;
    std::string frame_name;
    std::string frame_url;
    std::string frame_tag_html;
    int frame_index;
    int x_with_padding;
    int y_with_padding;
    int frame_depth;
    int frame_id;
    int parent_frame_id;
};


struct InspectResult
{
  int x;
  int y;
  int width;
  int height;
  std::string label;
  std::string css;
  std::string css2;
  std::string css3;
  std::string xpath;
  std::string match;
  int mousex;
  int mousey;
  bool active;
  bool isimage = false;
  std::string imagedata;
  FrameInspectResult FrameData;
  void Paint(HDC hdc, int BrowserRealWidth, int BrowserRealHeight, int BrowserDrawWidth, int BrowserDrawHeight, int BrowserScrollX, int BrowserScrollY, int BrowserLeft, int BrowserTop);
  std::string Serialize();

};


#endif // INSPECTRESULT

