#include "Test.h"


short // echoes a short
EchoShort(short x // number to be echoed
		   )
{
	return x;
}

MyMatrix EchoMat(const MyMatrix& EchoEe)
{
	return EchoEe;
}



MyArray EchoArray(const MyArray& Echoee// argument to be echoed
				  )
{
	return Echoee;
}


CellMatrix EchoCells(const CellMatrix& Echoee// argument to be echoed
				   )
{
	return Echoee;
}

double // computes the circumference of a circle
Circ(double Diameter //the circle's diameter
			)
{
	  return Diameter* 3.14159;
}


std::string Concat(std::string str1, std::string str2)
  {
    std::string ret = str1+str2;
    return ret;
  }

 
MyArray
Stats(const MyArray& data 	  )
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


std::string HelloWorldAgain(std::string name)
{
    return "hello "+name;
}

