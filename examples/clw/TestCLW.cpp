
#include "TestCLW.h"

MyArray
Stats(const MyArray& data       )
{
    double total=0.0;
    double totalsq=0.0;

    if (data.size() < 2)
        throw("At least data points are needed");

    for (unsigned long i=0; i < data.size(); i++)
    {
        total+=data[i];
        totalsq+=data[i]*data[i];
    }
    
    MyArray values(2);
    values[0] = total/data.size();
    values[1] = totalsq/data.size() - values[0] *values[0] ;

    return values;
}
