#include <cstddef>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <vector>

struct Node {
public:
  int val;
  Node *next, *random;

  Node(int _val) : val(_val), next(nullptr), random(nullptr) {};
};

class Solution {
public:
  Node *copyRandomList(Node *head) {
    if (head == nullptr)
      return nullptr;

    if (head->next == nullptr)
      return new Node(head->val);

    __gnu_pbds::gp_hash_table<Node *, Node *> nodeToCopy{};
    std::vector<Node *> nodeOrder{};

    Node *current = head;
    while (current != nullptr) {
      nodeOrder.push_back(current);
      nodeToCopy[current] = new Node(current->val);
      current = current->next;
    }

    std::size_t n = nodeOrder.size();

    Node *newHead = nodeToCopy[head];
    newHead->next = nodeToCopy[head->next];
    newHead->random = nodeToCopy[head->random];

    Node *newCurrent = newHead->next;

    for (std::size_t i = 0; i <= n - 1; i++) {
      newCurrent->next = nodeToCopy[nodeOrder[i]->next];
      newCurrent->random = nodeToCopy[nodeOrder[i]->random];
      newCurrent = newCurrent->next;
    }

    return newHead;
  }
};
