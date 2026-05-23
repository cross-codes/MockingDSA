package collections;

class TrieNode {
  private int alphabetSize = 26;
  public TrieNode[] children = new TrieNode[this.alphabetSize];
  public boolean isEndOfWord = false;
}

public class RadixTree {
  private TrieNode root;
  private char firstLetter = 'a';

  public RadixTree() {
    this.root = new TrieNode();
  }

  public void insert(String word) {
    TrieNode x = this.root;
    for (char c : word.toCharArray()) {
      if (x.children[c - this.firstLetter] == null) {
        x.children[c - this.firstLetter] = new TrieNode();
      }

      x = x.children[c - this.firstLetter];
    }

    x.isEndOfWord = true;
  }

  public boolean containsWordOrPrefix(String word, boolean prefix) {
    TrieNode p = this.root;
    for (char c : word.toCharArray()) {
      if (p.children[c - this.firstLetter] == null) {
        return false;
      }

      p = p.children[c - this.firstLetter];
    }

    if (!prefix) {
      return p.isEndOfWord;
    }

    return true;
  }
}
