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

