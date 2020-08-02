using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using xlwDotNet;
using xlwDotNet.xlwTypes;


namespace Example
{
    public class Class1
    {
     
        [ExcelExport("Hello World")]
        public static String HelloWorld()
        {
            return "Hello World!";
        }


        [ExcelExport("Bye World")]
        public static String byeWorld()
        {
            return "Bye World!";
        }

        [ExcelExport("Get's .NET Version")]
        public static String dotnetversion()
        {
            return System.Runtime.InteropServices.RuntimeInformation.FrameworkDescription;
        }


    }
}

