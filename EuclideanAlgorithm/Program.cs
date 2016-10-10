using System;
using System.Collections.Generic;
using System.Text;

namespace EuclideanAlgorithm
{
    class Program
    {
        static void Main(string[] args)
        {
            int first = 1020;
            int second = 60;

            int commonDivisor = GetCommonDivisor(first, second);

            Console.WriteLine(commonDivisor);

            Console.ReadLine();
        }

        static int GetCommonDivisor(int first, int second)
        {
            int big = first;
            int small = second;

            if (big < small)
            {
                big = second;
                small = first;
            }

            if (big % small == 0)
            {
                return small;
            }

            int newResult = big % small;

            return GetCommonDivisor(newResult, small);
        }
    }
}
