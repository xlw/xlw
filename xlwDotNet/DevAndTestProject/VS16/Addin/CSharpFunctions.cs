using System;
using System.IO;
using xlwDotNet;


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

        [ExcelOnOpen]
        public static void MyOpen()
        {
            XlwExcel.StatusBar.message = "YOYOYOYOYO";
           
        }

        [ExcelOnClose]
        public static void MyClose()
        {
            File.WriteAllText(@"C:\WorkSpace\xlw\xlwDotNet\DevAndTestProject\VS16\Addin\Debug\x64\net6.0\bye.txt", "BYE BYE");

        }


    }
}

