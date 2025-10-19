#include <string>
#include <vector>

class Solution
{
public:
  std::vector<std::string> getLongestSubsequence(
      std::vector<std::string> &words, std::vector<int> &groups)
  {
    int n = static_cast<int>(words.size());
    std::vector<std::string> zero_run{}, one_run{};

    auto run = [&groups, &n, &words](bool zero_run,
                                     std::vector<std::string> &res) -> void {
      int first{};
      for (; first < n; first++)
        if (groups[first] == zero_run)
          break;

      if (first == n)
        return;

      res.push_back(words[first]);

      bool alternate = true;
      for (; first < n; first++)
      {
        if (alternate)
        {
          if (groups[first] == !zero_run)
          {
            res.push_back(words[first]);
            alternate = !alternate;
          }
        }
        else
        {
          if (groups[first] == zero_run)
          {
            res.push_back(words[first]);
            alternate = !alternate;
          }
        }
      }
    };

    run(true, zero_run), run(false, one_run);
    return zero_run.size() > one_run.size() ? zero_run : one_run;
  }
};
