#include <cstdlib>
#include <queue>

class Solution
{
public:
  int lastStoneWeight(std::vector<int> &stones)
  {
    std::priority_queue<int> heap;

    for (const int &stone : stones)
      heap.push(stone);

    while (heap.size() > 1)
    {
      int x = heap.top();
      heap.pop();
      int y = heap.top();
      heap.pop();

      if (x != y)
        heap.push(std::abs(x - y));
    }

    return (heap.size() == 0) ? 0 : heap.top();
  }
};
