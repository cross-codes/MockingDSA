#include <iostream>
#include <string>
#include <vector>

class Solution {
private:
  inline std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
      token = s.substr(pos_start, pos_end - pos_start);
      pos_start = pos_end + delim_len;
      res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
  }

public:
  std::string encode(std::vector<std::string> &strs) {
    if (strs.empty())
      return "";

    if (strs.size() == 1 && strs[0].empty())
      return "\u011F";

    std::string res{};
    size_t n = strs.size();

    for (size_t i = 0; i < n - 1; i++)
      res += strs[i] + "\u011F";

    res += strs[n - 1];

    return res;
  }

  std::vector<std::string> decode(std::string str) {
    if (str.empty()) [[unlikely]]
      return {};

    if (str == "\u011F") [[unlikely]]
      return {""};

    auto decoded = split(str, "\u011F");
    if (decoded.empty())
      return {""};
    return decoded;
  }
};
