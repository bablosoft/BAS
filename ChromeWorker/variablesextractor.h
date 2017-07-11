#ifndef VARIABLESEXTRACTOR_H
#define VARIABLESEXTRACTOR_H

#include <string>

std::string extract_variables(const std::string& code);
std::string extract_global_variables(const std::string& code);

#endif // VARIABLESEXTRACTOR_H
