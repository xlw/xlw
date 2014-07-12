#ifndef DLL_H
#define DLL_H

#define ERRCELLS_NOT_REQUIRED

#include <xlwDotNet.h>

//<xlw:libraryname=Example


std::wstring // tests empty args 
EmptyArgFunction();

short // echoes a short 
EchoShort(short x // number to be echoed
);

MyMatrix // echoes a matrix
EchoMat(const MyMatrix& Echoee // argument to be echoed
);

MyArray // echoes an array
EchoArray(const MyArray& Echoee //  argument to be echoed
);

CellMatrix // echoes a  CellMatrix
//<xlw:time
EchoCells(const CellMatrix& Echoee //  argument to be echoed
);

double // computes the circumference of a circle 
Circ(double Diameter // the circle's diameter
);

std::wstring // Concatenates two strings
Concat(const std::wstring& str1, // first string
const std::wstring& str2 // second string
);

MyArray // computes mean and variance of a range 
//<xlw:time
stats(const MyArray& data // input for computation
);

std::wstring // says hello name
HelloWorldAgain(const std::wstring& name // name to be echoed
);

unsigned long // echoes an unsigned integer
EchoUL(unsigned long b // number to echo
);

int // Echoes an integer
EchoInt(int b // number to echo
);

double // tests DoubleOrNothingType
EchoDoubleOrNothing(const CellMatrix& x, // value to specify
double defaultValue // default value
);

double // system clock
//<xlw:volatile
//<xlw:time
SystemTime(const CellMatrix& ticksPerSecond // number to divide by
);

CellMatrix // echoes arg list
//<xlw:time
EchoArgList(const ArgumentList& args //  arguments to echo
);

double // evaluate pay--off
PayOffEvaluation(const CellMatrix& OptionPayoff, //  table for payoff
double Spot //  point for evaluation
);

bool // checks to see if there's an error
ContainsError(const CellMatrix& input // data to check for errors
);

bool // checks to see if there's a div by zero
ContainsDivByZero(const CellMatrix& input // data to check for errors
);

double // Gets the thread id
//<xlw:volatile
//<xlw:threadsafe
GetThreadId();

std::wstring // return a string indicating datatype of OPER/OPER12 input
typeString(const CellMatrix& input // parameter
);

std::wstring // return a string indicating datatype of XLOPER/XLOPER12 input
typeString2(const CellMatrix& input // parameter
);

MyArray // takes double[]
CastToCSArray(const MyArray& csarray //  double Array
);

MyArray // takes double[]
CastToCSArrayTwice(const MyArray& csarray //  double Array
);

MyMatrix // takes double[,]
CastToCSMatrix(const MyMatrix& csmatrix //  double Array
);

MyMatrix // takes double[,]
CastToCSMatrixTwice(const MyMatrix& csmatrix //  double Array
);

double // throws an exception of type ArgumentNullException
throwString(const std::wstring& err // Just any random string 
);

double // throws an exception of type cellMatrixException
throwCellMatrix(const std::wstring& err // Just any random string 
);

double // makes the C Runtime throw an exception
throwCError(const std::wstring& err // Just any random string 
);

CellMatrix // Obtains historial market data from yahoo
GetHistoricDataFromYahoo(const std::wstring& symbol, // Yahoo Symbol
double beginDate, // Begin Date
double endDate // End Date
);

#endif 
