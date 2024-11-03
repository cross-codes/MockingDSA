import java.util.Arrays;

public interface Debug {
  public final boolean isLocal = getLocal();

  public static boolean getLocal() {
    try {
      return System.getProperty("LOCAL") != null;
    } catch (SecurityException ex) {
      return false;
    }
  }

  public static <T> String convStr(T t) {
    if (t == null)
      return "null";
    if (t instanceof Iterable)
      return convStr((Iterable<?>) t);
    else if (t instanceof int[]) {
      String s = Arrays.toString((int[]) t);
      return "{" + s.substring(1, s.length() - 1) + "}";
    } else if (t instanceof long[]) {
      String s = Arrays.toString((long[]) t);
      return "{" + s.substring(1, s.length() - 1) + "}";
    } else if (t instanceof char[]) {
      String s = Arrays.toString((char[]) t);
      return "{" + s.substring(1, s.length() - 1) + "}";
    } else if (t instanceof double[]) {
      String s = Arrays.toString((double[]) t);
      return "{" + s.substring(1, s.length() - 1) + "}";
    } else if (t instanceof boolean[]) {
      String s = Arrays.toString((boolean[]) t);
      return "{" + s.substring(1, s.length() - 1) + "}";
    } else if (t instanceof Object[])
      return convStr((Object[]) t);
    return t.toString();
  }

  public static <T> String convStr(T[] arr) {
    StringBuilder ret = new StringBuilder();
    ret.append("{");
    boolean first = true;
    for (T t : arr) {
      if (!first)
        ret.append(", ");
      first = false;
      ret.append(convStr(t));
    }
    ret.append("}");
    return ret.toString();
  }

  public static <T> String convStr(Iterable<T> iter) {
    StringBuilder ret = new StringBuilder();
    ret.append("{");
    boolean first = true;
    for (T t : iter) {
      if (!first)
        ret.append(", ");
      first = false;
      ret.append(convStr(t));
    }
    ret.append("}");
    return ret.toString();
  }

  public static void print(Object... VAR_ARGS) {
    if (isLocal) {
      System.err.print("Line #" + Thread.currentThread().getStackTrace()[2].getLineNumber() + ": [");
      for (int i = 0; i < VAR_ARGS.length; i++) {
        if (i != 0)
          System.err.print(", ");
        System.err.print(convStr(VAR_ARGS[i]));
      }
      System.err.println("]");
    }
  }
}