#ifndef CONVERTENCODINC_H
#define CONVERTENCODINC_H

#include <string>
#include <memory>
#include <vector>

struct ConverterResultClass
{
      std::string Result;
      bool WasSuccess;
};

using ConverterResult = std::shared_ptr<ConverterResultClass>;


ConverterResult convert(const std::string& text, const std::string& encoding_in, const std::string& encoding_out);
ConverterResult convert_to_utf8(const std::string& text, const std::string& encoding_in);

#endif // CONVERTENCODINC_H
