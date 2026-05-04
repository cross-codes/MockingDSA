#include <array>
#include <vector>

class Solution
{
public:
  bool mergeTriplets(std::vector<std::vector<int>> &triplets,
                     std::vector<int> &target)
  {
    std::array<bool, 3> tests{};

    for (const auto &triplet : triplets)
    {
      if (triplet[0] > target[0] || triplet[1] > target[1] ||
          triplet[2] > target[2])
        continue;

      for (int i = 0; i < 3; i++)
      {
        if (triplet[i] == target[i])
          tests[i] = true;
      }
    }

    return tests[0] && tests[1] && tests[2];
  }
};
