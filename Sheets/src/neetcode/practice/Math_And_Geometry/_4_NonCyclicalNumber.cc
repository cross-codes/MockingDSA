#include <unordered_set>

class Solution {
private:
  std::unordered_set<int> seen;

public:
  Solution() : seen{} {};

  bool isHappy(int n) {
    while (true) {
      int sum = 0;
      while (n != 0) {
        int digit = n % 10;
        sum += digit * digit;
        n /= 10;
      }

      if (sum == 1)
        return true;

      if (seen.find(sum) != seen.end())
        return false;
      else {
        seen.insert(sum);
        n = sum;
      }
    }
  }
};
