using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using CSharpInterviews;

namespace CSharpInterviewTests
{
    [TestClass]
    public class TotalArrayEvenValuesTest
    {
        [TestMethod]
        public void NomalValues()
        {
            // Prepare
            int[] inputArray = new int[5] { 1, 2, 3, 4, 5 };
            int expectedResult = 6;

            // Act
            int actualResult = TotalArrayEvenValues.Calculate(inputArray);

            // Assert
            Assert.AreEqual(expectedResult, actualResult);
        }

        [TestMethod]
        public void OverflowTests()
        {
            // Prepare
            int[] inputArray = new int[5] { int.MaxValue, int.MaxValue - 1, int.MaxValue - 2, int.MaxValue - 3, int.MaxValue - 4 };

            // If overflowed, return -1.
            int expectedValue = -1;

            // Act
            int actualValue = TotalArrayEvenValues.Calculate(inputArray);

            // Assert
            // int.MinValue means overlfow.
            Assert.AreEqual(expectedValue, actualValue);
        }
    }
}
