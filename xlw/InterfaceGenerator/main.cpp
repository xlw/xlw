//
//
//                                    main.cpp
//
//
/*
Copyright (C) 2006, 2008 Mark Joshi
Copyright (C) 2011  Narinder Claire

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
#include <fstream>
#include "Functionizer.h"
#include "FunctionModel.h"
#include "FunctionType.h"
#include "Outputter.h"
#include "ManagedOutputter.h"
#include "ParserData.h"
#include "Tokenizer.h"
#include "Strip.h"
using namespace std;


int main(int argc, char *argv[])
{
	cout << "XLW InterfaceGenerator" << endl;
	cout << "Copyright (c) XLW Project 2006-2011. All Rights Reserved" << endl;
	try
	{

		std::vector<std::string> args;
		std::vector<std::string> options;

		for (int i=1; i < argc; ++i)
		{
			std::string arg(argv[i]);
			if (arg.size()>0 && arg[0] =='-')
				options.push_back(arg);
			else
				args.push_back(arg);

		}

		if (args.size() < 1 || args.size() > 2)
			throw("usage is :\n "
			"          inputfile \n"
			"          inputfile outputfile \n"
			"      -m  inputfile "
			"      -m  inputfile outputdirectory");
		std::string inputfile(args[0]);

		bool clw = false;
		bool managed_flag = false;

		for (std::vector<std::string>::const_iterator it = options.begin(); it != options.end(); ++it)
		{
			if (*it == "-c")
			{
				clw = true;
			}
			else if (*it == "-m")
			{
				managed_flag = true;
			}
			else
			{
				std::cerr << "unknown option ignored: " << *it << "\n";
			}

		}


		std::string outputfile;
		std::string managed_outputfile_h;
		std::string managed_outputfile_cpp;

		std::string dirname(getdir(inputfile));

		std::string outputDir = dirname;


		if ( !managed_flag && args.size()==2)
		{
			outputfile = args[1];
		}
		else
		{
			if (managed_flag && args.size()==2)
			{
				outputDir = args[1];
			}

			if (clw)
				outputfile= "clw";
			else
			{

				outputfile = "xlw";
				managed_outputfile_h = "mxlw";

			}
			std::string libName(strip(inputfile));
			for (unsigned long i=0; i < libName.size(); i++)
			{
				if (libName[i] == '.')
					break;
				PushBack(outputfile,libName[i]);
				PushBack(managed_outputfile_h,libName[i]);
			}

			outputfile += ".cpp";
			managed_outputfile_cpp = managed_outputfile_h + ".cpp";
			managed_outputfile_h +=".h";
		}

		ifstream input(inputfile.c_str());
		if (!input)
			throw("input file not found :"+inputfile+"\n");

		std::vector<char> inputvector;

		char c;
		while (input.get(c))
		{
			int i = static_cast<int>(c);
			if (i<32 && c!='\n')
				c=' '; // strip out special characters
			inputvector.push_back(c);
		}

		std::vector<FunctionDescription> managedFunctionVector;
		std::string LibraryName(inputfile);

		std::vector<std::string> openMethods;
		std::vector<std::string> closeMethods;

		if(managed_flag)
		{
			std::cout << "manged file has been read in\n";

			std::vector<Token> tokenVector1(Tokenize(inputvector));
			std::cout << "manged file has been tokenized\n";

			std::vector<Token> tokenVector2(Strip(tokenVector1));
			std::cout << "manged file has been stripped\n";

			LibraryName = inputfile;// use input file name as default library name



			std::vector<FunctionModel> managedModelVector( ConvertToFunctionModel(tokenVector2,LibraryName,openMethods,closeMethods));

			std::cout << "managed_flag file has been function modeled\n";

			managedFunctionVector = FunctionTyper<managed>(managedModelVector);

			std::cout << "managed_flag file has been function described\n";

			std::vector<char> outputVector_h;
			std::vector<char> outputVector_cpp;

			OutputFileCreatorMan(managedFunctionVector,inputfile,LibraryName,outputVector_h,outputVector_cpp);
			inputfile = managed_outputfile_h;

			managed_outputfile_h = outputDir+"/" + managed_outputfile_h;

			std::cout << " .. writing " <<  managed_outputfile_h <<  "\n";
			writeOutputFile( managed_outputfile_h,outputVector_h);
			std::cout << " .. writing " << (outputDir+"/" + managed_outputfile_cpp) <<  "\n";
			writeOutputFile(outputDir+"/" + managed_outputfile_cpp,outputVector_cpp);

			outputfile = outputDir+"/" + outputfile;

			inputvector.resize(0);

			ifstream input( managed_outputfile_h.c_str());
			if (!input)
				throw("input file not found :"+inputfile+"\n");

			char c;
			while (input.get(c))
			{
				int i = static_cast<int>(c);
				if (i<32 && c!='\n')
					c=' '; // strip out special characters
				inputvector.push_back(c);
			}

		}

		{
			std::cout << "file has been read in\n";

			std::vector<Token> tokenVector1(Tokenize(inputvector));
			std::cout << "file has been tokenized\n";

			std::vector<Token> tokenVector2(Strip(tokenVector1));
			std::cout << "file has been stripped\n";

			// use input file name as default library name

			std::vector<FunctionModel> modelVector(ConvertToFunctionModel(tokenVector2,LibraryName,openMethods,closeMethods));


			std::cout << "file has been function modeled\n";

			std::vector<FunctionDescription> functionVector(FunctionTyper<native>(modelVector));

			if(managed_flag)
			{
				FunctionDescription::Transit(managedFunctionVector, functionVector);
			}


			std::cout << "file has been function described\n";

			std::vector<char> outputVector_h;
			std::vector<char> outputVector_cpp;


			if (clw)
				outputVector_cpp = OutputFileCreatorCL(functionVector,
				inputfile);
			else
				outputVector_cpp = OutputFileCreator(functionVector,
				inputfile,LibraryName,openMethods,closeMethods);

			std::cout << " .. writing " << outputfile << "\n";
			writeOutputFile(outputfile,outputVector_cpp);
		}

		std::cout << "new file is a vector\n";


		std::cout << "all done\n";

	}
	catch (const char *c)
	{
		std::cout << "***ERROR***\n" << c << "\n***ERROR***\n";
	}
	catch (std::string c)
	{
		std::cout << "***ERROR***\n" << c << "\n***ERROR***\n";
	}
	catch (...)
	{
		std::cout << "***ERROR***\n" << "exception thrown" << "\n***ERROR***\n";
	}
	//char d;
	//std::cin >> d;
	return 0;
}
