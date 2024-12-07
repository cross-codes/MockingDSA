package neetcode.practice.Stack;

import java.util.ArrayDeque;

class Solution {
  public int evalRPN(String[] tokens) {
    ArrayDeque<String> stack = new ArrayDeque<>();
    for (String token : tokens) {
      int operand1, operand2;
      switch (token) {
        case "+":
          operand1 = Integer.parseInt(stack.removeLast());
          operand2 = Integer.parseInt(stack.removeLast());
          stack.addLast(String.valueOf(operand1 + operand2));
          break;
        case "-":
          operand1 = Integer.parseInt(stack.removeLast());
          operand2 = Integer.parseInt(stack.removeLast());
          stack.addLast(String.valueOf(operand2 - operand1));
          break;

        case "*":
          operand1 = Integer.parseInt(stack.removeLast());
          operand2 = Integer.parseInt(stack.removeLast());
          stack.addLast(String.valueOf(operand1 * operand2));
          break;

        case "/":
          operand1 = Integer.parseInt(stack.removeLast());
          operand2 = Integer.parseInt(stack.removeLast());
          stack.addLast(String.valueOf(operand2 / operand1));
          break;

        default:
          stack.addLast(token);
      }
    }
    return Integer.parseInt(stack.peek());
  }
}