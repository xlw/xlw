
/*
 Copyright (C) 2006 Mark Joshi
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2011 John Adcock
 Copyright (C) 2011 Narunder S Claire

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include "Test.h"
#include <ctime>
#include <windows.h>
#include<xlw/XlfExcel.h>
#include<xlw/XlOpenClose.h>
#include<xlw/XlfServices.h>

std::string // tests empty args
EmptyArgFunction()
{
    return "this function is useless except for testing.";
}

short // echoes a short
EchoShort(short x // number to be echoed
           )
{
    return x;
}

MyMatrix EchoMat(const MyMatrix& EchoEe)
{
    return EchoEe;
}

MyMatrix // echoes a matrix
EchoMatrix(const NEMatrix& Echoee // argument to be echoed
        )
{
    return Echoee;
}

MyArray EchoArray(const MyArray& Echoee// argument to be echoed
                  )
{
    return Echoee;
}

CellMatrix EchoCells(const CellMatrix& Echoee// argument to be echoed
                   )
{
    return Echoee;
}

double // computes the circumference of a circle
Circ(double Diameter //the circle's diameter
            )
{
      return Diameter* 3.14159;
}

std::wstring Concat(std::wstring str1, std::wstring str2)
  {
    std::wstring ret = str1+str2;
    return ret;
  }

MyArray
Stats(const MyArray& data       )
{
    double total=0.0;
    double totalsq=0.0;

    if (data.size() < 2)
        THROW_XLW("At least 2 data points are needed");

    for (unsigned long i=0; i < data.size(); i++)
    {
        total+=data[i];
        totalsq+=data[i]*data[i];
    }

    MyArray values(2);
    values[0] = total/data.size();
    values[1] = totalsq/data.size() - values[0] *values[0] ;

    return values;
}

std::string HelloWorldAgain(std::string name)
{
    return "hello "+name;
}

unsigned long // echoes an unsigned long
EchoUL( unsigned long b  // number to echo
     )
{
    return b;
}

int // echoes an int
EchoInt( int b  // number to echo
     )
{
    return b;
}

double // tests DoubleOrNothingType
EchoDoubleOrNothing( DoubleOrNothing x // value to specify
                    , double defaultValue // value to use if not specified
                    )
{
    return x.GetValueOrDefault(defaultValue);
}

CellMatrix // echoes arg list
EchoArgList( ArgumentList args  // arguments to echo
            )
{
    return args.AllData();
}

double // system clock
SystemTime(DoubleOrNothing ticksPerSecond // number to divide by
           )
{
    return clock()/ticksPerSecond.GetValueOrDefault(CLOCKS_PER_SEC);
}


bool // checks to see if there's an error
ContainsError(const CellMatrix& input // data to check for errors
                             )
{
    for (unsigned long i=0; i < input.RowsInStructure(); ++i)
        for (unsigned long j=0; j < input.ColumnsInStructure(); ++j)
            if (input(i,j).IsError())
                return true;

    return false;

}

bool // checks to see if there's a div by zero
ContainsDivByZero(const CellMatrix& input // data to check for errors
                             )
{
    for (unsigned long i=0; i < input.RowsInStructure(); ++i)
        for (unsigned long j=0; j < input.ColumnsInStructure(); ++j)
            if (input(i,j).IsError())
                if (input(i,j).ErrorValue() == 7UL)
                    return true;

    return false;

}

double GetThreadId() {
    return GetCurrentThreadId();
}

std::string // return a string indicating datatype of OPER/OPER12 input
typeString(const XlfOper &input) {
    return input.xltypeName();
}

std::string // return a string indicating datatype of XLOPER/XLOPER12 input
typeString2(const reftest &input) {
    return input.xltypeName();
}


