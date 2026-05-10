namespace _3917;

public class Solution
{
    public int[] CountOppositeParity(int[] nums)
    {
        int n = nums.Length;
        int[] answer = new int[n];
        for (int i = 0; i < n; i++)
        {
            int cnt = 0;
            for (int j = i + 1; j < n; j++)
            {
                if ((nums[i] % 2) != (nums[j] % 2))
                {
                    cnt += 1;
                }
            }

            answer[i] = cnt;
        }

        return answer;
    }
}
