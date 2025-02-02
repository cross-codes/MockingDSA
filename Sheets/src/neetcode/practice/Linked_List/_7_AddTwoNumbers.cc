#include "ListNode.hh"

class Solution {
public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode *newHead = new ListNode(), *current = newHead;

    unsigned int carry = 0U;

    while (l1 != nullptr && l2 != nullptr) {
      int sum = l1->val + l2->val + carry;

      carry = (sum >= 10) ? 1 : 0;
      sum -= (sum >= 10) ? 10 : 0;

      current->val = sum;
      l1 = l1->next;
      l2 = l2->next;
      if (l1 == nullptr && l2 == nullptr && carry)
        current->next = new ListNode(carry);
      else if (l1 != nullptr || l2 != nullptr) {
        current->next = new ListNode();
        current = current->next;
      }
    }

    while (l1 != nullptr) {
      int sum = l1->val + carry;
      carry = (sum >= 10) ? 1 : 0;
      sum -= (sum >= 10) ? 10 : 0;

      current->val = sum;
      l1 = l1->next;
      if (l1 != nullptr) {
        current->next = new ListNode();
        current = current->next;
      } else if (carry != 0)
        current->next = new ListNode(1);
    }

    while (l2 != nullptr) {
      int sum = l2->val + carry;
      carry = (sum >= 10) ? 1 : 0;
      sum -= (sum >= 10) ? 10 : 0;

      current->val = sum;
      l2 = l2->next;
      if (l2 != nullptr) {
        current->next = new ListNode();
        current = current->next;
      } else if (carry != 0)
        current->next = new ListNode(1);
    }

    return newHead;
  }
};
