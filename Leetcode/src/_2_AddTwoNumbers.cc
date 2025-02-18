#include "ListNode.hh"

class Solution {
public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {

    int carry = 0;
    ListNode *head = new ListNode(), *current = head;
    while (l1 != nullptr || l2 != nullptr) {
      int firstDigit = (l1 != nullptr ? l1->val : 0),
          secondDigit = (l2 != nullptr ? l2->val : 0);

      int partialSum = firstDigit + secondDigit + carry;
      carry = (partialSum < 10 ? 0 : 1);

      current->val = partialSum % 10;

      l1 = (l1 != nullptr ? l1->next : nullptr);
      l2 = (l2 != nullptr ? l2->next : nullptr);

      if (l1 != nullptr || l2 != nullptr || carry > 0) {
        current->next = new ListNode();
        current = current->next;
      }
    }

    if (carry > 0)
      current->val = 1;

    return head;
  }
};
