#include <array>
#include <vector>

class TreeAncestor
{
private:
  std::vector<std::array<int, 20>> lift{};

public:
  TreeAncestor(int n, std::vector<int> &parent)
  {
    lift.resize(n, std::array<int, 20>{});
    for (int u = 0; u < n; u++)
      lift[u][0] = parent[u];

    for (int i = 0; i < 20; i++)
      lift[0][i] = -1;

    for (int i = 1; i < 20; i++)
      for (int u = 0; u < n; u++)
        if (lift[u][i - 1] == -1)
          lift[u][i] = -1;
        else
          lift[u][i] = lift[lift[u][i - 1]][i - 1];
  }

  int getKthAncestor(int node, int k)
  {
    int curr = node;
    while (k != 0)
    {
      int pos = __builtin_ctz(k);
      curr    = lift[curr][pos];
      if (curr == -1)
        return curr;
      k &= (k - 1);
    }

    return curr;
  }
};
