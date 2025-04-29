#include <cstring>
#include <queue>
#include <vector>

class Solution {
public:
  bool canFinish(int numCourses, std::vector<std::vector<int>> &prerequisites) {
    std::size_t n = prerequisites.size();

    int inDegrees[numCourses];
    std::memset(inDegrees, 0x00, sizeof(inDegrees));

    for (std::size_t i = 0; i < n; i++)
      inDegrees[prerequisites[i][1]]++;

    std::queue<int> vertexQueue;
    for (int i = 0; i < numCourses; i++) {
      if (inDegrees[i] == 0)
        vertexQueue.push(i);
    }

    while (!vertexQueue.empty()) {
      int vertex = vertexQueue.front();
      vertexQueue.pop();
      inDegrees[vertex] = -1;

      for (std::size_t i = 0; i < n; i++) {
        if (prerequisites[i][0] == vertex)
          inDegrees[prerequisites[i][1]]--;
      }

      for (int i = 0; i < numCourses; i++) {
        if (inDegrees[i] == 0)
          vertexQueue.push(i);
      }
    }

    bool cond = true;
    for (std::size_t i = 0; i < n; i++) {
      if (inDegrees[i] >= 0) {
        cond = false;
        break;
      }
    }

    return vertexQueue.empty() && cond;
  }
};
