#include <vector>

struct Node
{
public:
  Node *next;
  int val;

  Node(int val) : next{nullptr}, val{val}
  {
  }
};

class LinkedList
{
private:
  Node *head_{}, *tail_{};

public:
  LinkedList()
  {
  }

  ~LinkedList()
  {
    Node *current = head_;
    while (current)
    {
      Node *tmp = current;
      current   = current->next;
      delete tmp;
    }
  }

  int get(int index)
  {
    Node *current = head_;
    int idx       = 0;
    while (current && idx < index)
    {
      current = current->next;
      idx += 1;
    }
    if (!current)
      return -1;
    return current->val;
  }

  void insertHead(int val)
  {
    Node *new_head = new Node(val);
    new_head->next = head_;
    head_          = new_head;
    if (tail_ == nullptr)
      tail_ = new_head;
  }

  void insertTail(int val)
  {
    Node *new_tail = new Node(val);
    if (tail_ == nullptr)
    {
      head_ = tail_ = new_tail;
    }
    else
    {
      tail_->next = new_tail;
      tail_       = new_tail;
    }
  }

  bool remove(int index)
  {
    if (head_ == nullptr)
      return false;
    if (index == 0)
    {
      Node *to_delete = head_;
      head_           = head_->next;

      if (head_ == nullptr)
        tail_ = nullptr;

      delete to_delete;
      return true;
    }
    Node *prev = head_;
    int idx    = 0;
    while (prev->next && idx < index - 1)
    {
      prev = prev->next;
      idx += 1;
    }

    if (!prev->next)
      return false;

    Node *to_delete = prev->next;
    prev->next      = to_delete->next;
    if (to_delete == tail_)
      tail_ = prev;
    delete to_delete;
    return true;
  }

  std::vector<int> getValues()
  {
    std::vector<int> res;
    Node *current = head_;
    while (current)
    {
      res.push_back(current->val);
      current = current->next;
    }
    return res;
  }
};
