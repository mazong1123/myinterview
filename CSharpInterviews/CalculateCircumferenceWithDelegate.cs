using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpInterviews
{
    /// <summary>
    /// Given an instance circle of the following class,
    /// write code to calculate the circumference of the circle, without modifying the Circle class itself.
    /// <see cref="http://www.toptal.com/c-sharp/interview-questions"/>
    /// </summary>
    public sealed class Circle
    {
        private double radius;

        public double Calculate(Func<double, double> op)
        {
            return op(radius);
        }
    }

    /// <summary>
    /// Write code to calculate the circumference of the circle, without modifying the Circle class itself.
    /// </summary>
    public static class CalculateCircumferenceWithDelegate
    {
        public static void Calculate()
        {
            var circle = new Circle();
            double result = circle.Calculate((double r) => {
                return 2 * Math.PI * r;
            });

            // Anwsers from the site is following. I prefer my solution for good reading in my opinion.
            circle.Calculate(r => 2 * Math.PI * r);

            Console.WriteLine(result);
        }
    }
}
