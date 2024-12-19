package year_2024.day2;

import java.nio.charset.StandardCharsets;

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
    int numberOfSafeLevels = 0;

    iter: while (in.hasNextByte()) {
      String[] stream = new String(in.nextLine(), StandardCharsets.US_ASCII).split(" ");
      if (stream.length == 1) {
        numberOfSafeLevels++;
        continue;
      }

      boolean strictlyIncreasingStream = Integer.parseInt(stream[0]) < Integer.parseInt(stream[1]);
      for (int i = 1; i < stream.length; i++) {
        int first = Integer.parseInt(stream[i - 1]);
        int second = Integer.parseInt(stream[i]);
        if (strictlyIncreasingStream) {
          if (second - first > 3 || second - first <= 0)
            continue iter;
        } else {
          if (first - second > 3 || first - second <= 0)
            continue iter;
        }
      }

      numberOfSafeLevels++;
    }

    out.append(numberOfSafeLevels);
  }

}

@MultipleInheritanceDisallowed(inheritor = Part1.class)
abstract strictfp class ModuleSignatures {
}
