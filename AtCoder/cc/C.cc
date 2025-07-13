#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <cassert>
#include <cmath>   // IWYU pragma: keep
#include <cstdint> // IWYU pragma: keep
#include <cstring> // IWYU pragma: keep
#include <iostream>
#include <string> // IWYU pragma: keep
#include <unistd.h>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _C
{

auto run() -> void
{
  int a;
  std::cin >> a;

  int64_t n;
  std::cin >> n;

  auto conv = [](int64_t num, int base) -> std::string {
    std::string chars = "0123456789";
    std::string res{};
    while (num != 0)
    {
      res.push_back(chars[num % base]);
      num /= base;
    }

    std::reverse(res.begin(), res.end());
    return res;
  };

  std::vector<int64_t> palindromes{};
  for (int i = 0; i < 10; i++)
    palindromes.push_back(i);

  for (int len = 2; len <= 12; len++)
  {
    int hl    = (len + 1) >> 1;
    int64_t L = static_cast<int64_t>(std::pow(10LL, hl - 1));
    int64_t R = static_cast<int64_t>(std::pow(10LL, hl)) - 1;

    if (len & 1)
    {
      for (int64_t i = L; i <= R; i++)
      {
        std::string num = std::to_string(i), num_cpy = num;
        std::reverse(num_cpy.begin(), num_cpy.end());
        num += num_cpy.substr(1, std::string::npos);
        palindromes.push_back(std::stoll(num));
      }
    }
    else
    {
      for (int64_t i = L; i <= R; i++)
      {
        std::string num = std::to_string(i), num_cpy = num;
        std::reverse(num_cpy.begin(), num_cpy.end());
        num += num_cpy;
        palindromes.push_back(std::stoll(num));
      }
    }
  }

  auto is_palindrome = [](std::string num) -> bool {
    int l{}, r{static_cast<int>(num.size()) - 1};
    while (l <= r)
    {
      if (num[l] != num[r])
        return false;
      l += 1;
      r -= 1;
    }

    return true;
  };

  int64_t result{};
  for (int64_t e : palindromes)
  {
    if (e > n)
      break;
    if (is_palindrome(conv(e, a)))
      result += e;
  }

  std::cout << result << "\n";
}

} // namespace _C

int main()
{
  std::cin.tie(nullptr)->sync_with_stdio(false);

#ifdef ANTUMBRA
  const rlim_t stack_size = 268435456;
  struct rlimit rl;

  int result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0 && rl.rlim_cur < stack_size)
  {
    rl.rlim_cur = stack_size;
    result      = setrlimit(RLIMIT_STACK, &rl);
    if (result != 0)
      std::cerr << "WARN: setrlimit failed\n";
  }

  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr)
  {
    std::cerr << "Input file not found\n";
    __builtin_trap();
  }
#endif

  int t{1};
  while (t-- > 0)
    _C::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
