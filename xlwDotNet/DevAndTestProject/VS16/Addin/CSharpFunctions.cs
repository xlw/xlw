using System;
using System.IO;
using System.Linq;
using xlwDotNet;


namespace Example
{
    public class Class1
    {
        public sealed class Quantity
        {
            public double Value { get; set; }
        }
     
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

        [ExcelExport("Add two numbers")]
        public static double Add([Parameter("First number")] double left, [Parameter("Second number")] double right)
        {
            return left + right;
        }

        [ExcelExport("Sum an array")]
        public static double SumArray([Parameter("Values")] double[] values)
        {
            return values.Sum();
        }

        [ExcelExport("Double a matrix")]
        public static double[,] DoubleMatrix([Parameter("Values")] double[,] values)
        {
            var result = new double[values.GetLength(0), values.GetLength(1)];
            for (int row = 0; row < values.GetLength(0); ++row)
                for (int column = 0; column < values.GetLength(1); ++column)
                    result[row, column] = values[row, column] * 2;
            return result;
        }

        [TypeRegister]
        public static Quantity ToQuantity(double value)
        {
            return new Quantity { Value = value };
        }

        [ExcelExport("Return a converted quantity")]
        public static double QuantityValue([Parameter("Quantity")] Quantity quantity)
        {
            return quantity.Value;
        }

        [ExcelOnOpen]
        public static void MyOpen()
        {
            File.WriteAllText(Path.Combine(Path.GetTempPath(), "xlw-aot-opened.txt"), "opened");
        }

        [ExcelOnClose]
        public static void MyClose()
        {
            File.WriteAllText(Path.Combine(Path.GetTempPath(), "xlw-aot-closed.txt"), "closed");

        }


    }
}
