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
""
);
}



extern "C"
{
LPXLOPER EXCEL_EXPORT
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
{ "x"," number to be echoed "}
};
  XLRegistration::XLFunctionRegistrationHelper
registerEchoShort("xlEchoShort",
"EchoShort",
" echoes a short ",
LibraryName,
EchoShortArgs,
"R"
);
}



extern "C"
{
LPXLOPER EXCEL_EXPORT
xlEchoShort(
LPXLOPER xa)
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
{ "Echoee"," argument to be echoed "}
};
  XLRegistration::XLFunctionRegistrationHelper
registerEchoMat("xlEchoMat",
"EchoMat",
" echoes a matrix ",
LibraryName,
EchoMatArgs,
"P"
);
}



extern "C"
{
LPXLOPER EXCEL_EXPORT
xlEchoMat(
LPXLOPER Echoeea)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper Echoeeb(
	(Echoeea));
MyMatrix Echoee(
	Echoeeb.AsMatrix("Echoee"));

 double t = (clock()+0.0)/CLOCKS_PER_SEC;
MyMatrix result(
	EchoMat(
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
EchoMatrixArgs[]=
{
{ "Echoee"," argument to be echoed "}
};
  XLRegistration::XLFunctionRegistrationHelper
registerEchoMatrix("xlEchoMatrix",
"EchoMatrix",
" echoes a matrix ",
LibraryName,
EchoMatrixArgs,
"K"
);
}



extern "C"
{
LPXLOPER EXCEL_EXPORT
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
{ "Echoee"," argument to be echoed "}
};
  XLRegistration::XLFunctionRegistrationHelper
registerEchoArray("xlEchoArray",
"EchoArray",
" echoes an array ",
LibraryName,
EchoArrayArgs,
"R"
);
}



extern "C"
{
LPXLOPER EXCEL_EXPORT
xlEchoArray(
LPXLOPER Echoeea)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper Echoeeb(
	(Echoeea));
MyArray Echoee(
	Echoeeb.AsArray("Echoee"));

 double t = (clock()+0.0)/CLOCKS_PER_SEC;
MyArray result(
	EchoArray(
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
EchoCellsArgs[]=
{
{ "Echoee"," argument to be echoed "}
};
  XLRegistration::XLFunctionRegistrationHelper
registerEchoCells("xlEchoCells",
"EchoCells",
" echoes a cell matrix ",
LibraryName,
EchoCellsArgs,
"P"
);
}



extern "C"
{
LPXLOPER EXCEL_EXPORT
xlEchoCells(
LPXLOPER Echoeea)
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
{ "Diameter","the circle's diameter "}
};
  XLRegistration::XLFunctionRegistrationHelper
registerCirc("xlCirc",
"Circ",
" computes the circumference of a circle ",
LibraryName,
CircArgs,
"B"
);
}



extern "C"
{
LPXLOPER EXCEL_EXPORT
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
{ "str1"," first string "},
{ "str2","second string "}
};
  XLRegistration::XLFunctionRegistrationHelper
registerConcat("xlConcat",
"Concat",
" Concatenates two strings ",
LibraryName,
ConcatArgs,
"RR"
);
}



extern "C"
{
LPXLOPER EXCEL_EXPORT
xlConcat(
LPXLOPER str1a,
LPXLOPER str2a)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper str1b(
	(str1a));
std::string str1(
	str1b.AsString("str1"));

XlfOper str2b(
	(str2a));
std::string str2(
	str2b.AsString("str2"));

 double t = (clock()+0.0)/CLOCKS_PER_SEC;
std::string result(
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
{ "data"," input for computation "}
};
  XLRegistration::XLFunctionRegistrationHelper
registerStats("xlStats",
"Stats",
" computes mean and variance of a range ",
LibraryName,
StatsArgs,
"R"
);
}



extern "C"
{
LPXLOPER EXCEL_EXPORT
xlStats(
LPXLOPER dataa)
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
{ "name"," name to be echoed "}
};
  XLRegistration::XLFunctionRegistrationHelper
registerHelloWorldAgain("xlHelloWorldAgain",
"HelloWorldAgain",
" says hello name ",
LibraryName,
HelloWorldAgainArgs,
"R"
);
}



extern "C"
{
LPXLOPER EXCEL_EXPORT
xlHelloWorldAgain(
LPXLOPER namea)
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
{ "b"," number to echo "}
};
  XLRegistration::XLFunctionRegistrationHelper
registerEchoUL("xlEchoUL",
"EchoUL",
" echoes an unsigned long ",
LibraryName,
EchoULArgs,
"B"
);
}



extern "C"
{
LPXLOPER EXCEL_EXPORT
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
{ "b"," number to echo "}
};
  XLRegistration::XLFunctionRegistrationHelper
registerEchoInt("xlEchoInt",
"EchoInt",
" echoes an int ",
LibraryName,
EchoIntArgs,
"B"
);
}



extern "C"
{
LPXLOPER EXCEL_EXPORT
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
{ "x"," value to specify "},
{ "defaultValue"," value to use if not specified "}
};
  XLRegistration::XLFunctionRegistrationHelper
registerEchoDoubleOrNothing("xlEchoDoubleOrNothing",
"EchoDoubleOrNothing",
" tests DoubleOrNothingType ",
LibraryName,
EchoDoubleOrNothingArgs,
"PB"
);
}



extern "C"
{
LPXLOPER EXCEL_EXPORT
xlEchoDoubleOrNothing(
LPXLOPER xa,
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
{ "args"," arguments to echo "}
};
  XLRegistration::XLFunctionRegistrationHelper
registerEchoArgList("xlEchoArgList",
"EchoArgList",
" echoes arg list ",
LibraryName,
EchoArgListArgs,
"P"
);
}



extern "C"
{
LPXLOPER EXCEL_EXPORT
xlEchoArgList(
LPXLOPER argsa)
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
{ "ticksPerSecond"," number to divide by "}
};
  XLRegistration::XLFunctionRegistrationHelper
registerSystemTime("xlSystemTime",
"SystemTime",
" system clock ",
LibraryName,
SystemTimeArgs,
"P"
,true
);
}



extern "C"
{
LPXLOPER EXCEL_EXPORT
xlSystemTime(
LPXLOPER ticksPerSeconda)
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
{ "PayOffTable"," table for payoff "},
{ "Spot"," point for evaluation "}
};
  XLRegistration::XLFunctionRegistrationHelper
registerPayOffEvaluation("xlPayOffEvaluation",
"PayOffEvaluation",
" evaluate pay--off ",
LibraryName,
PayOffEvaluationArgs,
"PB"
);
}



extern "C"
{
LPXLOPER EXCEL_EXPORT
xlPayOffEvaluation(
LPXLOPER PayOffTablea,
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
{ "input"," data to check for errors "}
};
  XLRegistration::XLFunctionRegistrationHelper
registerContainsError("xlContainsError",
"ContainsError",
" checks to see if there's an error ",
LibraryName,
ContainsErrorArgs,
"P"
);
}



extern "C"
{
LPXLOPER EXCEL_EXPORT
xlContainsError(
LPXLOPER inputa)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper inputb(
	(inputa));
CellMatrix input(
	inputb.AsCellMatrix("input"));

bool result(
	ContainsError(
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
ContainsDivByZeroArgs[]=
{
{ "input"," data to check for errors "}
};
  XLRegistration::XLFunctionRegistrationHelper
registerContainsDivByZero("xlContainsDivByZero",
"ContainsDivByZero",
" checks to see if there's a div by zero ",
LibraryName,
ContainsDivByZeroArgs,
"P"
);
}



extern "C"
{
LPXLOPER EXCEL_EXPORT
xlContainsDivByZero(
LPXLOPER inputa)
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

