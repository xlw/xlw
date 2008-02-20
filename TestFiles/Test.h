//
//
//																	Test.h
//

#ifndef TEST_H
#define TEST_H
#include <xlw/port.h>
#include <xlw/MyContainers.h>
#include <xlw/CellMatrix.h>
#include <xlw/DoubleOrNothing.h>
#include <xlw/ArgList.h>
#include "PayOff.h"
#include "reftest.h"
#include <xlw/Wrapper.h>

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
//<xlw:time
EchoCells(const CellMatrix& Echoee// argument to be echoed
				   );

double // computes the circumference of a circle
//<xlw:time
Circ(double Diameter //the circle's diameter
			);

std::wstring // Concatenates two strings
//<xlw:time
Concat(std::wstring str1 // first string
	   , std::wstring str2 //second string
	   );

MyArray // computes mean and variance of a range
//<xlw:time
Stats(const MyArray& data // input for computation
	  );

std::string // says hello name
//<xlw:time
HelloWorldAgain(std::string name // name to be echoed
           );

double // echoes an unsigned long 
//<xlw:time
EchoUL( unsigned long b  // number to echo
	 );

double // echoes an int 
//<xlw:time
EchoInt( int b  // number to echo
	 );

double // tests DoubleOrNothingType
//<xlw:time
EchoDoubleOrNothing( DoubleOrNothing x // value to specify
					, double defaultValue // value to use if not specified
					);

CellMatrix // echoes arg list
//<xlw:time
EchoArgList( ArgumentList args  // arguments to echo
	 );

double // system clock
//<xlw:volatile
//<xlw:time
SystemTime(DoubleOrNothing ticksPerSecond // number to divide by
		   );

double // evaluate pay--off
//<xlw:time
PayOffEvaluation(const Wrapper<PayOff>& PayOffTable // table for payoff
	   , double Spot // point for evaluation
			);

bool // checks to see if there's an error
ContainsError(const CellMatrix& input2 // data to check for errors
							 );


bool // checks to see if there's a div by zero
ContainsDivByZero(const CellMatrix& input // data to check for errors
							 );

double // returns ID of current execution thread
//<xlw:threadsafe
GetThreadId();

std::string // return a string indicating datatype of OPER/OPER12 input
//<xlw:time
typeString(const XlfOper &input // value on which to perform type check 
           );

std::string // return a string indicating datatype of XLOPER/XLOPER12 input
//<xlw:time
typeString2(const reftest &input // value on which to perform type check 
           );

#endif
