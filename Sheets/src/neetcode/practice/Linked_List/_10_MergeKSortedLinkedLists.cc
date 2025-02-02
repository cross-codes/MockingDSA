#include "ListNode.hh"
#include <vector>

class Solution {
public:
  ListNode *newHead = nullptr;

  void merge(ListNode *otherHead) {
    ListNode *left = newHead, *right = otherHead;

    if (left->val < right->val) {
      newHead = left;
      left = left->next;
    } else {
      newHead = right;
      right = right->next;
    }

    ListNode *current = newHead;

    while (left != nullptr && right != nullptr) {
      if (left->val < right->val) {
        current->next = left;
        left = left->next;
      } else {
        current->next = right;
        right = right->next;
      }

      current = current->next;
    }

    while (left != nullptr) {
      current->next = left;
      left = left->next;
      current = current->next;
    }

    while (right != nullptr) {
      current->next = right;
      right = right->next;
      current = current->next;
    }
  }

  ListNode *mergeKLists(std::vector<ListNode *> &lists) {
    if (lists.empty())
      return nullptr;

    newHead = lists[0];
    size_t n = lists.size();

    for (size_t i = 1; i < n; i++)
      merge(lists[i]);

    return newHead;
  }
};
