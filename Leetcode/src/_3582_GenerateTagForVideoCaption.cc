#include <algorithm>
#include <string>
#include <vector>

class Solution
{
private:
  constexpr inline std::vector<std::string> split(std::string s,
                                                  std::string delimiter)
  {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
    {
      token     = s.substr(pos_start, pos_end - pos_start);
      pos_start = pos_end + delim_len;
      res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
  }

public:
  std::string generateTag(std::string caption)
  {
    caption.erase(caption.begin(), std::find_if(caption.begin(), caption.end(),
                                                [](unsigned char c) {
                                                  return !std::isspace(c);
                                                }));
    auto vec = split(caption, " ");
    for (auto &word : vec)
      std::transform(word.begin(), word.end(), word.begin(), ::tolower);

    int n = static_cast<int>(vec.size());

    for (int i = 1; i < n; i++)
      vec[i][0] = static_cast<char>(std::toupper(vec[i][0]));

    std::string res{'#'};
    for (int i = 0; i < n; i++)
    {
      if (res.size() == 100)
        break;

      auto word = vec[i];
      res.append(word);
    }

    if (res.size() > 100)
      return res.substr(0, 100);
    else
      return res;
  }
};
