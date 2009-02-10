//// 
//// created by xlwplus
////

#include <xlw/pragmas.h>
#include <xlw/MyContainers.h>
#include <xlw/CellMatrix.h>
#include "Test.h"
#include <xlw/xlw.h>
#include <xlw/XlFunctionRegistration.h>
#include <stdexcept>
#include <xlw/XlOpenClose.h>
#include <ctime>
using namespace xlw;
#include <xlw/ArgList.h>

#include <xlw/ArgListFactory.h>

#include <xlw/xlarray.h>

namespace {
const char* LibraryName = "MyTestLibrary";
};

// dummy function to force linkage
namespace {
void DummyFunction()
{
xlAutoOpen();
xlAutoClose();
}
}

// registrations start here


namespace
{
XLRegistration::Arg
EmptyArgFunctionArgs[]=
{
 { "","" } 
};
  XLRegistration::XLFunctionRegistrationHelper
registerEmptyArgFunction("xlEmptyArgFunction",
"EmptyArgFunction",
" tests empty args ",
LibraryName,
EmptyArgFunctionArgs,
0
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlEmptyArgFunction(
)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

std::string result(
	EmptyArgFunction());
return XlfOper(result);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
EchoShortArgs[]=
{
{ "x"," number to be echoed ","XLF_OPER"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerEchoShort("xlEchoShort",
"EchoShort",
" echoes a short ",
LibraryName,
EchoShortArgs,
1
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlEchoShort(
LPXLFOPER xa)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper xb(
	(xa));
short x(
	xb.AsShort("x"));

short result(
	EchoShort(
		x)
	);
return XlfOper(result);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
EchoMatArgs[]=
{
{ "Echoee"," argument to be echoed ","XLF_OPER"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerEchoMat("xlEchoMat",
"EchoMat",
" echoes a matrix ",
LibraryName,
EchoMatArgs,
1
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlEchoMat(
LPXLFOPER Echoeea)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper Echoeeb(
	(Echoeea));
MyMatrix Echoee(
	Echoeeb.AsMatrix("Echoee"));

MyMatrix result(
	EchoMat(
		Echoee)
	);
return XlfOper(result);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
EchoMatrixArgs[]=
{
{ "Echoee"," argument to be echoed ","K"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerEchoMatrix("xlEchoMatrix",
"EchoMatrix",
" echoes a matrix ",
LibraryName,
EchoMatrixArgs,
1
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlEchoMatrix(
LPXLARRAY Echoeea)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

NEMatrix Echoee(
	GetMatrix(Echoeea));

MyMatrix result(
	EchoMatrix(
		Echoee)
	);
return XlfOper(result);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
EchoArrayArgs[]=
{
{ "Echoee"," argument to be echoed ","XLF_OPER"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerEchoArray("xlEchoArray",
"EchoArray",
" echoes an array ",
LibraryName,
EchoArrayArgs,
1
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlEchoArray(
LPXLFOPER Echoeea)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper Echoeeb(
	(Echoeea));
MyArray Echoee(
	Echoeeb.AsArray("Echoee"));

MyArray result(
	EchoArray(
		Echoee)
	);
return XlfOper(result);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
EchoCellsArgs[]=
{
{ "Echoee"," argument to be echoed ","XLF_OPER"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerEchoCells("xlEchoCells",
"EchoCells",
" echoes a cell matrix ",
LibraryName,
EchoCellsArgs,
1
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlEchoCells(
LPXLFOPER Echoeea)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper Echoeeb(
	(Echoeea));
CellMatrix Echoee(
	Echoeeb.AsCellMatrix("Echoee"));

 double t = (clock()+0.0)/CLOCKS_PER_SEC;
CellMatrix result(
	EchoCells(
		Echoee)
	);
  t = (clock()+0.0)/CLOCKS_PER_SEC-t;
CellMatrix resultCells(result);
CellMatrix time(1,2);
time(0,0) = "time taken";
time(0,1) = t;
resultCells.PushBottom(time);
return XlfOper(resultCells);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
CircArgs[]=
{
{ "Diameter","the circle's diameter ","B"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerCirc("xlCirc",
"Circ",
" computes the circumference of a circle ",
LibraryName,
CircArgs,
1
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlCirc(
double Diameter)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);


 double t = (clock()+0.0)/CLOCKS_PER_SEC;
double result(
	Circ(
		Diameter)
	);
  t = (clock()+0.0)/CLOCKS_PER_SEC-t;
CellMatrix resultCells(result);
CellMatrix time(1,2);
time(0,0) = "time taken";
time(0,1) = t;
resultCells.PushBottom(time);
return XlfOper(resultCells);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
ConcatArgs[]=
{
{ "str1"," first string ","XLW_WSTR"},
{ "str2","second string ","XLW_WSTR"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerConcat("xlConcat",
"Concat",
" Concatenates two strings ",
LibraryName,
ConcatArgs,
2
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlConcat(
XLWSTR str1a,
XLWSTR str2a)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

std::wstring str1(
	voidToWstr(str1a));

std::wstring str2(
	voidToWstr(str2a));

 double t = (clock()+0.0)/CLOCKS_PER_SEC;
std::wstring result(
	Concat(
		str1,
		str2)
	);
  t = (clock()+0.0)/CLOCKS_PER_SEC-t;
CellMatrix resultCells(result);
CellMatrix time(1,2);
time(0,0) = "time taken";
time(0,1) = t;
resultCells.PushBottom(time);
return XlfOper(resultCells);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
StatsArgs[]=
{
{ "data"," input for computation ","XLF_OPER"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerStats("xlStats",
"Stats",
" computes mean and variance of a range ",
LibraryName,
StatsArgs,
1
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlStats(
LPXLFOPER dataa)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper datab(
	(dataa));
MyArray data(
	datab.AsArray("data"));

 double t = (clock()+0.0)/CLOCKS_PER_SEC;
MyArray result(
	Stats(
		data)
	);
  t = (clock()+0.0)/CLOCKS_PER_SEC-t;
CellMatrix resultCells(result);
CellMatrix time(1,2);
time(0,0) = "time taken";
time(0,1) = t;
resultCells.PushBottom(time);
return XlfOper(resultCells);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
HelloWorldAgainArgs[]=
{
{ "name"," name to be echoed ","XLF_OPER"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerHelloWorldAgain("xlHelloWorldAgain",
"HelloWorldAgain",
" says hello name ",
LibraryName,
HelloWorldAgainArgs,
1
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlHelloWorldAgain(
LPXLFOPER namea)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper nameb(
	(namea));
std::string name(
	nameb.AsString("name"));

 double t = (clock()+0.0)/CLOCKS_PER_SEC;
std::string result(
	HelloWorldAgain(
		name)
	);
  t = (clock()+0.0)/CLOCKS_PER_SEC-t;
CellMatrix resultCells(result);
CellMatrix time(1,2);
time(0,0) = "time taken";
time(0,1) = t;
resultCells.PushBottom(time);
return XlfOper(resultCells);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
EchoULArgs[]=
{
{ "b"," number to echo ","B"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerEchoUL("xlEchoUL",
"EchoUL",
" echoes an unsigned long ",
LibraryName,
EchoULArgs,
1
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlEchoUL(
double ba)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

unsigned long b(
	static_cast<unsigned long>(ba));

 double t = (clock()+0.0)/CLOCKS_PER_SEC;
double result(
	EchoUL(
		b)
	);
  t = (clock()+0.0)/CLOCKS_PER_SEC-t;
CellMatrix resultCells(result);
CellMatrix time(1,2);
time(0,0) = "time taken";
time(0,1) = t;
resultCells.PushBottom(time);
return XlfOper(resultCells);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
EchoIntArgs[]=
{
{ "b"," number to echo ","B"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerEchoInt("xlEchoInt",
"EchoInt",
" echoes an int ",
LibraryName,
EchoIntArgs,
1
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlEchoInt(
double ba)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

int b(
	static_cast<int>(ba));

 double t = (clock()+0.0)/CLOCKS_PER_SEC;
double result(
	EchoInt(
		b)
	);
  t = (clock()+0.0)/CLOCKS_PER_SEC-t;
CellMatrix resultCells(result);
CellMatrix time(1,2);
time(0,0) = "time taken";
time(0,1) = t;
resultCells.PushBottom(time);
return XlfOper(resultCells);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
EchoDoubleOrNothingArgs[]=
{
{ "x"," value to specify ","XLF_OPER"},
{ "defaultValue"," value to use if not specified ","B"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerEchoDoubleOrNothing("xlEchoDoubleOrNothing",
"EchoDoubleOrNothing",
" tests DoubleOrNothingType ",
LibraryName,
EchoDoubleOrNothingArgs,
2
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlEchoDoubleOrNothing(
LPXLFOPER xa,
double defaultValue)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper xb(
	(xa));
CellMatrix xc(
	xb.AsCellMatrix("xc"));
DoubleOrNothing x(
	DoubleOrNothing(xc,"x"));


 double t = (clock()+0.0)/CLOCKS_PER_SEC;
double result(
	EchoDoubleOrNothing(
		x,
		defaultValue)
	);
  t = (clock()+0.0)/CLOCKS_PER_SEC-t;
CellMatrix resultCells(result);
CellMatrix time(1,2);
time(0,0) = "time taken";
time(0,1) = t;
resultCells.PushBottom(time);
return XlfOper(resultCells);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
EchoArgListArgs[]=
{
{ "args"," arguments to echo ","XLF_OPER"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerEchoArgList("xlEchoArgList",
"EchoArgList",
" echoes arg list ",
LibraryName,
EchoArgListArgs,
1
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlEchoArgList(
LPXLFOPER argsa)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper argsb(
	(argsa));
CellMatrix argsc(
	argsb.AsCellMatrix("argsc"));
ArgumentList args(
	ArgumentList(argsc,"args"));

 double t = (clock()+0.0)/CLOCKS_PER_SEC;
CellMatrix result(
	EchoArgList(
		args)
	);
  t = (clock()+0.0)/CLOCKS_PER_SEC-t;
CellMatrix resultCells(result);
CellMatrix time(1,2);
time(0,0) = "time taken";
time(0,1) = t;
resultCells.PushBottom(time);
return XlfOper(resultCells);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
SystemTimeArgs[]=
{
{ "ticksPerSecond"," number to divide by ","XLF_OPER"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerSystemTime("xlSystemTime",
"SystemTime",
" system clock ",
LibraryName,
SystemTimeArgs,
1
,true
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlSystemTime(
LPXLFOPER ticksPerSeconda)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper ticksPerSecondb(
	(ticksPerSeconda));
CellMatrix ticksPerSecondc(
	ticksPerSecondb.AsCellMatrix("ticksPerSecondc"));
DoubleOrNothing ticksPerSecond(
	DoubleOrNothing(ticksPerSecondc,"ticksPerSecond"));

 double t = (clock()+0.0)/CLOCKS_PER_SEC;
double result(
	SystemTime(
		ticksPerSecond)
	);
  t = (clock()+0.0)/CLOCKS_PER_SEC-t;
CellMatrix resultCells(result);
CellMatrix time(1,2);
time(0,0) = "time taken";
time(0,1) = t;
resultCells.PushBottom(time);
return XlfOper(resultCells);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
PayOffEvaluationArgs[]=
{
{ "PayOffTable"," table for payoff ","XLF_OPER"},
{ "Spot"," point for evaluation ","B"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerPayOffEvaluation("xlPayOffEvaluation",
"PayOffEvaluation",
" evaluate pay--off ",
LibraryName,
PayOffEvaluationArgs,
2
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlPayOffEvaluation(
LPXLFOPER PayOffTablea,
double Spot)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper PayOffTableb(
	(PayOffTablea));
CellMatrix PayOffTablec(
	PayOffTableb.AsCellMatrix("PayOffTablec"));
ArgumentList PayOffTabled(
	ArgumentList(PayOffTablec,"PayOffTabled"));
Wrapper<PayOff> PayOffTable(
	GetFromFactory<PayOff>(PayOffTabled));


 double t = (clock()+0.0)/CLOCKS_PER_SEC;
double result(
	PayOffEvaluation(
		PayOffTable,
		Spot)
	);
  t = (clock()+0.0)/CLOCKS_PER_SEC-t;
CellMatrix resultCells(result);
CellMatrix time(1,2);
time(0,0) = "time taken";
time(0,1) = t;
resultCells.PushBottom(time);
return XlfOper(resultCells);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
ContainsErrorArgs[]=
{
{ "input2"," data to check for errors ","XLF_OPER"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerContainsError("xlContainsError",
"ContainsError",
" checks to see if there's an error ",
LibraryName,
ContainsErrorArgs,
1
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlContainsError(
LPXLFOPER input2a)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper input2b(
	(input2a));
CellMatrix input2(
	input2b.AsCellMatrix("input2"));

bool result(
	ContainsError(
		input2)
	);
return XlfOper(result);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
ContainsDivByZeroArgs[]=
{
{ "input"," data to check for errors ","XLF_OPER"}
};
  XLRegistration::XLFunctionRegistrationHelper
registerContainsDivByZero("xlContainsDivByZero",
"ContainsDivByZero",
" checks to see if there's a div by zero ",
LibraryName,
ContainsDivByZeroArgs,
1
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlContainsDivByZero(
LPXLFOPER inputa)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper inputb(
	(inputa));
CellMatrix input(
	inputb.AsCellMatrix("input"));

bool result(
	ContainsDivByZero(
		input)
	);
return XlfOper(result);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
GetThreadIdArgs[]=
{
 { "","" } 
};
  XLRegistration::XLFunctionRegistrationHelper
registerGetThreadId("xlGetThreadId",
"GetThreadId",
" returns ID of current execution thread ",
LibraryName,
GetThreadIdArgs,
0
,false
,true
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlGetThreadId(
)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

double result(
	GetThreadId());
return XlfOper(result);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
typeStringArgs[]=
{
{ "input"," value on which to perform type check ","XLF_OPER"}
};
  XLRegistration::XLFunctionRegistrationHelper
registertypeString("xltypeString",
"typeString",
" return a string indicating datatype of OPER/OPER12 input ",
LibraryName,
typeStringArgs,
1
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xltypeString(
LPXLFOPER inputa)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper input(
	(inputa));

 double t = (clock()+0.0)/CLOCKS_PER_SEC;
std::string result(
	typeString(
		input)
	);
  t = (clock()+0.0)/CLOCKS_PER_SEC-t;
CellMatrix resultCells(result);
CellMatrix time(1,2);
time(0,0) = "time taken";
time(0,1) = t;
resultCells.PushBottom(time);
return XlfOper(resultCells);
EXCEL_END
}
}



//////////////////////////

namespace
{
XLRegistration::Arg
typeString2Args[]=
{
{ "input"," value on which to perform type check ","XLF_XLOPER"}
};
  XLRegistration::XLFunctionRegistrationHelper
registertypeString2("xltypeString2",
"typeString2",
" return a string indicating datatype of XLOPER/XLOPER12 input ",
LibraryName,
typeString2Args,
1
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xltypeString2(
LPXLFOPER inputa)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

reftest input(
	(inputa));

 double t = (clock()+0.0)/CLOCKS_PER_SEC;
std::string result(
	typeString2(
		input)
	);
  t = (clock()+0.0)/CLOCKS_PER_SEC-t;
CellMatrix resultCells(result);
CellMatrix time(1,2);
time(0,0) = "time taken";
time(0,1) = t;
resultCells.PushBottom(time);
return XlfOper(resultCells);
EXCEL_END
}
}



//////////////////////////

