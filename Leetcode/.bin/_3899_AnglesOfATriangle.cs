namespace _3899;

using System.Linq;

public class Solution
{
    private static double EPS = 1e-5;

    public double[] InternalAngles(int[] sides)
    {
        var (a, b, c) = (sides[0], sides[1], sides[2]);
        var (aa, bb, cc) = (a * a, b * b, c * c);

        double[] angles = new double[3];
        angles[0] = Math.Acos((cc - aa - bb) / -(2.0 * a * b));
        angles[1] = Math.Acos((bb - cc - aa) / -(2.0 * a * c));
        angles[2] = Math.Acos((aa - bb - cc) / -(2.0 * b * c));
        Array.Sort(angles);

        double[] res = angles.Select(x => x * 180 / Math.PI).ToArray();
        bool bad = false;
        foreach (double d in res)
        {
            if (d < EPS || double.IsNaN(d))
            {
                bad = true;
            }
        }
        if (bad || Math.Abs(res.Sum() - 180.0) > EPS)
        {
            return Array.Empty<double>();
        }
        else
        {
            return res;
        }
    }
}
