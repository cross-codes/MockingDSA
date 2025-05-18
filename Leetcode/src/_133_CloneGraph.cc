#include "Node.hh"
#include <unordered_map>
#include <unordered_set>

class Solution
{
private:
  std::unordered_map<Node *, Node *> copies_{};
  std::unordered_set<Node *> visited_{};

  void dfs_visit_(Node *node)
  {
    Node *node_copy = copies_[node];
    visited_.insert(node);

    for (Node *neighbor : node->neighbors)
    {
      Node *nbd_copy;

      auto it = copies_.find(neighbor);
      if (it == copies_.end())
      {
        nbd_copy = new Node(neighbor->val);
        copies_.insert({neighbor, nbd_copy});
      }
      else
        nbd_copy = it->second;

      node_copy->neighbors.push_back(nbd_copy);
      if (!visited_.contains(neighbor))
        dfs_visit_(neighbor);
    }
  }

public:
  Node *cloneGraph(Node *node)
  {
    if (node == nullptr)
      return nullptr;

    Node *root_copy = new Node(node->val);
    copies_.insert({node, root_copy});
    visited_.insert(node);

    for (Node *neighbor : node->neighbors)
    {
      Node *nbd_copy;

      auto it = copies_.find(neighbor);
      if (it == copies_.end())
      {
        nbd_copy = new Node(neighbor->val);
        copies_.insert({neighbor, nbd_copy});
      }
      else
        nbd_copy = it->second;

      root_copy->neighbors.push_back(nbd_copy);

      if (!visited_.contains(neighbor))
        dfs_visit_(neighbor);
    }

    return root_copy;
  }
};
