#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <bit>       // IWYU pragma: keep
#include <cassert>
#include <cmath>   // IWYU pragma: keep
#include <cstdint> // IWYU pragma: keep
#include <cstring> // IWYU pragma: keep
#include <iostream>
#include <string> // IWYU pragma: keep
#include <unistd.h>
#include <unordered_map>
#include <unordered_set>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _WordCombinations
{

struct StringHash
{
private:
  int n;

public:
  std::vector<int> powers{}, prefix_hashes{};
  int64_t A;
  int B;

  StringHash(const std::string &s, int64_t _A, int _B)
      : n(static_cast<int>(s.length())), powers(n + 1, 1),
        prefix_hashes(n + 1, 0), A{_A}, B{_B}
  {
    for (int i = 1; i <= n; i++)
    {
      powers[i] = powers[i - 1] * A % B;
      prefix_hashes[i] =
          (prefix_hashes[i - 1] * A + static_cast<int64_t>(s[i - 1])) % B;
    }
  }

  int get_hash(int l, int r)
  {
    int64_t h = static_cast<int64_t>(prefix_hashes[r]) -
                static_cast<int64_t>(prefix_hashes[l]) * powers[r - l];
    return (h % B + B) % B;
  }
};

constexpr int64_t MOD = static_cast<int64_t>(1e9 + 7);

auto run() -> void
{
  std::string s;
  std::cin >> s;

  int n            = static_cast<int>(s.size());

  const int64_t A1 = 31;
  const int64_t B1 = static_cast<int>(1e9 + 7);

  const int64_t A2 = 53;
  const int64_t B2 = static_cast<int>(1e9 + 9);

  StringHash hash1(s, A1, B1), hash2(s, A2, B2);

  std::unordered_map<int, int> hashes{};
  hashes.reserve(100000);

  int k;
  std::cin >> k;
  while (k-- > 0)
  {
    std::string part;
    std::cin >> part;

    int m = static_cast<int>(part.size());

    StringHash h1(part, A1, static_cast<int>(B1));
    StringHash h2(part, A2, static_cast<int>(B2));
    hashes[h1.get_hash(0, m)] = h2.get_hash(0, m);
  }

  int comb[5001];
  std::memset(comb, -1, sizeof comb);

  auto dfs = [&n, &hashes, &hash1, &hash2, &comb](auto &&dfs,
                                                  int pos) -> int64_t {
    if (pos == n)
      return 1;

    if (comb[pos] != -1)
      return comb[pos];

    int64_t res{};
    for (int i = pos + 1; i <= n; i++)
      if (hashes.contains(hash1.get_hash(pos, i)) &&
          hashes[hash1.get_hash(pos, i)] == hash2.get_hash(pos, i))
        res += dfs(dfs, i);

    return comb[pos] = res % MOD;
  };

  std::cout << dfs(dfs, 0) << "\n";
}

} // namespace _WordCombinations

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
    _WordCombinations::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
