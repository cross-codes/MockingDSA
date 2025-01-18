#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <cstdint>
#include <cstring>
#include <iostream>
#include <queue>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  std::cin >> t;
  while (t-- > 0) {
    size_t n;
    std::cin >> n;

    int adj[n][n], inDegree[n];
    size_t topologicalOrder[n];

    std::memset(adj, 0, sizeof(adj));
    std::memset(inDegree, 0, sizeof(inDegree));
    std::memset(topologicalOrder, 0, sizeof(topologicalOrder));

    for (size_t i = 0; i < n; i++) {
      std::string row;
      std::cin >> row;
      for (size_t j = 0; j < n; j++)
        adj[i][j] = row[j] - '0';
    }

    for (size_t i = 0; i < n; i++) {
      for (size_t j = i + 1; j < n; j++) {
        if (adj[i][j] == 1)
          inDegree[j]++;
        else
          inDegree[i]++;
      }
    }

    std::queue<size_t> nodeQueue{};
    for (size_t i = 0; i < n; i++) {
      if (inDegree[i] == 0)
        nodeQueue.push(i);
    }

    int i = 0;
    while (!nodeQueue.empty()) {
      size_t node = nodeQueue.front();
      nodeQueue.pop();
      topologicalOrder[i++] = node + 1;
      inDegree[node] = -1;

      for (size_t j = 0; j < node; j++) {
        if (adj[j][node] == 0)
          inDegree[j]--;
      }

      for (size_t j = node; j < n; j++) {
        if (adj[node][j] == 1)
          inDegree[j]--;
      }

      for (size_t j = 0; j < n; j++) {
        if (inDegree[j] == 0) {
          inDegree[j] = -1;
          nodeQueue.push(j);
        }
      }
    }

    for (const size_t &node : topologicalOrder) 
      std::cout << node << " ";

    std::cout << "\n";
  }

  return 0;
}
