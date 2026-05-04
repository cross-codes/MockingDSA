import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

class Solution {
  public String sortVowels(String s) {
    int n = s.length();

    var freq = new IntOrderedPair[26];
    for (int i = 0; i < 26; i++) {
      freq[i] = new IntOrderedPair(0, -1);
    }

    ArrayList<Character> vowels = new ArrayList<>(List.of('a', 'e', 'i', 'o', 'u'));
    ArrayList<Character> inVowels = new ArrayList<>();
    for (int i = 0; i < n; i++) {
      char c = s.charAt(i);
      freq[c - 'a'].first += 1;
      if (freq[c - 'a'].second == -1) {
        freq[c - 'a'].second = i;
      }

      if (vowels.contains(c)) {
        inVowels.add(c);
      }
    }

    inVowels.sort((c1, c2) -> {
      int f1 = freq[c1 - 'a'].first, f2 = freq[c2 - 'a'].first;
      int i1 = freq[c1 - 'a'].second, i2 = freq[c2 - 'a'].second;
      if (f1 == f2) {
        return Integer.compare(i1, i2);
      }

      return Integer.compare(f2, f1);
    });

    int vidx = 0;
    var sb = new StringBuilder();
    for (char c : s.toCharArray()) {
      if (vowels.contains(c)) {
        sb.append(inVowels.get(vidx));
        vidx += 1;
      } else {
        sb.append(c);
      }
    }

    return sb.toString();
  }
}

class IntOrderedPair implements Comparable<IntOrderedPair> {

  public int first;
  public int second;

  public IntOrderedPair(int first, int second) {
    this.first = first;
    this.second = second;
  }

  @Override
  public int compareTo(IntOrderedPair other) {
    int cmp = Integer.compare(this.first, other.first);
    if (cmp == 0)
      return Integer.compare(this.second, other.second);

    return cmp;
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj)
      return true;
    if (!(obj instanceof IntOrderedPair))
      return false;
    IntOrderedPair pair = (IntOrderedPair) obj;
    return this.first == pair.first && this.second == pair.second;
  }

  @Override
  public int hashCode() {
    return Objects.hash(this.first, this.second);
  }
}
