//// A Temporary test for CellValue of type XlfOper

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
EmptyArgFunctionArgs2[]=
{
 { "","" } 
};
  XLRegistration::XLFunctionRegistrationHelper
registerEmptyArgFunction2("xlTest1",
"Test1",
" tests empty args ",
LibraryName,
EmptyArgFunctionArgs2,
0
,false
);
}



extern "C"
{
LPXLFOPER EXCEL_EXPORT
xlTest1(){
EXCEL_BEGIN;

	if (XlfExcel::Instance().IsCalledByFuncWiz())
		return XlfOper(true);


 double t = (clock()+0.0)/CLOCKS_PER_SEC;

CellMatrix result(1, 2);
result(0,0) = XlfOper("hi");
result(0,1) = XlfOper(42.);

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

