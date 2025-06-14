#include <chrono>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

template <> struct std::hash<std::pair<int, int>>
{
  std::size_t operator()(const std::pair<int, int> &a) const noexcept
  {
    return std::hash<int64_t>{}(a.first) ^ std::hash<int64_t>{}(a.second);
  }
};

class Solution
{
private:
  struct StringHash
  {
  private:
    int n;

  public:
    std::vector<int> powers{}, prefix_hashes{};
    int64_t A;
    int B;

    StringHash(std::string s, int64_t _A, int _B)
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

    int hash(int l, int r)
    {
      int64_t h = static_cast<int64_t>(prefix_hashes[r]) -
                  static_cast<int64_t>(prefix_hashes[l]) * powers[r - l];
      return (h % B + B) % B;
    }
  };

public:
  std::string longestDupSubstring(std::string s)
  {
    int n{static_cast<int>(s.length())};

    std::mt19937_64 rng(
        std::chrono::steady_clock::now().time_since_epoch().count());

    int B1{static_cast<int>(1e9 - 7)};
    int64_t A1{std::uniform_int_distribution<int64_t>(
        static_cast<int>(0.1 * B1), static_cast<int>(0.9 * B1))(rng)};

    int B2{static_cast<int>(1e9 - 21)};
    int64_t A2{std::uniform_int_distribution<int64_t>(
        static_cast<int>(0.1 * B2), static_cast<int>(0.9 * B2))(rng)};

    StringHash h1(s, A1, B1), h2(s, A2, B2);

    auto pred = [&h1, &h2, &n](int k) -> std::optional<std::pair<int, int>> {
      std::unordered_map<std::pair<int, int>, std::pair<int, int>> seen{};
      for (int i = 0; i < n - k + 1; i++)
      {
        auto pair = std::make_pair(h1.hash(i, i + k), h2.hash(i, i + k));
        if (seen.contains(pair))
          return seen[pair];

        seen[pair] = {i, k};
      }

      return std::nullopt;
    };

    int L{-1}, R{n};
    while (R - L > 1)
    {
      int M                          = std::midpoint(L, R);
      (!pred(M).has_value() ? R : L) = M;
    }

    if (auto result = pred(L))
    {
      auto [idx, length] = *result;
      return s.substr(idx, length);
    }
    else
      return "";
  }
};
