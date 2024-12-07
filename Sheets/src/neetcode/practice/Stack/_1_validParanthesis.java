package neetcode.practice.Stack;

import java.util.ArrayDeque;

class Solution {
  public boolean isValid(String s) {
    ArrayDeque<Character> stack = new ArrayDeque<>();
    for (char c : s.toCharArray()) {
      char value;
      switch (c) {
        case '(':
        case '[':
        case '{':
          stack.addLast(c);
          break;

        case ')':
          if (stack.size() == 0)
            return false;
          value = stack.removeLast();
          if (value != '(')
            return false;
          break;

        case ']':
          if (stack.size() == 0)
            return false;
          value = stack.removeLast();
          if (value != '[')
            return false;
          break;

        case '}':
          if (stack.size() == 0)
            return false;
          value = stack.removeLast();
          if (value != '{')
            return false;
          break;

        default:
          return false;
      }
    }
    return stack.size() == 0;
  }
}