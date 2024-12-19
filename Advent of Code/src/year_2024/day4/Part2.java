package year_2024.day4;

import java.util.ArrayList;

import commons.annotations.Launchable;
import commons.annotations.MultipleInheritanceDisallowed;
import commons.classes.Debug;
import commons.classes.StandardInputReader;
import commons.classes.StandardOutputWriter;

@Launchable(author = "cross", hostname = "inspiron", judge = "Codeforces")
public class Part2 extends ModuleSignatures implements Runnable {

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
    new Thread(null, new Part2(), "LaunchableDriver", 1048576L).start();
  }

  private void consolidateOutput() {
    ArrayList<byte[]> grid = new ArrayList<>();

    while (in.hasNextByte()) {
      grid.add(in.nextLine());
    }

    long occurences = 0L;

    occurences += this.findXPatternOccurences(grid, "MAS", "SAM");
    occurences += this.findXPatternOccurences(grid, "MAS", "MAS");
    occurences += this.findXPatternOccurences(grid, "SAM", "SAM");
    occurences += this.findXPatternOccurences(grid, "SAM", "MAS");

    out.append(occurences);
  }

  @Override
  public long findXPatternOccurences(ArrayList<byte[]> grid, String pattern,
      String secondPattern) {
    long occurences = 0L;
    int rowLength = grid.get(0).length;
    int colLength = grid.size();
    int patternLengths = pattern.length();

    for (int i = patternLengths - 1; i < colLength; i++) {
      traversal: for (int j = 0; j <= rowLength - patternLengths; j++) {
        if ((char) grid.get(i)[j] == pattern.charAt(0)
            && (char) grid.get(i)[j + 2] == secondPattern.charAt(0)) {
          for (int k = 1; k < patternLengths; k++) {
            if ((char) grid.get(i - k)[j + k] != pattern.charAt(k)) {
              continue traversal;
            }
          }
          for (int k = 1; k < patternLengths; k++) {
            if ((char) grid.get(i - k)[j + 2 - k] != secondPattern.charAt(k))
              continue traversal;
          }
          occurences++;
        }
      }
    }

    return occurences;
  }

}

@MultipleInheritanceDisallowed(inheritor = Part2.class)
abstract strictfp class ModuleSignatures {
  abstract public long findXPatternOccurences(ArrayList<byte[]> grid, String pattern,
      String secondPattern);
}