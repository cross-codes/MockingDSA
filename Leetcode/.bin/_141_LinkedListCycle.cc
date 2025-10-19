#include "ListNode.hh"

class Solution
{
public:
  bool hasCycle(ListNode *head)
  {
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
      return false;

    ListNode *slow = head, *fast = head;

    while (true)
    {
      if (fast == nullptr || fast->next == nullptr)
        return false;

      slow = slow->next;
      fast = fast->next->next;

      if (slow == fast)
        return true;
    }
  }
};
