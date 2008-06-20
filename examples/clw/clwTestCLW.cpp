//// 
//// created by xlwplus
////

#include <xlw/pragmas.h>
#include <clw/Dispatcher.h>
#include <xlw/MyContainers.h>
#include <xlw/CellMatrix.h>
#include "TestCLW.h"
#include <xlw/xlw.h>
#include <xlw/XlFunctionRegistration.h>
#include <stdexcept>
#include <xlw/XlOpenClose.h>
#include <ctime>



 namespace 
{
CellMatrix clStats(ArgumentList arguments)  
{

MyArray data(
arguments.GetArrayArgumentValue("data"));

MyArray result(
	Stats(
		data)
	);
return result;
}


clw::DispatcherHelper clhelperStats("Stats",&clStats);

//////////////////////////

}


