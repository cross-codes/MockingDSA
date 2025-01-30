#include "./ListNode.hh"

class Solution {
public:
  auto reverse(ListNode *head) -> ListNode * {
    if (head == nullptr || head->next == nullptr)
      return head;

    ListNode *prev = nullptr, *current = head, *next = head->next;

    while (next != nullptr) {
      current->next = prev;
      prev = current;
      current = next;
      next = next->next;
    }

    current->next = prev;

    return current;
  }

  void reorderList(ListNode *head) {
    ListNode *slow = head, *fast = head;

    while (fast != nullptr && fast->next != nullptr) {
      slow = slow->next;
      fast = fast->next->next;
    }

    ListNode *firstHalf = head, *secondHalf = slow->next;
    slow->next = nullptr;
    secondHalf = reverse(secondHalf);

    while (firstHalf != nullptr && secondHalf != nullptr) {
      ListNode *firstAux = firstHalf->next, *secondAux = secondHalf->next;

      firstHalf->next = secondHalf;
      secondHalf->next = firstAux;
      firstHalf = firstAux, secondHalf = secondAux;
    }
  }
};
