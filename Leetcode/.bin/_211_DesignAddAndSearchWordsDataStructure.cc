#include <array>
#include <memory>
#include <string>

struct TrieNode
{
public:
  std::array<std::shared_ptr<TrieNode>, 26> children;
  bool is_end_of_word{};
};

class WordDictionary
{
private:
  std::shared_ptr<TrieNode> root_;

  auto dfs_(const std::string &word, int index, std::shared_ptr<TrieNode> &node)
      -> bool
  {
    int n = static_cast<int>(word.size());
    if (index == n)
      return node->is_end_of_word;

    char c = word[index];
    if (c == '.')
    {
      bool found = false;
      for (std::shared_ptr<TrieNode> ptr : node->children)
        if (ptr != nullptr)
        {
          found = found || dfs_(word, index + 1, ptr);
          if (found)
            break;
        }

      return found;
    }
    else if (node->children[c - 'a'] == nullptr)
      return false;
    else
      return dfs_(word, index + 1, node->children[c - 'a']);
  }

public:
  WordDictionary() : root_{std::make_shared<TrieNode>()} {};

  void addWord(std::string word)
  {
    TrieNode *x = root_.get();
    for (const auto &c : word)
    {
      if (x->children[c - 'a'] == nullptr)
        x->children[c - 'a'] = std::make_shared<TrieNode>();

      x = x->children[c - 'a'].get();
    }

    x->is_end_of_word = true;
  }

  bool search(std::string word)
  {
    return true && dfs_(word, 0, root_);
  }
};
