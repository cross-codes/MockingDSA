#include "ListNode.hh"

class Solution
{
private:
  auto determine_length(ListNode *head) -> int
  {
    ListNode *current = head;

    int length{};
    while (current != nullptr)
    {
      current = current->next;
      length += 1;
    }

    return length;
  }

  // Inv: Valid reversal is possible
  auto reverse_group(ListNode *head, int k, ListNode *&last_before_rev,
                     ListNode *prev_new_head) -> ListNode *
  {
    ListNode *group_tail = head;
    ListNode *prev = nullptr, *current = head, *fwd = head->next;

    while (k-- > 0)
    {
      current->next = prev;
      prev          = current;
      current       = fwd;
      if (fwd != nullptr)
        fwd = fwd->next;
    }

    last_before_rev = prev;

    if (prev_new_head != nullptr)
      prev_new_head->next = last_before_rev;

    group_tail->next = current;
    return group_tail;
  }

public:
  ListNode *reverseKGroup(ListNode *head, int k)
  {
    int length     = determine_length(head);
    int num_groups = length / k;

    if (num_groups == 0)
      return head;

    ListNode *dummy, *start;
    ListNode *tail = reverse_group(head, k, start, nullptr);

    num_groups -= 1;
    while (num_groups-- > 0)
      tail = reverse_group(tail->next, k, dummy, tail);

    return start;
  }
};
