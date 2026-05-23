#include <string>
#include <vector>

class Solution
{
private:
  auto split_(std::string_view s, char delim) -> std::vector<std::string>
  {
    std::vector<std::string> res{};
    size_t start = 0, end = s.find_first_of(delim);
    while (end != std::string_view::npos)
    {
      res.emplace_back(s.substr(start, end - start));
      start = end + 1;
      end   = s.find_first_of(delim, start);
    }

    res.emplace_back(s.substr(start));
    return res;
  }

public:
  int compareVersion(std::string version1, std::string version2)
  {
    auto tokens1 = split_(version1, '.');
    auto tokens2 = split_(version2, '.');

    int n{static_cast<int>(tokens1.size())};
    int m{static_cast<int>(tokens2.size())};

    for (int i = 0; i < std::max(n, m); i++)
    {
      int val1{}, val2{};
      if (i < n)
        val1 = std::stoi(tokens1[i]);
      if (i < m)
        val2 = std::stoi(tokens2[i]);

      if (val1 != val2)
        return val1 > val2 ? 1 : -1;
    }

    return 0;
  }
};
