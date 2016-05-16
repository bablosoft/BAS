#include "match.h"
#include <algorithm>
#include <locale>


char tolower(char in)
{
    std::locale loc;
    return std::tolower(in,loc);
}

bool match(const std::string& pattern, const std::string& text)
{
    std::string p = std::string("*") + pattern + std::string("*");
    return match_strict(p,text);

}

bool match_strict(const std::string& pattern, const std::string& text)
{
    const char* s;
    const char* p;
    const char *str = text.c_str();
    const char *pat = pattern.c_str();
    bool star = false;

    loopStart:
       for (s = str, p = pat; *s; ++s, ++p) {
          switch (*p) {
             case '?':
                if (*s == '.') goto starCheck;
                break;
             case '*':
                star = true;
                str = s, pat = p;
                if (!*++pat) return true;
                goto loopStart;
             default:
                if (tolower(*s) != tolower(*p))
                   goto starCheck;
                break;
          } /* endswitch */
       } /* endfor */
       if (*p == '*') ++p;
       return (!*p);

    starCheck:
       if (!star) return false;
       str++;
       goto loopStart;
}
