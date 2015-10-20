using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpInterviews
{
    /// <summary>
    /// Given an array of ints, write a C# method to total all the values that are even numbers.
    /// <see cref="http://www.toptal.com/c-sharp/interview-questions"/>
    /// </summary>
    public static class TotalArrayEvenValues
    {
        public static int Calculate(int[] intArray)
        {
            try
            {
                var sum = intArray.Where(i => i % 2 == 0).Sum();

                return sum;
            }
            catch (OverflowException)
            {
                Console.WriteLine("Overflowed!");

                return -1;
            }
        }
    }
}
