class Solution {
  public int longestCommonPrefix(int[] arr1, int[] arr2) {
    Generator prefixGenerator = (e) -> {
      String s = Integer.toString(e);
      int n = s.length();
      String[] res = new String[n];
      StringBuilder sb = new StringBuilder(n);
      for (int i = 0; i < n; i++) {
        sb.append(s.charAt(i));
        res[i] = sb.toString();
      }

      return res;
    };

    RadixTree radixTree = new RadixTree();

    for (int e: arr1) {
      String[] pref = prefixGenerator.generate(e);
      for (String p: pref) {
        radixTree.insert(p);
      }
    }

    int mx = 0;
    for (int e: arr2) {
      String[] pref = prefixGenerator.generate(e);
      for (String p: pref) {
        if (radixTree.containsWordOrPrefix(p, true)) {
          mx = Math.max(mx, p.length());
        }
      }
    }

    return mx;
  }
}

@FunctionalInterface
interface Generator {
  String[] generate(int e);
}

class TrieNode {
  private int alphabetSize = 10;
  public TrieNode[] children = new TrieNode[this.alphabetSize];
  public boolean isEndOfWord = false;
}

class RadixTree {
  private TrieNode root;
  private char firstLetter = '0';

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
