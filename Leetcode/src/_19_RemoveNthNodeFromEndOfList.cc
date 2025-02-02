#include "ListNode.hh"

class Solution {
public:
  ListNode *removeNthFromEnd(ListNode *head, int n) {
    if (head == nullptr || head->next == nullptr) [[unlikely]]
      return nullptr;

    ListNode *prev = nullptr, *current = head, *marker = head;

    while (n-- > 0)
      marker = marker->next;

    while (marker != nullptr) {
      prev = current;
      current = current->next;
      marker = marker->next;
    }

    if (prev == nullptr) [[unlikely]]
      head = current->next;
    else
      prev->next = current->next;

    return head;
  }
};
