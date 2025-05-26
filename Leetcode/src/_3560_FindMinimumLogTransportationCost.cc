class Solution
{
public:
  long long minCuttingCost(int n, int m, int k)
  {
    long long cost{};
    if (m > k)
      cost += (m - k) * static_cast<long long>(k);

    if (n > k)
      cost += (n - k) * static_cast<long long>(k);

    return cost;
  }
};
