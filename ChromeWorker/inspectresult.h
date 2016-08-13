#ifndef INSPECTRESULT
#define INSPECTRESULT

#include <string>
#include <vector>
#include <windows.h>

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
  std::string match;
  int mousex;
  int mousey;
  bool active;
  void Paint(HDC hdc, int BrowserRealWidth, int BrowserRealHeight, int BrowserDrawWidth, int BrowserDrawHeight, int BrowserScrollX, int BrowserScrollY, int BrowserLeft, int BrowserTop);
  std::string Serialize();
};

#endif // INSPECTRESULT

