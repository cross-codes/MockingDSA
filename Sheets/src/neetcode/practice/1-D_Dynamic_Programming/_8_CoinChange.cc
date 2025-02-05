#include <climits>
#include <cstring>
#include <vector>

class Solution {
public:
  int coinChange(std::vector<int> &coins, int amount) {
    int minCoins[amount + 1];

    std::memset(minCoins, 0x00, sizeof(minCoins));

    for (int i = 1; i <= amount; i++) {
      minCoins[i] = INT_MAX;
      for (const int &coin: coins) {
        if (i - coin >= 0 && minCoins[i - coin] != -1)
          minCoins[i] = std::min(minCoins[i], minCoins[i - coin] + 1);
      }

      if (minCoins[i] == INT_MAX)
        minCoins[i] = -1;
    }

    return minCoins[amount];
  }
};
