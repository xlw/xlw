//
//
//                                                                    Test.h
//

#ifndef TEST_H
#define TEST_H

#include "xlw/MyContainers.h"
#include <xlw/CellMatrix.h>
#include <xlw/DoubleOrNothing.h>
#include <xlw/ArgList.h>

using namespace xlw;



//<xlw:libraryname=MyManagedTestLibrary


double // Adds number of days to given date
AddDays(double date // date to which to add 
       ,double days // number of days to add 
       );

double // Adds hours to given date
AddHours(double date // date to which to add 
       , double hours // hours to add 
       );






#endif
