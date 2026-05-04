#include <algorithm>
#include <memory>

template <typename Satellite> struct AugmentedAVLTree
{
protected:
  struct Node
  {
    Satellite data;
    int height;

    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    Node(const Satellite &k) : data(k), height(1)
    {
    }

    virtual ~Node() = default;
  };

  using NodePtr = std::unique_ptr<Node>;
  NodePtr root;

  auto height(const NodePtr &node) const -> int
  {
    return node != nullptr ? node->height : 0;
  }

  void update_node(Node *node)
  {
    node->height = 1 + std::max(height(node->left), height(node->right));
    //...
  }

  auto rotate_right(NodePtr y) -> NodePtr
  {
    auto x   = std::move(y->left);
    y->left  = std::move(x->right);
    x->right = std::move(y);
    update_node(x->right.get());
    update_node(x.get());
    return x;
  }

  auto rotate_left(NodePtr x) -> NodePtr
  {
    auto y   = std::move(x->right);
    x->right = std::move(y->left);
    y->left  = std::move(x);
    update_node(y->left.get());
    update_node(y.get());
    return y;
  }

  auto balance_factor(const Node *node) const -> int
  {
    return height(node->left) - height(node->right);
  }

  auto insert(NodePtr node, const Satellite &key) -> NodePtr
  {
    if (node == nullptr)
      return std::make_unique<Node>(key);

    if (key < node->data)
      node->left = insert(std::move(node->left), key);

    else if (key > node->data)
      node->right = insert(std::move(node->right), key);

    else
      return node;

    update_node(node.get());
    const int balance = balance_factor(node.get());

    if (balance > 1)
    {
      return key < node->left->key
                 ? rotate_right(std::move(node))
                 : (node->left = rotate_left(std::move(node->left)),
                    rotate_right(std::move(node)));
    }
    if (balance < -1)
    {
      return key > node->right->key
                 ? rotate_left(std::move(node))
                 : (node->right = rotate_right(std::move(node->right)),
                    rotate_left(std::move(node)));
    }
    return node;
  }

  auto delete_node(NodePtr node, const Satellite &key) -> NodePtr
  {
    if (node == nullptr)
      return nullptr;

    if (key < node->data)
      node->left = delete_node(std::move(node->left), key);
    else if (key > node->data)
      node->right = delete_node(std::move(node->right), key);
    else
    {
      if (!node->left)
        return std::move(node->right);
      if (!node->right)
        return std::move(node->left);

      Node *successor = node->right.get();
      while (successor->left)
        successor = successor->left.get();

      node->data  = successor->data;
      node->right = delete_node(std::move(node->right), successor->data);
    }

    update_node(node.get());
    const int balance = balance_factor(node.get());

    if (balance > 1)
      return balance_factor(node->left.get()) >= 0
                 ? rotate_right(std::move(node))
                 : (node->left = rotate_left(std::move(node->left)),
                    rotate_right(std::move(node)));

    if (balance < -1)
      return balance_factor(node->right.get()) <= 0
                 ? rotate_left(std::move(node))
                 : (node->right = rotate_right(std::move(node->right)),
                    rotate_left(std::move(node)));

    return node;
  }

public:
  void insert(const Satellite &key)
  {
    root = insert(std::move(root), key);
  }

  void remove(const Satellite &key)
  {
    root = delete_node(std::move(root), key);
  }

  auto contains(const Satellite &key) const -> bool
  {
    const Node *current = root.get();
    while (current != nullptr)
    {
      if (key < current->data)
        current = current->left.get();
      else if (key > current->data)
        current = current->right.get();
      else
        return true;
    }
    return false;
  }

  virtual ~AugmentedAVLTree() = default;
};
