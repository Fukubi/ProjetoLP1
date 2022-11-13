#include "string_utils.hpp"

#include <sstream>
#include <string>

std::vector<std::string> StringUtils::parseString(std::string str,
                                                  char delimeter) {
  std::stringstream parsing(str);
  std::string buffer;
  std::vector<std::string> parsedString;

  while (!parsing.eof()) {
    std::getline(parsing, buffer, delimeter);
    parsedString.push_back(buffer);
  }

  return parsedString;
}
