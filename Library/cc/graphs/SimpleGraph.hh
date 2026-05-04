#include <queue>
#include <vector>

struct SimpleGraph {
 private:
  enum class Color { WHITE, GRAY, BLACK };

 public:
  int V{}, E{};
  constexpr static int INF{static_cast<int>(1e9)};

  struct Vertex {
    int p, u, d;
    Color color;

    Vertex(int u) : p{-1}, u{u}, d{INF}, color{Color::WHITE} {}
  };

  std::vector<Vertex> vertices{};
  std::vector<std::vector<int>> adj{};
  int NIL = -1;

  SimpleGraph(int n) : V(n) {
    for (int i = 0; i < V; i++)
      vertices.push_back(Vertex(i));

    reset();
  }

  void construct(const std::vector<std::pair<int, int>>& edge_list) {
    for (const auto& [from, to] : edge_list) {
      adj[from].push_back(to);
      adj[to].push_back(from);
      E += 1;
    }
  }

  void reset() { adj = std::vector<std::vector<int>>(V, std::vector<int>()); }

  void bfs(int source) {
    Vertex s = vertices[source];
    s.color  = Color::GRAY;
    s.p      = NIL;

    std::queue<Vertex> queue{};
    queue.emplace(s);

    while (!queue.empty()) {
      Vertex u = queue.front();
      queue.pop();

      for (const auto& id : adj[u.u]) {
        Vertex& v = vertices[id];
        if (v.color == Color::WHITE) {
          v.color = Color::GRAY;
          v.d     = u.d + 1;
          v.p     = u.u;
          queue.emplace(v);
        }
      }

      u.color = Color::BLACK;
    }
  }

  void shortest_path(int s, int v, bool& possible, std::vector<int>& path) {
    if (v == s)
      path.push_back(s);
    else if (vertices[v].p == NIL)
      possible = false;
    else {
      shortest_path(s, vertices[v].p, possible, path);
      path.push_back(v);
    }
  }
};
