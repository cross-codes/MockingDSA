#include <cstddef>
#include <unordered_map>

class Node
{
public:
  int val;
  Node *next;
  Node *random;

  Node(int _val)
  {
    val    = _val;
    next   = NULL;
    random = NULL;
  }
};

class Solution
{
public:
  Node *copyRandomList(Node *head)
  {
    if (head == nullptr)
      return nullptr;

    std::unordered_map<Node *, Node *> new_nodes{};
    Node *new_head  = new Node(head->val);
    new_nodes[head] = new_head;

    Node *curr      = head;
    Node *new_curr  = new_head;
    while (curr != nullptr)
    {
      if (curr->next == nullptr)
        new_curr->next = nullptr;
      else if (new_nodes.contains(curr->next))
        new_curr->next = new_nodes[curr->next];
      else
      {
        new_curr->next        = new Node(curr->next->val);
        new_nodes[curr->next] = new_curr->next;
      }

      if (curr->random == nullptr)
        new_curr->random = nullptr;
      else if (new_nodes.contains(curr->random))
        new_curr->random = new_nodes[curr->random];
      else
      {
        new_curr->random        = new Node(curr->random->val);
        new_nodes[curr->random] = new_curr->random;
      }

      curr     = curr->next;
      new_curr = new_curr->next;
    }

    return new_head;
  }
};
