package neetcode.practice.Linked_List;

class Solution {
  public ListNode reverseList(ListNode head) {
    if (head == null || head.next == null)
      return head;

    ListNode prevNode = null, currentNode = head, nextNode = head.next;
    while (nextNode != null) {
      currentNode.next = prevNode;
      prevNode = currentNode;
      currentNode = nextNode;
      nextNode = currentNode.next;
    }

    currentNode.next = prevNode;
    return currentNode;
  }
}