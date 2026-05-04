class Solution
{
public:
  int tribonacci(int n)
  {
    int back{}, prev{1}, front{1};

    if (n < 3) [[unlikely]]
    {
      switch (n)
      {
      case 0:
        return back;

      case 1:
      case 2:
        return prev;

      default:
        __builtin_unreachable();
      }
    }

    for (int i = 3; i <= n; i++)
    {
      int next = front + prev + back;
      back     = prev;
      prev     = front;
      front    = next;
    }

    return front;
  }
};
