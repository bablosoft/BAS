#ifndef REPLACEALL_H
#define REPLACEALL_H

#include <string>

void ReplaceAllInPlace(std::string & str, const std::string& from, const std::string& to);
std::string ReplaceAll(const std::string & str, const std::string& from, const std::string& to);

#endif // REPLACEALL_H
