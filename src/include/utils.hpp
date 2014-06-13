#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

namespace utils {

    std::vector<std::string> get_lines(std::string);
    std::vector<std::string> get_lines(std::ifstream&);
    std::vector<std::string> split(std::string, char);

    std::vector<int> get_size(std::vector<std::string>);
};

#endif
