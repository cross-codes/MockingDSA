#include <climits>
#include <cstdint>
#include <optional>
#include <unordered_map>
#include <vector>

class Solution
{
public:
  std::vector<int> earliestAndLatest(int n, int f, int s)
  {
    f -= 1;
    s -= 1;

    auto get_pairs_or_end = [&f, &s](uint32_t players, int &odd_player)
        -> std::optional<std::vector<std::pair<int, int>>> {
      std::vector<int> p{};

      int curr = players;
      while (curr != 0)
      {
        int pos = __builtin_ctz(curr);
        p.push_back(pos);
        curr &= curr - 1;
      }

      std::vector<std::pair<int, int>> res{};

      int n = static_cast<int>(p.size());
      int l{}, r{n - 1};
      while (l < r)
      {
        res.emplace_back(p[l], p[r]);
        l += 1;
        r -= 1;
      }

      if (l == r)
        odd_player = p[l];

      if (res.size() == 0)
        return std::nullopt;

      for (const auto &[x, y] : res)
        if ((x == f && y == s) || (x == s && y == f))
          return std::nullopt;

      return res;
    };

    std::unordered_map<uint32_t, int> lookup{};

    int mn{INT_MAX}, mx{INT_MIN};
    auto dfs = [&lookup, &f, &s, &mn, &mx,
                &get_pairs_or_end](auto &&dfs, uint32_t set, int depth) -> int {
      if (lookup.contains(set))
        return lookup[set];

      int odd_player{-1};

      auto pairs = get_pairs_or_end(set, odd_player);
      if (!pairs.has_value())
      {
        mn = std::min(mn, depth);
        mx = std::max(mx, depth);
        return depth;
      }

      int n = static_cast<int>(pairs->size());
      for (int i = 0; i < (1 << n); i++)
      {
        uint32_t new_set{};
        if (odd_player != -1)
          new_set |= (1 << odd_player);

        for (int j = 0; j < n; j++)
        {
          auto [a, b] = (*pairs)[j];
          if (a == f || a == s)
            new_set |= (1 << a);
          else if (b == f || b == s)
            new_set |= (1 << b);
          else
          {
            if (i & (1 << j))
              new_set |= (1 << b);
            else
              new_set |= (1 << a);
          }
        }

        int end_depth = dfs(dfs, new_set, depth + 1);
        if (end_depth != INT_MAX)
        {
          mn = std::min(end_depth, mn);
          mx = std::max(end_depth, mx);
        }
      }

      return lookup[set] = INT_MAX;
    };

    dfs(dfs, (1 << n) - 1, 1);
    return {mn, mx};
  }
};
