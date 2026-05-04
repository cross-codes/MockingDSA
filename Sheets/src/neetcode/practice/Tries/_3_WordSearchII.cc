#include <array>
#include <memory>
#include <string>
#include <vector>

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

class Solution
{
private:
  RadixTree trie_{};

  void add_words_to_trie_(std::vector<std::vector<char>> &board,
                          std::string current_word, int x, int y,
                          std::array<std::array<bool, 12>, 12> &visited)
  {
    long n = board.size(), m = board[0].size();
    if (x < 0 || y < 0 || y >= n || x >= m || visited[y][x])
      return;

    visited[y][x] = true;
    current_word += board[y][x];
    trie_.insert(current_word);
    add_words_to_trie_(board, current_word, x + 1, y, visited);
    add_words_to_trie_(board, current_word, x, y + 1, visited);
    add_words_to_trie_(board, current_word, x - 1, y, visited);
    add_words_to_trie_(board, current_word, x, y - 1, visited);
    visited[y][x] = false;
  }

  void reset_array_(std::array<std::array<bool, 12>, 12> &array)
  {
    for (auto &arr : array)
      std::fill(arr.begin(), arr.end(), false);
  }

public:
  std::vector<std::string> findWords(std::vector<std::vector<char>> &board,
                                     std::vector<std::string> &words)
  {
    long n = board.size(), m = board[0].size();
    std::array<std::array<bool, 12>, 12> visited;
    for (auto &array : visited)
      std::fill(array.begin(), array.end(), false);

    for (int y = 0; y < n; y++)
      for (int x = 0; x < m; x++)
      {
        std::string empty{};
        add_words_to_trie_(board, empty, x, y, visited);
        reset_array_(visited);
      }

    std::vector<std::string> res{};
    for (const auto &word : words)
    {
      if (trie_.contains_word(word))
        res.push_back(word);
    }

    return res;
  }
};
