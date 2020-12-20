#include "Utils.h"

std::vector<std::string> split_by(std::string s, std::string delimiter) {
    std::vector<std::string> result;

    auto start = 0U;
    auto end = s.find(delimiter);
    while (end != std::string::npos)
    {
        result.push_back(s.substr(start, end - start));
        start = end + delimiter.length();
        end = s.find(delimiter, start);
    }

    result.push_back(s.substr(start, end));

    return result;
}
