class Solution
{
public:
  int getSum(int a, int b)
  {
    while (b != 0)
    {
      int temp = a;
      a        = a ^ b;
      b        = (temp & b) << 1;
    }
    return a;
  }
};
