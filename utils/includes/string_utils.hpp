#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <string>
#include <vector>

class StringUtils {
public:
  static std::vector<std::string> parseString(std::string str,
                                              char delimiter = ',');
};

#endif // !STRING_UTILS_HPP
