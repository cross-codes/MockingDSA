#include <array>
#include <memory>
#include <string>

class TrieNode
{
public:
  std::array<std::unique_ptr<TrieNode>, 26> child;
  bool isWord{};
};

class Trie
{
private:
  std::unique_ptr<TrieNode> root_;

public:
  Trie()
  {
    root_ = std::make_unique<TrieNode>();
  }

  void insert(const std::string &word)
  {
    TrieNode *x = root_.get();

    for (const char &c : word)
    {
      if (!x->child[c - 'a'])
        x->child[c - 'a'] = std::make_unique<TrieNode>();

      x = x->child[c - 'a'].get();
    }

    x->isWord = true;
  }

  bool search(const std::string &word, bool prefix = false)
  {
    TrieNode *p = root_.get();
    for (const char &c : word)
    {
      if (!p->child[c - 'a'])
      {
        return false;
      }

      p = p->child[c - 'a'].get();
    }

    if (!prefix)
      return p->isWord;

    return true;
  }

  bool startsWith(const std::string &prefix)
  {
    return search(prefix, true);
  }
};
