using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using CSharpInterviews;

namespace CSharpInterviewTests
{
    [TestClass]
    public class AsyncTaskOutputTest
    {
        [TestMethod]
        public void RunTest()
        {
            AsyncTaskOutput.Run();

            Assert.IsTrue(true);
        }
    }
}
