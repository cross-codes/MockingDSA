package neetcode.practice.Binary_Search;

class Solution {
  public boolean searchMatrix(int[][] matrix, int target) {
    int numberOfColumns = matrix[0].length, numberOfRows = matrix.length;
    int low = 0, high = (numberOfRows * numberOfColumns) - 1;
    while (low <= high) {
      int mid = low + high >> 1;
      if (matrix[mid / numberOfColumns][mid % numberOfColumns] > target)
        high = mid - 1;
      else if (matrix[mid / numberOfColumns][mid % numberOfColumns] < target)
        low = mid + 1;
      else
        return true;
    }
    return false;
  }
}