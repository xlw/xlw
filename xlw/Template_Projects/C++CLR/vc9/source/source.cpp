
#include<cppinterface.h>

#pragma warning (disable : 4996)
using namespace System;

double // Adds # of days to given date
AddDays(double date // date to which to add 
       ,double days // number of days to add 
       )
{
    DateTime theTime = DateTime::FromOADate(date);
    theTime = theTime.AddDays(days);
    return theTime.ToOADate();
}

double // Adds hours to given date
AddHours(double date // date to which to add 
       , double hours // hours to add 
       )
{
    DateTime theTime = DateTime::FromOADate(date);
    theTime = theTime.AddHours(hours);
    return theTime.ToOADate();
}



