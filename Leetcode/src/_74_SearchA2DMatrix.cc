#include <vector>

class Solution
{
public:
  bool searchMatrix(std::vector<std::vector<int>> &matrix, int target)
  {
    std::ptrdiff_t numberOfColumns = matrix[0].size(),
                   numberOfRows    = matrix.size();
    std::ptrdiff_t low = 0, high = (numberOfRows * numberOfColumns) - 1;
    while (low <= high)
    {
      std::size_t mid = (low + high) >> 1;
      if (matrix[mid / numberOfColumns][mid % numberOfColumns] > target)
        high = mid - 1;
      else if (matrix[mid / numberOfColumns][mid % numberOfColumns] < target)
        low = mid + 1;
      else
        return true;
    }
    return false;
  }
};
