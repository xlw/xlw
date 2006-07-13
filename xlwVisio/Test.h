//
//
//																	Test.h
//

#ifndef TEST_H
#define TEST_H

#include <xlw/MyContainers.h>
#include <xlw/CellMatrix.h>

MyMatrix // echoes a matrix
EchoMat(const MyMatrix& Echoee // argument to be echoed
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


std::string // Concatenates two strings
Concat(std::string str1 // first string
	   , std::string str2 //second string
	   );
 
MyArray // computes mean and variance of a range
Stats(const MyArray& data // input for computation
	  );



std::string // says hello name
HelloWorld(std::string name // name to be echoed
           );
 
#endif
