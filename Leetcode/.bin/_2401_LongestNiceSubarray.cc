#include <vector>

class Solution
{
public:
  int longestNiceSubarray(std::vector<int> &a)
  {
    int n = static_cast<int>(a.size()), mx{1};
    for (int k = 2; k < 31; k++)
    {
      for (int i = 0; i < n - k + 1; i++)
      {
        int test = a[i];
        bool possible{true};
        for (int j = i + 1; j < i + k; j++)
        {
          if ((a[j] & test))
          {
            possible = false;
            break;
          }
          test |= a[j];
        }

        if (possible)
        {
          mx = k;
          continue;
        }
      }
    }

    return mx;
  }
};
