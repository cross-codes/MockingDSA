#include <array>
#include <memory>
#include <string>

struct TrieNode
{
public:
  std::array<std::unique_ptr<TrieNode>, 26> children;
  bool is_end_of_word{};
};

struct PrefixTree
{
private:
  std::unique_ptr<TrieNode> root_;

public:
  PrefixTree() : root_{std::make_unique<TrieNode>()} {};

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

  bool search(const std::string &word, bool prefix = false)
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

  bool startsWith(const std::string &prefix)
  {
    return search(prefix, true);
  }
};
