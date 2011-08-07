/*
Copyright (C) 2011 John Adcock

This file is part of XLW, a free-software/open-source C++ wrapper of the
Excel C API - http://xlw.sourceforge.net/

XLW is free software: you can redistribute it and/or modify it under the
terms of the XLW license.  You should have received a copy of the
license along with this program; if not, please email xlw-users@lists.sf.net

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the license for more details.
*/
#include <iostream>
#include <string>
#include <stdexcept>
#include <windows.h>
using namespace std;

bool checkUsage(int argc, char *argv[])
{
    cout << "XlwDocGen" << endl;
    cout << "Copyright (c) Xlw Project 2011" << endl;
    if(argc != 2 && argc != 3)
    {
        cerr << "    Usage:" << endl;
        cerr << "        " << argv[0] << " fullPathToXllFile [OutputDir]" << endl;
        return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    try
    {
        if(!checkUsage(argc, argv))
        {
            return 1;
        }

        string xllFileName(argv[1]);
        string outputDir;
        if(argc == 3)
        {
            outputDir = argv[2];
        }
        else
        {
            string::size_type lastSlashPos = xllFileName.find_last_of("\\/");
            if(lastSlashPos != string::npos)
            {
                outputDir = xllFileName.substr(0, lastSlashPos);
            }
            else
            {
                outputDir = ".";
            }
        }

        typedef void (_cdecl *GenDocFunc)(const char*);

        // load up our xlcall dll first
        HINSTANCE xlcall32Instance = LoadLibrary("xlcall32.dll");
        if(!xlcall32Instance)
        {
            throw std::runtime_error("Can't find xlcall32.dll stub");
        }

        // then load up the xll to be documented
        HINSTANCE xllInstance = LoadLibrary(xllFileName.c_str());
        if(!xllInstance)
        {
            throw std::runtime_error("LoadLibrary failed");
        }

        // try and get our documentation function
        GenDocFunc genDocFunc = (GenDocFunc)GetProcAddress(xllInstance, "xlwGenDoc");
        if(!genDocFunc)
        {
            throw std::runtime_error("No export xlwGenDoc found");
        }

        cout << "Start Generating files in " << outputDir << endl;

        // generate the xml
        genDocFunc(outputDir.c_str());

        // clean up
        FreeLibrary(xllInstance);
        FreeLibrary(xlcall32Instance);

        cout << "Done" << endl;

        return 0;
    }
    catch(std::exception& e)
    {
        cerr << "Exception occured: " << e.what() << endl;
        cerr << "Exiting" << endl;
        return 2;
    }
    catch(...)
    {
        cerr << "An error has occured. Quitting ..." << endl;
        return 2;
    }
    return 3;
}
