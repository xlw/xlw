
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


#ifndef TEST_H
#define TEST_H

#include "xlw/MyContainers.h"
#include <xlw/CellMatrix.h>
#include <xlw/DoubleOrNothing.h>
#include <xlw/ArgList.h>
#include "reftest.h"

using namespace xlw;



//<xlw:libraryname=MyTestLibrary
std::string // tests empty args
EmptyArgFunction();

short // echoes a short
EchoShort(short x // number to be echoed
       );

MyMatrix // echoes a matrix
EchoMat(const MyMatrix& Echoee // argument to be echoed
        );

MyMatrix // echoes a matrix
EchoMatrix(const NEMatrix& Echoee // argument to be echoed
        );

MyArray // echoes an array
EchoArray(const MyArray& Echoee // argument to be echoed
                  );

CellMatrix // echoes a cell matrix
EchoCells(const CellMatrix& Echoee// argument to be echoed
                   );

double // computes the circumference of a circle
Circ(double Diameter //the circle's diameter
            );

std::wstring // Concatenates two strings
Concat(std::wstring str1 // first string
       , std::wstring str2 //second string
       );

MyArray // computes mean and variance of a range
Stats(const MyArray& data // input for computation
      );

std::string // says hello name
HelloWorldAgain(std::string name // name to be echoed
           );

unsigned long // echoes an unsigned int
EchoUL( unsigned long b  // number to echo
     );

int // echoes an int
EchoInt( int b  // number to echo
     );

double // tests DoubleOrNothingType
EchoDoubleOrNothing( DoubleOrNothing x // value to specify
                    , double defaultValue // value to use if not specified
                    );

CellMatrix // echoes arg list
EchoArgList( ArgumentList args  // arguments to echo
     );

double // system clock
SystemTime(DoubleOrNothing ticksPerSecond // number to divide by
           );


bool // checks to see if there's an error
//<xlw:threadsafe
ContainsError(const CellMatrix& input2 // data to check for errors
                             );


bool // checks to see if there's a div by zero
//<xlw:threadsafe
ContainsDivByZero(const CellMatrix& input // data to check for errors
                             );

double // returns ID of current execution thread
GetThreadId();

std::string // return a string indicating datatype of OPER/OPER12 input
typeString(const XlfOper &input // value on which to perform type check
           );

std::string // return a string indicating datatype of XLOPER/XLOPER12 input
typeString2(const reftest &input // value on which to perform type check
           );


#endif
