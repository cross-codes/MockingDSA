#include <algorithm>
#include <string>
#include <vector>

class Solution
{
private:
  auto ltrim(std::string_view s) -> std::string_view
  {
    auto start = s.find_first_not_of(" ");
    if (start == std::string_view::npos)
      return std::string_view{};
    else
      return s.substr(start);
  }

  auto rtrim(std::string_view s) -> std::string_view
  {
    auto end = s.find_last_not_of(" ");
    if (end == std::string_view::npos)
      return std::string_view{};
    else
      return s.substr(0, end + 1);
  }

  auto split(std::string_view s, char delim) -> std::vector<std::string_view>
  {
    std::vector<std::string_view> res{};
    auto start = 0UZ, end = s.find(delim);

    while (end != std::string_view::npos)
    {
      res.emplace_back(s.substr(start, end - start));
      start = s.find_first_not_of(" ", end);
      end   = s.find(delim, start);
    }

    res.emplace_back(s.substr(start));
    return res;
  }

public:
  std::string reverseWords(std::string s)
  {
    auto tokens = split(rtrim(ltrim(s)), ' ');

    std::reverse(tokens.begin(), tokens.end());
    std::string res{};
    for (const auto &token : tokens)
    {
      res += token;
      res += " ";
    }

    if (!res.empty())
      res.pop_back();
    return res;
  }
};
