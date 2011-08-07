#include "cppinterface.h"
#include <xlw/XlfServices.h>
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;
using namespace Runtime::InteropServices;


std::string CLR2CPP(String^ clrString)
{
    System::IntPtr memHandle = Marshal::StringToHGlobalAnsi(clrString);
    std::string result =  (const char*)(memHandle.ToPointer());
    Marshal::FreeHGlobal(memHandle);
    return result;
}

String^ CPP2CLR(const std::string &cppString)
{
    return gcnew String(cppString.c_str());
}





double // Echoes Date
EchoDate(
		 DateTime date // the Date
		 )
{
	return date.ToOADate();
}

std::string SHA1Hash(const std::string &value)
{

	String^ clrValue = CPP2CLR(value);

	Text::ASCIIEncoding^ theEncoding = gcnew Text::ASCIIEncoding();

	array<Byte>^  valueAsBytes = theEncoding->GetBytes(clrValue);

	Security::Cryptography::SHA1Managed^ theHasher = gcnew Security::Cryptography::SHA1Managed();

	array<Byte>^  theHash =  theHasher->ComputeHash(valueAsBytes);

	std::string theUnmangedHash;

	for(int i(0); i< theHash->GetLength(0); ++i)
	{
		theUnmangedHash+=CLR2CPP(theHash[i].ToString("X"));
	}

	return theUnmangedHash;
}