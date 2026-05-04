#include <algorithm>
#include <charconv>

class Solution
{
public:
  int reverse(int x)
  {
    char buf[11]{};
    auto [ptr, ec] = std::to_chars(buf, buf + sizeof(buf), x);

    if (x < 0)
      std::reverse(buf + 1, ptr);
    else
      std::reverse(buf, ptr);

    int result{};
    auto [rptr, rec] = std::from_chars(buf, ptr, result);
    if (rec == std::errc())
      return result;
    else if (rec == std::errc::result_out_of_range)
      return 0;

    __builtin_unreachable();
  }
};
