
/*
Copyright (C) 1998, 1999, 2001, 2002 Jérôme Lecomte
Copyright (C) 2006 Mark Joshi
Copyright (C) 2009 Narinder S Claire

This file is part of xlw, a free-software/open-source C++ wrapper of the
Excel C API - http://xlw.sourceforge.net/

xlw is free software: you can redistribute it and/or modify it under the
terms of the xlw license.  You should have received a copy of the
license along with this program; if not, please email xlw-users@lists.sf.net

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#undef  UNICODE          // need to undefine for mingw
#undef _UNICODE
#include <windows.h>



#include <xlw/XlOpenClose.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <xlw/Win32StreamBuf.h>
#include <xlw/XlFunctionRegistration.h>
#include <xlw/CellMatrix.h>
#include<memory>
#include<string>


xlw::Win32StreamBuf debuggerStreamBuf;
std::streambuf * oldStreamBuf;

extern "C"
{

	long EXCEL_EXPORT xlAutoOpen()
	{
		MEMORY_BASIC_INFORMATION theInfo ;
		HMODULE theHandle = NULL;
		char theDLLPathChar [MAX_PATH + 1] = "";
		DWORD dwRet = 0;
		const int bufferSize=4096;
		std::auto_ptr<char> originalPathValue;
		bool ok=true;
		try {



			oldStreamBuf = std::cerr.rdbuf(&debuggerStreamBuf);
			std::cerr << XLW__HERE__ << "std::cerr redirected to MSVC debugger" << std::endl;

			dwRet = VirtualQuery (((LPCVOID) (&oldStreamBuf)), &theInfo,((DWORD) (sizeof (MEMORY_BASIC_INFORMATION))));
			if (dwRet)
			{
				theHandle = ((HMODULE) (theInfo.AllocationBase));
				GetModuleFileName (theHandle, theDLLPathChar , MAX_PATH);
				xlw::XlfExcel::Instance().SendMessage(theDLLPathChar);

				originalPathValue.reset(new char[bufferSize]);
				dwRet = GetEnvironmentVariable("Path", originalPathValue.get(),  bufferSize);
				if(bufferSize < dwRet)
				{
					originalPathValue.reset( new char[dwRet]);   
					dwRet = GetEnvironmentVariable("Path", originalPathValue.get(), dwRet);
					if(!dwRet)
					{
						ok = false;
						std::cerr << XLW__HERE__ <<" Could not get PATH Environment Variable" << std::endl; 

					}
				}

			}
			else
			{
				ok = false;
				std::cerr << XLW__HERE__ <<" Could not attain path of DLL" << std::endl;

			}
			if(ok) 
			{
				std::string theDLLPath(theDLLPathChar);
				std::string newPathValue( originalPathValue.get());
				std::string::size_type pos = theDLLPath.find_last_of("\\");

				newPathValue+= ";"+theDLLPath.substr(0,pos);

				if (!SetEnvironmentVariable("Path", newPathValue.c_str())) 
				{
					std::cerr << XLW__HERE__ << " SetEnvironmentVariable failed to set PATH" << std::endl; 
					ok = false;
				}
				else
				{
					std::cerr << XLW__HERE__ << " PATH set successfully " << std::endl;
				}
			}
			if(!ok)
			{
				std::cerr << XLW__HERE__ << " Warning: Unable to initialise PATH to directory of library " << std::endl;
			}

			// Displays a message in the status bar.
			xlw::XlfExcel::Instance().SendMessage("Registering library...");

			xlw::XLRegistration::ExcelFunctionRegistrationRegistry::Instance().DoTheRegistrations();

			// Clears the status bar.
			xlw::XlfExcel::Instance().SendMessage();
			return 1;

		} catch(...) {
			return 0;
		}
	}

	long EXCEL_EXPORT xlAutoClose()
	{
		std::cerr << XLW__HERE__ << "Releasing ressources" << std::endl;
		delete &xlw::XlfExcel::Instance();
		std::cerr.rdbuf(oldStreamBuf);
		return 1;
	}

}

