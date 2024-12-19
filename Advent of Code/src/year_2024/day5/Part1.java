package year_2024.day5;

import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.HashSet;
import java.util.stream.Stream;

import commons.annotations.Launchable;
import commons.annotations.MultipleInheritanceDisallowed;
import commons.classes.Debug;
import commons.classes.StandardInputReader;
import commons.classes.StandardOutputWriter;

@Launchable(author = "cross", hostname = "inspiron", judge = "Codeforces")
public class Part1 extends ModuleSignatures implements Runnable {

  private final StandardInputReader in = new StandardInputReader();
  private final StandardOutputWriter out = new StandardOutputWriter();
  @SuppressWarnings("unused")
  private final Debug dbg = Debug.getInstance();

  @Override
  public void run() {
    this.consolidateOutput();
    this.out.flush();
  }

  public static void main(String... args) {
    new Thread(null, new Part1(), "LaunchableDriver", 1048576L).start();
  }

  private void consolidateOutput() {
    HashMap<Integer, HashSet<Integer>> pageBeforeMap = new HashMap<>();
    long result = 0L;

    while (in.hasNextByte()) {
      String input = new String(in.nextLine(), StandardCharsets.US_ASCII);
      if (input.contains("|")) {
        int[] pages = Stream.of(input.split("\\|")).mapToInt(Integer::parseInt).toArray();
        pageBeforeMap.computeIfAbsent(pages[0], k -> new HashSet<>()).add(pages[1]);
      } else if (!input.isEmpty()) {
        int[] sequence = Stream.of(input.split(",")).mapToInt(Integer::parseInt).toArray();
        if (this.isValidSequence(sequence, pageBeforeMap)) {
          result += (long) sequence[sequence.length / 2];
        }
      }
    }

    out.append(result);
  }

  @Override
  public boolean isValidSequence(int[] sequence,
      HashMap<Integer, HashSet<Integer>> ruleset) {
    int n = sequence.length;

    for (int i = 0; i < n; i++) {
      int page = sequence[i];
      HashSet<Integer> pagesInFront = ruleset.get(page);
      if (pagesInFront == null)
        continue;
      for (int j = 0; j < i; j++) {
        if (pagesInFront.contains(sequence[j]))
          return false;
      }
      for (int j = i + 1; j < n; j++) {
        if (!pagesInFront.contains(sequence[j]))
          return false;
      }
    }

    return true;
  }

}

@MultipleInheritanceDisallowed(inheritor = Part1.class)
abstract strictfp class ModuleSignatures {
  abstract public boolean isValidSequence(int[] sequence,
      HashMap<Integer, HashSet<Integer>> ruleset);
}