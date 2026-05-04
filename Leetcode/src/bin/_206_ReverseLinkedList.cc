#include "ListNode.hh"

class Solution
{
public:
  ListNode *reverseList(ListNode *head)
  {
    if (head == nullptr || head->next == nullptr)
      return head;

    ListNode *prev = nullptr, *current = head, *next = head->next;

    while (next != nullptr)
    {
      current->next = prev;
      prev = current, current = next, next = next->next;
    }

    current->next = prev;

    return current;
  }
};
