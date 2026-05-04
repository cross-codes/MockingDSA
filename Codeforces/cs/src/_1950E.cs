using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Collections.Generic;
using System.Linq;
using Evermore.IO;

namespace _1950E
{
    public class _1950E
    {
        private static string GetSourceFilePath([CallerFilePath] string path = "") => path;
        private static readonly StandardInputReader input = new();
        private static readonly StandardOutputWriter output = new();

        public static void Main(string[] args)
        {
            SourceExpander.Expander.Expand(GetSourceFilePath(), Path.Combine(Directory.GetCurrentDirectory(), "_1950E.txt"), false);
            int t = input.NextInt();
            for (int _case = 1; _case <= t; _case++)
            {
                SolveCase(_case);
            }
            output.Flush();
        }

        private static void SolveCase(int _case)
        {
            int n = input.NextInt();
            string str = input.NextStr();
            char[] cha = str.ToCharArray();
            char first = cha[0];

            List<int> div = new();
            for (int i = 1; i * i <= n; i++)
            {
                if (n % i == 0)
                {
                    div.Add(i);
                    if (n != i * i)
                    {
                        div.Add(n / i);
                    }
                }
            }

            div.Sort();

            bool Ok(int k)
            {
                int numDiff = 0;
                for (int s = k; s < n; s += k)
                {
                    for (int i = 0; i < k; i++)
                    {
                        if (str[i] != str[s + i])
                        {
                            numDiff++;
                            if (numDiff > 1)
                            {
                                goto chk2;
                            }
                        }
                    }
                }

                return true;


            chk2:
                numDiff = 0;
                for (int s = 2 * k; s < n; s += k)
                {
                    for (int i = 0; i < k; i++)
                    {
                        if (str[k + i] != str[s + i])
                        {
                            return false;
                        }
                    }
                }

                int pd = 0;
                for (int i = 0; i < k; i++)
                {
                    if (str[i] != str[k + i])
                    {
                        pd++;
                        if (pd > 1) return false;
                    }
                }

                return true;
            }

            foreach (int k in div)
            {
                if (Ok(k))
                {
                    output.Append(k).AppendNewLine();
                    return;
                }
            }

        }
    }
}
