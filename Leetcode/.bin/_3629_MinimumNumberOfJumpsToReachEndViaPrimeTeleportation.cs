namespace _3629;

using System.Diagnostics;

public class Solution
{
    public static bool[] sieve = new bool[1000001];

    static Solution()
    {
        sieve[0] = true;
        sieve[1] = true;
        for (int i = 2; i < 1000001; i++)
        {
            if (!sieve[i])
            {
                int x = i << 1;
                while (x < 1000001)
                {
                    sieve[x] = true;
                    x += i;
                }
            }
        }
    }

    public static bool IsPrime(int p)
    {
        return !sieve[p];
    }

    public int MinJumps(int[] nums)
    {
        int n = nums.Length;
        if (n == 1)
        {
            return 0;
        }

        if (n == 2)
        {
            return 1;
        }

        if (IsPrime(nums[0]) && nums[n - 1] % nums[0] == 0)
        {
            return 1;
        }

        if (IsPrime(nums[0]) && nums[n - 2] % nums[0] == 0)
        {
            return 2;
        }

        Dictionary<int, List<int>> primePos = new(); // prime -> pos
        for (int i = 0; i < n; i++)
        {
            int e = nums[i];
            if (IsPrime(e))
            {
                if (primePos.ContainsKey(e))
                {
                    primePos[e].Add(i);
                }
                else
                {
                    List<int> posList = new();
                    posList.Add(i);
                    primePos.Add(e, posList);
                }
            }
            else
            {
                for (int j = 2; j * j <= nums[i]; j++)
                {
                    if (e % j == 0)
                    {
                        if (primePos.ContainsKey(j))
                        {
                            primePos[j].Add(i);
                        }
                        else
                        {
                            List<int> primeList = new();
                            primeList.Add(i);
                            primePos.Add(j, primeList);
                        }
                    }
                    while (e % j == 0)
                    {
                        e /= j;
                    }
                }

                if (IsPrime(e))
                {
                    if (primePos.ContainsKey(e))
                    {
                        primePos[e].Add(i);
                    }
                    else
                    {
                        List<int> posList = new();
                        posList.Add(i);
                        primePos.Add(e, posList);
                    }

                }
            }
        }

        bool[] visited = new bool[n];
        int[] distance = new int[n];
        visited[0] = true;
        Queue<int> queue = new();
        queue.Enqueue(0);
        distance[0] = 0;
        while (queue.Count != 0)
        {
            int s = queue.Dequeue();
            if (s > 0 && !visited[s - 1])
            {
                visited[s - 1] = true;
                distance[s - 1] = distance[s] + 1;
                queue.Enqueue(s - 1);
            }

            if (s < n - 1 && !visited[s + 1])
            {
                visited[s + 1] = true;
                distance[s + 1] = distance[s] + 1;
                queue.Enqueue(s + 1);
                if (s + 1 == n - 1)
                {
                    return distance[n - 1];
                }
            }

            if (IsPrime(nums[s]) && primePos.ContainsKey(nums[s]))
            {
                foreach (var u in primePos[nums[s]])
                {
                    if (u != s && !visited[u])
                    {
                        visited[u] = true;
                        distance[u] = distance[s] + 1;
                        queue.Enqueue(u);
                        if (u == n - 1)
                        {
                            return distance[n - 1];
                        }
                    }
                }
            }
        }

        throw new UnreachableException();
    }
}
