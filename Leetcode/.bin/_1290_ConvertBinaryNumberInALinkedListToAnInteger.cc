#include "ListNode.hh"
#include <string>

class Solution
{
public:
  int getDecimalValue(ListNode *head)
  {
    std::string bin{};
    ListNode *curr = head;
    while (curr != nullptr)
    {
      bin.push_back(static_cast<char>('0' + curr->val));
      curr = curr->next;
    }

    return std::stoi(bin, 0, 2);
  }
};
