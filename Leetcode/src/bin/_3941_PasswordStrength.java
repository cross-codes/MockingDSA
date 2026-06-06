class Solution {
  public int passwordStrength(String password) {
    String map = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$";

    CharToIntFunction points = (c) -> {
      if (Character.isLowerCase(c))
        return 1;
      else if (Character.isUpperCase(c))
        return 2;
      else if (Character.isDigit(c))
        return 3;
      else
        return 5;
    };

    boolean[] visited = new boolean[map.length()];
    int res = 0;
    for (char c : password.toCharArray()) {
      int idx = map.indexOf(c);
      if (!visited[idx]) {
        res += points.of(c);
        visited[idx] = true;
      }
    }

    return res;
  }
}

@FunctionalInterface
interface CharToIntFunction {
  int of(char c);
}
