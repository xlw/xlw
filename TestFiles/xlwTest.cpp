//// 
//// created by xlwplus
////

#include <xlw/pragmas.h>
#include <xlw/MyContainers.h>
#include <xlw/CellMatrix.h>
#include "test.h"
#include <xlw/xlw.h>
#include <xlw/XlFunctionRegistration.h>
#include <stdexcept>
#include <xlw/XlOpenClose.h>
#include <xlw/ArgList.h>

#include <xlw/ArgListFactory.h>

namespace {
const char* LibraryName = "TestLibrary";
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
LPXLOPER xlx_)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper xlx(xlx_);
short x(
	xlx.AsShort("x"));

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
LPXLOPER xlEchoee_)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper xlEchoee(xlEchoee_);
MyMatrix Echoee(
	xlEchoee.AsMatrix("Echoee"));

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
LPXLOPER xlEchoee_)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper xlEchoee(xlEchoee_);
MyArray Echoee(
	xlEchoee.AsArray("Echoee"));

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
LPXLOPER xlEchoee_)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper xlEchoee(xlEchoee_);
CellMatrix Echoee(
	xlEchoee.AsCellMatrix("Echoee"));

CellMatrix result(
	EchoCells(
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
"R"
);
}



extern "C"
{
LPXLOPER EXCEL_EXPORT
xlCirc(
LPXLOPER xlDiameter_)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper xlDiameter(xlDiameter_);
double Diameter(
	xlDiameter.AsDouble("Diameter"));

double result(
	Circ(
		Diameter)
	);
return XlfOper(result);
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
LPXLOPER xlstr1_,
LPXLOPER xlstr2_)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper xlstr1(xlstr1_);
std::string str1(
	xlstr1.AsString("str1"));

XlfOper xlstr2(xlstr2_);
std::string str2(
	xlstr2.AsString("str2"));

std::string result(
	Concat(
		str1,
		str2)
	);
return XlfOper(result);
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
LPXLOPER xldata_)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper xldata(xldata_);
MyArray data(
	xldata.AsArray("data"));

MyArray result(
	Stats(
		data)
	);
return XlfOper(result);
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
LPXLOPER xlname_)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper xlname(xlname_);
std::string name(
	xlname.AsString("name"));

std::string result(
	HelloWorldAgain(
		name)
	);
return XlfOper(result);
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
"R"
);
}



extern "C"
{
LPXLOPER EXCEL_EXPORT
xlEchoUL(
LPXLOPER xlb_)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper xlb(xlb_);
double ba(
	xlb.AsDouble("ba"));
unsigned long b(
	static_cast<unsigned long>(ba));

double result(
	EchoUL(
		b)
	);
return XlfOper(result);
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
"R"
);
}



extern "C"
{
LPXLOPER EXCEL_EXPORT
xlEchoInt(
LPXLOPER xlb_)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper xlb(xlb_);
double ba(
	xlb.AsDouble("ba"));
int b(
	static_cast<int>(ba));

double result(
	EchoInt(
		b)
	);
return XlfOper(result);
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
"PR"
);
}



extern "C"
{
LPXLOPER EXCEL_EXPORT
xlEchoDoubleOrNothing(
LPXLOPER xlx_,
LPXLOPER xldefaultValue_)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper xlx(xlx_);
CellMatrix xa(
	xlx.AsCellMatrix("xa"));
DoubleOrNothing x(
	DoubleOrNothing(xa,"x"));

XlfOper xldefaultValue(xldefaultValue_);
double defaultValue(
	xldefaultValue.AsDouble("defaultValue"));

double result(
	EchoDoubleOrNothing(
		x,
		defaultValue)
	);
return XlfOper(result);
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
LPXLOPER xlargs_)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper xlargs(xlargs_);
CellMatrix argsa(
	xlargs.AsCellMatrix("argsa"));
ArgumentList args(
	ArgumentList(argsa,"args"));

CellMatrix result(
	EchoArgList(
		args)
	);
return XlfOper(result);
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
LPXLOPER xlticksPerSecond_)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper xlticksPerSecond(xlticksPerSecond_);
CellMatrix ticksPerSeconda(
	xlticksPerSecond.AsCellMatrix("ticksPerSeconda"));
DoubleOrNothing ticksPerSecond(
	DoubleOrNothing(ticksPerSeconda,"ticksPerSecond"));

double result(
	SystemTime(
		ticksPerSecond)
	);
return XlfOper(result);
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
"PR"
);
}



extern "C"
{
LPXLOPER EXCEL_EXPORT
xlPayOffEvaluation(
LPXLOPER xlPayOffTable_,
LPXLOPER xlSpot_)
{
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);

XlfOper xlPayOffTable(xlPayOffTable_);
CellMatrix PayOffTablea(
	xlPayOffTable.AsCellMatrix("PayOffTablea"));
ArgumentList PayOffTableb(
	ArgumentList(PayOffTablea,"PayOffTableb"));
Wrapper<PayOff> PayOffTable(
	GetFromFactory<PayOff>(PayOffTableb));

XlfOper xlSpot(xlSpot_);
double Spot(
	xlSpot.AsDouble("Spot"));

double result(
	PayOffEvaluation(
		PayOffTable,
		Spot)
	);
return XlfOper(result);
EXCEL_END
}
}



//////////////////////////

