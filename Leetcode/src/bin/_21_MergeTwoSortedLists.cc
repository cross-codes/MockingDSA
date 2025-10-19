#include "ListNode.hh"

class Solution
{
public:
  ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
  {
    ListNode *left = list1, *right = list2;
    ListNode *newHead = nullptr;

    if (left == nullptr)
      return right;
    else if (right == nullptr)
      return left;

    if (left->val < right->val)
    {
      newHead = left;
      left    = left->next;
    }
    else
    {
      newHead = right;
      right   = right->next;
    }

    ListNode *current = newHead;

    while (left != nullptr && right != nullptr)
    {
      if (left->val < right->val)
      {
        current->next = left;
        left          = left->next;
        current       = current->next;
      }
      else
      {
        current->next = right;
        right         = right->next;
        current       = current->next;
      }
    }

    while (left != nullptr)
    {
      current->next = left;
      left          = left->next;
      current       = current->next;
    }

    while (right != nullptr)
    {
      current->next = right;
      right         = right->next;
      current       = current->next;
    }

    return newHead;
  }
};
