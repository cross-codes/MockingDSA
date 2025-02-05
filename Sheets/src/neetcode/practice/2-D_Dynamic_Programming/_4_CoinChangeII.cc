#include <cstring>
#include <vector>

class Solution {
public:
  int change(int amount, std::vector<int> &coins) {
    int distinctAmount[amount + 1];

    std::memset(distinctAmount, 0x00, sizeof(distinctAmount));

    distinctAmount[0] = 1;
    for (const int &coin: coins) {
      for (int i = 1;i <= amount; i++)
        if (i >= coin)
          distinctAmount[i] += distinctAmount[i - coin];
    }

    return distinctAmount[amount];
  }
};
