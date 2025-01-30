#include "./ListNode.hh"

class Solution {
public:
  ListNode *removeNthFromEnd(ListNode *head, int n) {
    ListNode *marker = head, *current = head, *prev = nullptr;
    while (n--)
      marker = marker->next;

    while (marker != nullptr) {
      prev = current;
      current = current->next;
      marker = marker->next;
    }

    if (prev == nullptr)
      return head->next;

    prev->next = current->next;
    return head;
  }
};
