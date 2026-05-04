using System;
using System.IO;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using Evermore.IO;
using System.Linq;

namespace _2185E
{
    public class _2185E
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new();
        private static readonly StandardOutputWriter output = new();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "_2185E.txt"), false);
            int t = input.NextInt();
            for (int _case = 1; _case <= t; _case++)
            {
                SolveCase(_case);
            }
            output.Flush();
        }

        private static void SolveCase(int _case)
        {
            var (n, m, k) = (input.NextInt(), input.NextInt(), input.NextInt());
            int[] a = input.ReadIntegerArray(n), b = input.ReadIntegerArray(m);
            string instr = input.NextStr();

            SortedDictionary<int, int> distToTime = new();
            int curr = 0;
            for (int i = 0; i < k; i++)
            {
                curr += (instr[i] == 'L' ? -1 : 1);
                if (!distToTime.ContainsKey(curr))
                {
                    distToTime.Add(curr, i);
                }
            }
            var distances = distToTime.Keys.ToList();

            Array.Sort(b);
            SortedDictionary<int, int> destroyed = new();
            foreach (int e in a)
            {
                int rIdx = ~Array.BinarySearch(b, e);
                int ld = -1, nldIdx = -1;
                if (rIdx != 0)
                {
                    ld = b[rIdx - 1] - e;
                    nldIdx = distances.BinarySearch(ld);
                    if (nldIdx < 0)
                    {
                        nldIdx = ~nldIdx - 1;
                    }
                }

                int rd = -1, nrdIdx = -1;
                if (rIdx != m)
                {
                    rd = b[rIdx] - e;
                    nrdIdx = distances.BinarySearch(rd);
                    if (nrdIdx < 0)
                    {
                        nrdIdx = ~nrdIdx;
                    }

                    if (nrdIdx == distances.Count)
                    {
                        nrdIdx = -1;
                    }
                }

                int mta = Math.Min(nldIdx == -1 ? int.MaxValue : distToTime[distances[nldIdx]], nrdIdx == -1 ? int.MaxValue : distToTime[distances[nrdIdx]]);
                if (destroyed.ContainsKey(mta))
                {
                    destroyed[mta] += 1;
                }
                else
                {
                    destroyed.Add(mta, 1);
                }
            }

            var destTimes = destroyed.Keys.ToList();
            int tot = n, dIdx = 0;
            for (int i = 0; i < k; i++)
            {
                if (dIdx < destTimes.Count && i == destTimes[dIdx])
                {
                    tot -= destroyed[destTimes[dIdx]];
                    dIdx += 1;
                }

                output.Append(tot).Append(" ");
            }

            output.AppendNewLine();
        }
    }
}
