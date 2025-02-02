#include <cstddef>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

struct DualLinkedNode {
public:
  int key, value;
  DualLinkedNode *prev, *next;

  DualLinkedNode(int key, int value)
      : key(key), value(value), prev(nullptr), next(nullptr) {};
};

class LRUCache {
private:
  size_t capacity_, currentSize_;
  DualLinkedNode *headSentinel_, *tailSentinel_;
  __gnu_pbds::gp_hash_table<int, DualLinkedNode *> cache_;

  void breakAndShiftToFront(DualLinkedNode *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;

    addToFront(node);
  }

  void addToFront(DualLinkedNode *node) {
    node->next = headSentinel_->next;
    node->prev = headSentinel_;

    headSentinel_->next->prev = node;
    headSentinel_->next = node;
    currentSize_++;
  }

  void removeBack() {
    auto tail = tailSentinel_->prev;

    tail->prev->next = tail->next;
    tail->next->prev = tail->prev;

    cache_.erase(tail->key);
    currentSize_--;
  }

public:
  LRUCache(size_t capacity)
      : capacity_(capacity), currentSize_(0),
        headSentinel_(new DualLinkedNode(-1, -1)),
        tailSentinel_(new DualLinkedNode(-1, -1)), cache_() {
    headSentinel_->next = tailSentinel_;
    tailSentinel_->prev = headSentinel_;
  }

  int get(int key) {
    auto it = cache_.find(key);

    if (it != cache_.end()) {
      auto node = it->second;
      breakAndShiftToFront(node);

      return node->value;
    } else
      return -1;
  }

  void put(int key, int value) {
    auto it = cache_.find(key);
    if (it == cache_.end()) {
      auto newNode = new DualLinkedNode(key, value);

      cache_.insert({key, newNode});
      addToFront(newNode);

      if (currentSize_ > capacity_) 
        removeBack();
    } else {
      auto node = it->second;
      node->value = value;
      breakAndShiftToFront(node);
    }
  }
};
