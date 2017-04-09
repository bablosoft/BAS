#include "xml_encoder.h"

void xml_encode(std::string& data) {
    std::string buffer;
    buffer.reserve(data.size());
    for(size_t pos = 0; pos != data.size(); ++pos) {
        bool AllowedChar = true;
        /*int c = data[pos];
        if(c < 32 && c != 9 && c != 10 && c != 13)
        {
            AllowedChar = false;
        }*/

        if(AllowedChar)
        {
            switch(data[pos]) {
                case '&':  buffer.append("&amp;");       break;
                case '\"': buffer.append("&quot;");      break;
                case '\'': buffer.append("&apos;");      break;
                case '<':  buffer.append("&lt;");        break;
                case '>':  buffer.append("&gt;");        break;
                default:   buffer.append(&data[pos], 1); break;
            }
        }
    }
    data.swap(buffer);
}
