#include "./ListNode.hpp"

class Solution {
public:
  ListNode *newHead = nullptr;

  void reverse(ListNode *head) {
    if (head->next->next == nullptr) {
      newHead = head->next;
      head->next->next = head;
      head->next = nullptr;
      return;
    }

    reverse(head->next);
    head->next->next = head;
    head->next = nullptr;
  }

  ListNode *reverseList(ListNode *head) {
    if (head == nullptr || head->next == nullptr)
      return head;

    reverse(head);
    return newHead;
  }
};
