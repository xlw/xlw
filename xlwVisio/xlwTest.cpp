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
namespace {
const char* LibraryName = "test.h";
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
"R");
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
short x(xlx.AsShort("x"));

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
"P");
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
MyMatrix Echoee(xlEchoee.AsMatrix("Echoee"));

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
"R");
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
MyArray Echoee(xlEchoee.AsArray("Echoee"));

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
"P");
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
CellMatrix Echoee(xlEchoee.AsCellMatrix("Echoee"));

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
"R");
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
double Diameter(xlDiameter.AsDouble("Diameter"));

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
"RR");
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
std::string str1(xlstr1.AsString("str1"));

XlfOper xlstr2(xlstr2_);
std::string str2(xlstr2.AsString("str2"));

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
"R");
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
MyArray data(xldata.AsArray("data"));

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
"R");
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
std::string name(xlname.AsString("name"));

std::string result(
	HelloWorldAgain(
		name)
	);
return XlfOper(result);
EXCEL_END
}
}



//////////////////////////

