#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _83B
{

auto sumOfDigits(int) -> int;

auto run() -> void
{
  int N;
  std::cin >> N;

  int A, B;
  std::cin >> A >> B;

  i64 sum{};
  for (int i = 1; i <= N; i++)
  {
    int digitSum = sumOfDigits(i);
    if (digitSum <= B && digitSum >= A)
      sum += i;
  }

  std::cout << sum << "\n";
}

auto sumOfDigits(int n) -> int
{
  int res{};
  while (n != 0)
  {
    res += n % 10;
    n /= 10;
  }

  return res;
}

} // namespace _83B

int main()
{
#ifdef CROSS
  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr)
  {
#if __cplusplus >= 202302L
    std::println(stderr, "Input file not found");
#else
    std::cerr << "Input file not found\n";
#endif
    __builtin_trap();
  }
#else
  std::cin.tie(nullptr)->sync_with_stdio(false);
#endif

  int t{1};

  while (t-- > 0)
    _83B::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
