#include <array>
#include <memory>
#include <string>

struct TrieNode
{
public:
  std::array<std::unique_ptr<TrieNode>, 26> children;
  bool is_end_of_word{};
};

struct RadixTree
{
private:
  std::unique_ptr<TrieNode> root_;

public:
  RadixTree() : root_{std::make_unique<TrieNode>()} {};

  void insert(const std::string &word)
  {
    TrieNode *x = root_.get();

    for (const char &c : word)
    {
      if (x->children[c - 'a'] == nullptr)
        x->children[c - 'a'] = std::make_unique<TrieNode>();

      x = x->children[c - 'a'].get();
    }

    x->is_end_of_word = true;
  }

  auto contains_word(const std::string &word, bool prefix = false) -> bool
  {
    TrieNode *p = root_.get();
    for (const char &c : word)
    {
      if (p->children[c - 'a'] == nullptr)
        return false;

      p = p->children[c - 'a'].get();
    }

    if (!prefix)
      return p->is_end_of_word;

    return true;
  }

  auto contains_prefix(const std::string &prefix) -> bool
  {
    return contains_word(prefix, true);
  }
};
