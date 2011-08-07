
#ifndef NATIVE_H
#define NATIVE_H
            
#include "xlw/MyContainers.h"
#include <xlw/CellMatrix.h>
#include <xlw/DoubleOrNothing.h>
#include <xlw/ArgList.h>
#include <string>

using namespace System;
             
using namespace xlw;
  
//<xlw:libraryname=cpp_clr_Template

CellMatrix // Obtains historial market data from yahoo 
GetHistoricDataFromYahoo(
                          std::string  symbol // Yahoo Symbol 
                         ,DateTime beginDate // Begin Date
                         ,DateTime endDate //End Date
                         );

double // Echoes Date
//<xlw:time
EchoDate(
		 DateTime date // the Date
		 );

std::string //  Computes the SHA1 hash of the input string
SHA1Hash(
			const std::string &value // The data 
			);

#endif
