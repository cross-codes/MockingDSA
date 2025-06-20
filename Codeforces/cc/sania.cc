#include <algorithm>
#include <cstring>
#include <vector>

std::vector<int> get_preference_order(
    std::vector<std::vector<int>> song_priority_order)
{
  int n = static_cast<int>(song_priority_order.size());
  int m = static_cast<int>(song_priority_order[0].size());

  int positions[n][m];
  std::memset(positions, 0x00, sizeof(positions));

  std::pair<int, int> scores[m];
  for (int i = 0; i < m; i++)
    scores[i] = std::make_pair(0, i);

  for (int i = 0; i < m; i++)
    for (int j = i + 1; j < m; j++)
    {
      int num_pref_i{}, num_pref_j{};

      for (int k = 0; k < m; k++)
        if (positions[k][i] < positions[k][j])
          num_pref_i += 1;
        else
          num_pref_j += 1;

      if (num_pref_i >= num_pref_j)
        scores[i].first += 1;
      else
        scores[j].first += 1;
    }

  auto PAIR_ORDER = [](const std::pair<int, int> &a,
                       const std::pair<int, int> &b) -> bool {
    int cmp1 = a.first - b.first;
    if (cmp1 == 0)
      return a.second < b.second;
    else
      return cmp1 > 0;
  };

  std::sort(scores, scores + m, PAIR_ORDER);
  std::vector<int> res{};
  for (const auto &[s, id] : scores)
    res.push_back(id);

  return res;
}
