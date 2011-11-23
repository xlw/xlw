/*
 Copyright (C) 2008 2009  Narinder S Claire
 Copyright (C) 2011  John Adcock

 This file is part of XLWDOTNET, a free-software/open-source C# wrapper of the
 Excel C API - http://xlw.sourceforge.net/
 
 XLWDOTNET is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/
 
 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net
 
 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using xlwDotNet;
using xlwDotNet.xlwTypes;


namespace Example
{
    public class Class1
    {
     
        [ExcelExport("tests empty args ")]
        public static String EmptyArgFunction()
        {
            return "this function is useless except for testing.";
        }

        [ExcelExport("echoes a short ")]
        public static short EchoShort(
                             [Parameter("number to be echoed")] short x
                            )
        {
            return x;
        }

        [ExcelExport("echoes a matrix")]
        public static MyMatrix EchoMat(
                             [Parameter("argument to be echoed")] MyMatrix Echoee
                            )
        {
            return Echoee;
        }
        [ExcelExport("echoes an array")]
        public static MyArray EchoArray(
                             [Parameter(" argument to be echoed")] MyArray Echoee
                            )
        {
            return Echoee;
        }
        [ExcelExport("echoes a  CellMatrix", timeFlag = true)]
        public static CellMatrix EchoCells(
                             [Parameter(" argument to be echoed")] CellMatrix Echoee
                            )
        {
            CellValue.ValueTypeEnum type = Echoee[0, 0].ValueType;
            return Echoee;
        }

        [ExcelExport("computes the circumference of a circle ")]
        public static double Circ(
                             [Parameter("the circle's diameter")] double Diameter
                            )
        {
            return Diameter * 3.14159;
        }

        [ExcelExport("Concatenates two strings")]
        public static string Concat(
                             [Parameter("first string")] string str1,
                             [Parameter("second string")] string str2  
                            )
        {
            return str1+str2;
        }
        [ExcelExport("computes mean and variance of a range ", timeFlag = true)]
        public static MyArray stats(
                             [Parameter("input for computation")] MyArray data
                            )
        {
            double total=0.0;
	        double totalsq=0.0;

	        if (data.size < 2)
		        throw(new Exception("At least data points are needed"));

	        for (int i=0; i < data.size; i++)
	            {
		            total+=data[i];
		            totalsq+=data[i]*data[i];
	            }
    	
	        MyArray values = new MyArray(2);
	        values[0] = total/data.size;
	        values[1] = totalsq/data.size - values[0] *values[0] ;

	        return values;

        }


        [ExcelExport("says hello name")]
        public static string HelloWorldAgain(
                             [Parameter("name to be echoed")] string name
                            )
        {
            return "hello " + name;
        }

        [ExcelExport("echoes an unsigned integer")]
        public static UInt32 EchoUL(
                             [Parameter("number to echo")] UInt32 b
                            )
        {
            return b;
        }

        [ExcelExport("Echoes an integer")]
        public static int EchoInt(
                             [Parameter("number to echo")] int b
                            )
        {
            return b;
        }

        [ExcelExport("tests DoubleOrNothingType")]
        public static double EchoDoubleOrNothing(
                             [Parameter("value to specify")] CellMatrix x, 
                             [Parameter("default value")] double defaultValue 
                            )
        {
            throw new Exception("type DoubleOrNothing not supported in xlwDotNet");
        }

        private static long timeAtStart = DateTime.Now.Ticks;

        [ExcelExport("system clock", timeFlag=true, volatileFlag=true)]
        public static double SystemTime(
                             [Parameter("number to divide by")] CellMatrix ticksPerSecond
                            )
        {
            if (ticksPerSecond.ColumnsInStructure != 1 || ticksPerSecond.RowsInStructure != 1)
                throw new Exception("Multiple values given where one expected for a double or nothing ");

            if (!ticksPerSecond[0, 0].IsEmpty && !ticksPerSecond[0, 0].IsANumber)
                throw new Exception("expected a double or nothing, got something else ");

            bool Empty = ticksPerSecond[0, 0].IsEmpty;

            double Value = Empty ? 1000: ticksPerSecond[0, 0].NumericValue();
            TimeSpan span = new TimeSpan(DateTime.Now.Ticks - timeAtStart);

            return span.TotalMilliseconds / Value;
        }

        [ExcelExport("echoes arg list", timeFlag = true)]
        public static CellMatrix EchoArgList(
                             [Parameter(" arguments to echo")] ArgumentList args
                            )
        {
            return args.AllData();
        }

        [ExcelExport("evaluate pay--off")]
        public static double PayOffEvaluation(
                             [Parameter(" table for payoff")] CellMatrix OptionPayoff,
                             [Parameter(" point for evaluation")] double Spot
                            )
        {
            throw new Exception("type Wrapper<PayOff> not supported in xlwDotNet");
        }

        [ExcelExport("checks to see if there's an error")]
        public static Boolean ContainsError(
                             [Parameter("data to check for errors")] CellMatrix input
                            )
        {
            for (int i = 0; i < input.RowsInStructure; ++i)
                for (int j = 0; j < input.ColumnsInStructure; ++j)
                    if (input[i, j].IsError)
                        return true;

            return false;
        }

        [ExcelExport("checks to see if there's a div by zero")]
        public static Boolean ContainsDivByZero(
                             [Parameter("data to check for errors")] CellMatrix input
                            )
        {
            for (int i = 0; i < input.RowsInStructure; ++i)
                for (int j = 0; j < input.ColumnsInStructure; ++j)
                    if (input[i, j].IsError)
                        if (input[i, j].ErrorValue() == 7)
                            return true;

            return false;

        }
        [ExcelExport("Gets the thread id", volatileFlag = true, threadSafeFlag = true)]
        public static double GetThreadId()
        {
            return (double)Thread.CurrentThread.ManagedThreadId;

        }

        [ExcelExport("return a string indicating datatype of OPER/OPER12 input")]
        public static string typeString(
                             [Parameter("parameter")] CellMatrix input
                            )
        {
            throw new Exception("XlfOper not implemented directly in xlwDotNet");
        }

        [ExcelExport("return a string indicating datatype of XLOPER/XLOPER12 input")]
        public static string typeString2(
                             [Parameter("parameter")] CellMatrix input
                            )
        {
            throw new Exception("XlfOper not implemented directly in xlwDotNet");
        }






///////////////////////////////////////////////////////////////////////////////////
/////////////// C# Specific test /////////////////////////////////////////////////


        [ExcelExport("takes double[]")]
        public static MyArray CastToCSArray (
                             [Parameter(" double Array")] double[] csarray
                            )
        {
            return csarray;
        }

        [ExcelExport("takes double[]")]
        public static double[] CastToCSArrayTwice(
                             [Parameter(" double Array")] double[] csarray
                            )
        {
            return csarray;
        }

        [ExcelExport("takes double[,]")]
        public static MyMatrix CastToCSMatrix(
                             [Parameter(" double Array")] double[,] csmatrix
                            )
        {
            return csmatrix;
        }

        [ExcelExport("takes double[,]")]
        public static double[,] CastToCSMatrixTwice(
                             [Parameter(" double Array")] double[,] csmatrix
                            )
        {
            return csmatrix;
        }

        ///////////////////////////////////////////////////////////////////////////////////
        /////////////// Throwing Exceptions ///////////////////////////////////////////////

        [ExcelExport("throws an exception of type ArgumentNullException")]
        public static double throwString(
                             [Parameter("Just any random string ")] string err
                            )
        {
            throw(new ArgumentNullException("err",err));
        }
        [ExcelExport("throws an exception of type cellMatrixException")]
        public static double throwCellMatrix(
                             [Parameter("Just any random string ")] string err
                            )
        {
            ArgumentList theContent = new ArgumentList("EXCEPTION");
            theContent.add("Error", "Don't worry, this is a dummy Error :-)");
            throw (new cellMatrixException("WOW its warm up here ",theContent.AllData()));
        }

        [ExcelExport("makes the C Runtime throw an exception")]
        public static double throwCError(
                             [Parameter("Just any random string ")] string err
                            )
        {
            MyMatrix theMatrix = new MyMatrix(2,2);
            return theMatrix[3,3];
        }


    }
}


