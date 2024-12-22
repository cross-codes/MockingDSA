package year_2024.day6;

import java.nio.charset.StandardCharsets;
import java.util.ArrayList;

import commons.annotations.Launchable;
import commons.annotations.MultipleInheritanceDisallowed;
import commons.classes.Debug;
import commons.classes.StandardInputReader;
import commons.classes.StandardOutputWriter;

@Launchable(author = "Cross", hostname = "inspiron", judge = "Advent of Code")
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
    int caretRow = -1, caretColumn = -1;
    Directions direction = null;

    ArrayList<ArrayList<Character>> map = new ArrayList<>();
    while (in.hasNextByte()) {
      String row = new String(in.nextLine(), StandardCharsets.US_ASCII);
      ArrayList<Character> rowList = new ArrayList<>();
      for (char c : row.toCharArray()) {
        rowList.add(c);

        switch (c) {
          case '^':
            caretRow = map.size();
            caretColumn = rowList.size() - 1;
            direction = Directions.UP;
            break;

          case '>':
            caretRow = map.size();
            caretColumn = rowList.size() - 1;
            direction = Directions.RIGHT;
            break;

          case '<':
            caretRow = map.size();
            caretColumn = rowList.size() - 1;
            direction = Directions.LEFT;
            break;

          case 'v':
            caretRow = map.size();
            caretColumn = rowList.size() - 1;
            direction = Directions.DOWN;
            break;

          default:
            break;
        }

      }
      map.add(rowList);
    }

    long numberOfDisinctPositions = this.simulateGrid(map, caretRow, caretColumn,
        direction);
    out.append(numberOfDisinctPositions);
  }

  @Override
  public long simulateGrid(ArrayList<ArrayList<Character>> map, int caretRow,
      int caretColumn, Directions direction) {
    int numberOfRows = map.size(), numberOfColumns = map.get(0).size();
    int i = caretRow, j = caretColumn;

    long result = 0L;
    while (true) {
      if (i < 0 || i >= numberOfRows || j < 0 || j >= numberOfColumns)
        break;

      switch (direction) {
        case UP:
          if (map.get(i).get(j) == '.' || map.get(i).get(j) == '^') {
            map.get(i).set(j, 'X');
            result++;
            i--;
          } else if (map.get(i).get(j) == 'X') {
            i--;
          } else {
            i++;
            direction = this.rotateClockwise(direction);
          }

          break;

        case DOWN:
          if (map.get(i).get(j) == '.' || map.get(i).get(j) == 'v') {
            map.get(i).set(j, 'X');
            result++;
            i++;
          } else if (map.get(i).get(j) == 'X') {
            i++;
          } else {
            i--;
            direction = this.rotateClockwise(direction);
          }

          break;

        case LEFT:
          if (map.get(i).get(j) == '.' || map.get(i).get(j) == '<') {
            map.get(i).set(j, 'X');
            result++;
            j--;
          } else if (map.get(i).get(j) == 'X') {
            j--;
          } else {
            j++;
            direction = this.rotateClockwise(direction);
          }

          break;

        case RIGHT:
          if (map.get(i).get(j) == '.' || map.get(i).get(j) == '>') {
            map.get(i).set(j, 'X');
            result++;
            j++;
          } else if (map.get(i).get(j) == 'X') {
            j++;
          } else {
            j--;
            direction = this.rotateClockwise(direction);
          }

          break;

        default:
          throw new RuntimeException();
      }

    }

    return result;
  }

  @Override
  public Directions rotateClockwise(Directions currentDirection) {
    switch (currentDirection) {
      case UP:
        return Directions.RIGHT;

      case RIGHT:
        return Directions.DOWN;

      case DOWN:
        return Directions.LEFT;

      case LEFT:
        return Directions.UP;

      default:
        return null;
    }
  }

}

@MultipleInheritanceDisallowed(inheritor = Part2.class)
abstract strictfp class ModuleSignatures {
  abstract public long simulateGrid(ArrayList<ArrayList<Character>> map, int caretRow,
      int caretColumn, Directions direction);

  abstract public Directions rotateClockwise(Directions currentDirection);
}