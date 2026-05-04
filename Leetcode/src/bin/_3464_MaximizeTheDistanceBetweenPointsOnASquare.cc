#include <algorithm>
#include <numeric>
#include <vector>

class Solution
{
public:
  int maxDistance(int side, std::vector<std::vector<int>> &points, int k)
  {
    int n = static_cast<int>(points.size());

    auto manhattan_distance =
        [](const std::pair<int64_t, int64_t> &p1,
           const std::pair<int64_t, int64_t> &p2) -> int64_t {
      return std::abs(p1.first - p2.first) + std::abs(p1.second - p2.second);
    };

    auto get_equiv_dist = [&](const std::pair<int64_t, int64_t> &p) {
      if (p.second == side)
      {
        return p.first;
      }
      else if (p.first == side)
      {
        return side + (side - p.second);
      }
      else if (p.second == 0)
      {
        return INT64_C(2) * side + (side - p.first);
      }
      else if (p.first == 0)
      {
        return INT64_C(3) * side + p.second;
      }

      std::unreachable();
    };

    std::vector<std::pair<int64_t, int64_t>> coords(n);
    for (int i = 0; i < n; i++)
    {
      coords[i] = {points[i][0], points[i][1]};
    }

    auto cmp = [&](const std::pair<int64_t, int64_t> &a,
                   const std::pair<int64_t, int64_t> &b) -> bool {
      return get_equiv_dist(a) < get_equiv_dist(b);
    };

    std::sort(coords.begin(), coords.end(), cmp);

    auto pred = [&](int m) -> bool {
      for (int i = 0; i <= n - k; i++)
      {
        auto first     = coords[i];
        int curr_idx   = i;
        int cnt        = 1;
        auto find_next = [&](int start_idx,
                             const std::pair<int64_t, int64_t> &p_prev)
            -> std::optional<int> {
          int L = start_idx, R = n;

          while (R - L > 1)
          {
            int mid = std::midpoint(L, R);
            (manhattan_distance(p_prev, coords[mid]) >= m ? R : L) = mid;
          }

          if (R < n)
          {
            return R;
          }
          return std::nullopt;
        };

        bool possible = true;
        while (cnt < k)
        {
          auto nxt_idx = find_next(curr_idx, coords[curr_idx]);
          if (!nxt_idx.has_value())
          {
            possible = false;
            break;
          }

          curr_idx = *nxt_idx;
          cnt++;

          if (n - curr_idx < k - cnt)
          {
            possible = false;
            break;
          }
        }

        if (possible && manhattan_distance(coords[curr_idx], first) >= m)
        {
          return false;
        }
      }

      return true;
    };

    int L = -1, R = static_cast<int>(2e9) + 1;
    while (R - L > 1)
    {
      int M             = std::midpoint(L, R);
      (pred(M) ? R : L) = M;
    }

    return L;
  }
};
