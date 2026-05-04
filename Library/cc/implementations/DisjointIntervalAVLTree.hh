#include <memory>

struct Interval
{
  int start, end;
  Interval(int s, int e) : start(s), end(e) {};
};

struct IntervalNode
{
  Interval interval;
  int max_end, max_size, incl_height;

  std::unique_ptr<IntervalNode> left;
  std::unique_ptr<IntervalNode> right;

  IntervalNode(const Interval &i)
      : interval(i), max_end(i.end), max_size(i.end - i.start + 1),
        incl_height(1) {};
};

struct DisjointIntervalAVLTree
{
  std::unique_ptr<IntervalNode> root;

  int incl_height(const std::unique_ptr<IntervalNode> &node) const
  {
    return node ? node->incl_height : 0;
  }

  void update(IntervalNode *node)
  {
    node->incl_height =
        1 + std::max(incl_height(node->left), incl_height(node->right));
    node->max_end  = node->interval.end;
    node->max_size = node->interval.end - node->interval.start + 1;

    if (node->left)
    {
      node->max_end  = std::max(node->max_end, node->left->max_end);
      node->max_size = std::max(node->max_size, node->left->max_size);
    }
    if (node->right)
    {
      node->max_end  = std::max(node->max_end, node->right->max_end);
      node->max_size = std::max(node->max_size, node->right->max_size);
    }
  }

  std::unique_ptr<IntervalNode> rotate_right(std::unique_ptr<IntervalNode> y)
  {
    auto x   = std::move(y->left);
    y->left  = std::move(x->right);
    x->right = std::move(y);
    update(x->right.get());
    update(x.get());
    return x;
  }

  std::unique_ptr<IntervalNode> rotate_left(std::unique_ptr<IntervalNode> x)
  {
    auto y   = std::move(x->right);
    x->right = std::move(y->left);
    y->left  = std::move(x);
    update(y->left.get());
    update(y.get());
    return y;
  }

  std::unique_ptr<IntervalNode> insert(std::unique_ptr<IntervalNode> node,
                                       const Interval &interval)
  {
    if (!node)
      return std::make_unique<IntervalNode>(interval);

    if (interval.start < node->interval.start)
      node->left = insert(std::move(node->left), interval);
    else
      node->right = insert(std::move(node->right), interval);

    update(node.get());
    int balance = incl_height(node->left) - incl_height(node->right);

    if (balance > 1)
    {
      if (interval.start >= node->left->interval.start)
        node->left = rotate_left(std::move(node->left));
      return rotate_right(std::move(node));
    }
    if (balance < -1)
    {
      if (interval.start < node->right->interval.start)
        node->right = rotate_right(std::move(node->right));
      return rotate_left(std::move(node));
    }
    return node;
  }

  std::unique_ptr<IntervalNode> delete_node(std::unique_ptr<IntervalNode> node,
                                            const Interval &target)
  {
    if (!node)
      return nullptr;

    if (target.start < node->interval.start)
      node->left = delete_node(std::move(node->left), target);
    else if (target.start > node->interval.start)
      node->right = delete_node(std::move(node->right), target);
    else
    {
      if (node->interval.end != target.end)
        node->right = delete_node(std::move(node->right), target);
      else
      {
        if (!node->left)
          return std::move(node->right);
        else if (!node->right)
          return std::move(node->left);
        else
        {
          IntervalNode *minNode = min_value_node(node->right.get());
          node->interval        = minNode->interval;
          node->right = delete_node(std::move(node->right), minNode->interval);
        }
      }
    }

    update(node.get());
    int balance = incl_height(node->left) - incl_height(node->right);

    if (balance > 1)
    {
      if (incl_height(node->left->left) >= incl_height(node->left->right))
        return rotate_right(std::move(node));
      else
      {
        node->left = rotate_left(std::move(node->left));
        return rotate_right(std::move(node));
      }
    }
    if (balance < -1)
    {
      if (incl_height(node->right->right) >= incl_height(node->right->left))
        return rotate_left(std::move(node));
      else
      {
        node->right = rotate_right(std::move(node->right));
        return rotate_left(std::move(node));
      }
    }
    return node;
  }

  IntervalNode *min_value_node(IntervalNode *node) const
  {
    while (node && node->left)
      node = node->left.get();
    return node;
  }

public:
  DisjointIntervalAVLTree()                                           = default;
  DisjointIntervalAVLTree(const DisjointIntervalAVLTree &)            = delete;
  DisjointIntervalAVLTree &operator=(const DisjointIntervalAVLTree &) = delete;

  void insert(int start, int end)
  {
    root = insert(std::move(root), Interval(start, end));
  }

  void remove(int start, int end)
  {
    root = delete_node(std::move(root), Interval(start, end));
  }

  Interval *interval_containing(int p) const
  {
    IntervalNode *current = root.get();
    while (current)
    {
      if (p >= current->interval.start && p <= current->interval.end)
        return &current->interval;
      if (current->left && p <= current->left->max_end)
        current = current->left.get();
      else
        current = current->right.get();
    }
    return nullptr;
  }

  Interval *largest_interval() const
  {
    IntervalNode *current = root.get();
    while (current)
    {
      if (current->left && current->left->max_size == current->max_size)
        current = current->left.get();
      else if (current->right && current->right->max_size == current->max_size)
        current = current->right.get();
      else
        return &current->interval;
    }
    return nullptr;
  }
};
