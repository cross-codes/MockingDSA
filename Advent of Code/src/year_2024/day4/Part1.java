package year_2024.day4;

import java.util.ArrayList;

import commons.annotations.Launchable;
import commons.annotations.MultipleInheritanceDisallowed;
import commons.classes.Debug;
import commons.classes.StandardInputReader;
import commons.classes.StandardOutputWriter;

@Launchable(author = "cross", hostname = "inspiron", judge = "Advent of Code")
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
    ArrayList<byte[]> grid = new ArrayList<>();

    while (in.hasNextByte()) {
      grid.add(in.nextLine());
    }

    long totalOccurences = 0L;

    totalOccurences += this.findRightwardOccurences(grid, "XMAS");
    totalOccurences += this.findRightwardOccurences(grid, "SAMX");

    totalOccurences += this.findDownwardOccurences(grid, "XMAS");
    totalOccurences += this.findDownwardOccurences(grid, "SAMX");

    totalOccurences += this.findDiagonalUpLeftOccurences(grid, "XMAS");
    totalOccurences += this.findDiagonalUpLeftOccurences(grid, "SAMX");

    totalOccurences += this.findDiagonalUpRightOccurences(grid, "XMAS");
    totalOccurences += this.findDiagonalUpRightOccurences(grid, "SAMX");

    out.append(totalOccurences);
  }

  @Override
  public long findRightwardOccurences(ArrayList<byte[]> grid,
      String pattern) {
    long occurences = 0L;
    int rowLength = grid.get(0).length;
    int colLength = grid.size();
    int patternLength = pattern.length();

    for (int i = 0; i < colLength; i++) {
      traversal: for (int j = 0; j <= rowLength - patternLength; j++) {
        if ((char) grid.get(i)[j] == pattern.charAt(0)) {
          for (int k = 1; k < patternLength; k++) {
            if ((char) grid.get(i)[j + k] != pattern.charAt(k))
              continue traversal;
          }
          occurences++;
        }
      }
    }

    return occurences;
  }

  @Override
  public long findDownwardOccurences(ArrayList<byte[]> grid,
      String pattern) {
    long occurences = 0L;
    int rowLength = grid.get(0).length;
    int colLength = grid.size();
    int patternLength = pattern.length();

    for (int i = 0; i <= colLength - patternLength; i++) {
      traversal: for (int j = 0; j < rowLength; j++) {
        if ((char) grid.get(i)[j] == pattern.charAt(0)) {
          for (int k = 1; k < patternLength; k++) {
            if ((char) grid.get(i + k)[j] != pattern.charAt(k))
              continue traversal;
          }
          occurences++;
        }
      }
    }

    return occurences;
  }

  @Override
  public long findDiagonalUpRightOccurences(ArrayList<byte[]> grid,
      String pattern) {
    long occurences = 0L;
    int rowLength = grid.get(0).length;
    int colLength = grid.size();
    int patternLength = pattern.length();

    for (int i = patternLength - 1; i < colLength; i++) {
      traversal: for (int j = 0; j <= rowLength - patternLength; j++) {
        if ((char) grid.get(i)[j] == pattern.charAt(0)) {
          for (int k = 1; k < patternLength; k++) {
            if ((char) grid.get(i - k)[j + k] != pattern.charAt(k))
              continue traversal;
          }
          occurences++;
        }
      }
    }

    return occurences;
  }

  @Override
  public long findDiagonalUpLeftOccurences(ArrayList<byte[]> grid,
      String pattern) {
    long occurences = 0L;
    int rowLength = grid.get(0).length;
    int colLength = grid.size();
    int patternLength = pattern.length();

    for (int i = patternLength - 1; i < colLength; i++) {
      traversal: for (int j = patternLength - 1; j < rowLength; j++) {
        if ((char) grid.get(i)[j] == pattern.charAt(0)) {
          for (int k = 1; k < patternLength; k++) {
            if ((char) grid.get(i - k)[j - k] != pattern.charAt(k))
              continue traversal;
          }
          occurences++;
        }
      }
    }

    return occurences;
  }

}

@MultipleInheritanceDisallowed(inheritor = Part1.class)
abstract strictfp class ModuleSignatures {
  abstract public long findRightwardOccurences(ArrayList<byte[]> grid,
      String pattern);

  abstract public long findDownwardOccurences(ArrayList<byte[]> grid,
      String pattern);

  abstract public long findDiagonalUpRightOccurences(ArrayList<byte[]> grid,
      String pattern);

  abstract public long findDiagonalUpLeftOccurences(ArrayList<byte[]> grid,
      String pattern);
}