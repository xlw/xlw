//
//
//																	Test.h
//

#ifndef TEST_H
#define TEST_H

#include <xlw/MyContainers.h>
#include <xlw/CellMatrix.h>
#include <xlw/DoubleOrNothing.h>
#include <xlw/ArgList.h>
#include "PayOff.h"
#include <xlw/Wrapper.h>

//<xlw:libraryname=MyTestLibrary

short // echoes a short
EchoShort(short x // number to be echoed
	   );

MyMatrix // echoes a matrix
//<xlw:time
EchoMat(const MyMatrix& Echoee // argument to be echoed
		);


MyArray // echoes an array
//<xlw:time
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


std::string // Concatenates two strings
//<xlw:time
Concat(std::string str1 // first string
	   , std::string str2 //second string
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
#endif
