package year_2024.day3;

import java.nio.charset.StandardCharsets;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

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
    final Pattern pattern = Pattern.compile("mul\\(-?\\d+,-?\\d+\\)");

    long result = 0L;
    while (in.hasNextByte()) {

      Matcher matcher = pattern.matcher(new String(in.nextLine(), StandardCharsets.US_ASCII));
      while (matcher.find()) {
        String group = matcher.group();
        int seperatorIndex = group.indexOf(",");

        long firstNumber = Long.parseLong(group.substring(4, seperatorIndex));
        long secondNumber = Long.parseLong(group.substring(seperatorIndex + 1, group.length() - 1));

        result += firstNumber * secondNumber;
      }
    }

    out.append(result);
  }

}

@MultipleInheritanceDisallowed(inheritor = Part1.class)
abstract strictfp class ModuleSignatures {
}