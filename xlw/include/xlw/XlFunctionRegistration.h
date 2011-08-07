
/*
 Copyright (C) 2006 Mark Joshi
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2011 Narinder S Claire

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#if !defined(REGISTER_XL_FUNCTION_H)
#define REGISTER_XL_FUNCTION_H


#include <string>
#include <vector>
#include <list>
#include <xlw/XlfExcel.h>
#include <xlw/Singleton.h>
#include <xlw/eshared_ptr.h>
#include <xlw/XlfFuncDesc.h>
#include <xlw/XlfCmdDesc.h>


namespace xlw {

    namespace XLRegistration
    {

    struct Arg { const char * ArgumentName; const char * ArgumentDescription; const char * ArgumentType; };

    class XLCommandRegistrationData
    {
    public:
        XLCommandRegistrationData(const std::string& CommandName_,
                                  const std::string& ExcelCommandName_,
                                  const std::string& Comment_,
                                  const std::string& Menu_,
                                  const std::string& MenuText_):
                                  CommandName(CommandName_),
                                  ExcelCommandName(ExcelCommandName_),
                                  Comment(Comment_),
                                  Menu(Menu_),
                                  MenuText(MenuText_){}
        

        const std::string& GetCommandName() const;
        const std::string& GetExcelCommandName() const;
        const std::string& GetCommandComment() const;
        const std::string& GetMenu() const;
        const std::string& GetMenuText() const;


    private:
        std::string CommandName;
        std::string ExcelCommandName;
        std::string Comment;
        std::string Menu;
        std::string MenuText;

    
    };
    

    class XLFunctionRegistrationData
    {
    public:
          XLFunctionRegistrationData(const std::string& FunctionName_,
                         const std::string& ExcelFunctionName_,
                         const std::string& FunctionDescription_,
                         const std::string& Library_,
                         const Arg Arguments[],
                         int NoOfArguments_,
                         bool Volatile_,
                         bool Threadsafe_,
                         const std::string &ReturnTypeCode_,
                         const std::string &HelpID_,
                         bool Asynchronous_,
                         bool MacroSheetEquivalent_,
                         bool ClusterSafe_);

        const std::string&  GetFunctionName() const;
        const std::string&  GetExcelFunctionName() const;
        const std::string&  GetFunctionDescription() const;
        const std::string&  GetLibrary() const;
        int GetNoOfArguments() const;
        const std::vector<std::string>&  GetArgumentNames() const;
        const std::vector<std::string>&  GetArgumentDescriptions() const;
        const std::vector<std::string>&  GetArgumentTypes() const;

        bool GetVolatile() const
        {
            return Volatile;
        }

        bool GetThreadsafe() const
        {
            return Threadsafe;
        }

        bool GetAsynchronous() const
        {
            return Asynchronous;
        }

        bool GetMacroSheetEquivalent() const
        {
            return MacroSheetEquivalent;
        }

        bool GetClusterSafe() const
        {
            return ClusterSafe;
        }

        const std::string & GetReturnTypeCode() const;
        const std::string & GetHelpID() const;
    private:

        std::string FunctionName;
        std::string ExcelFunctionName;
        std::string FunctionDescription;
        std::string Library;
        int NoOfArguments;
        std::vector<std::string> ArgumentNames;
        std::vector<std::string> ArgumentDescriptions;
        std::vector<std::string> ArgumentTypes;
        bool Volatile;
        bool Threadsafe;
        std::string ReturnTypeCode;
        std::string helpID;
        bool Asynchronous;
        bool MacroSheetEquivalent;
        bool ClusterSafe;
    };

    class XLFunctionRegistrationHelper
    {
    public:

        XLFunctionRegistrationHelper(const std::string& FunctionName,
                         const std::string& ExcelFunctionName,
                         const std::string& FunctionDescription,
                         const std::string& Library,
                         const Arg Args[] = 0,
                         int NoOfArguments = 0,
                         bool Volatile = false,
                         bool Threadsafe = false,
                         const std::string &ReturnTypeCode_ = "",
                         const std::string &HelpID = "",
                         bool Asynchronous = false,
                         bool MacroSheetEquivalent = false,
                         bool ClusterSafe = false);

    };

     class XLCommandRegistrationHelper
    {
    public:

        XLCommandRegistrationHelper(const std::string& CommandName_,
                                  const std::string& ExcelCommandName_,
                                  const std::string& Comment_,
                                  const std::string& Menu_,
                                  const std::string& MenuText_);

    };


    // singleton pattern, cf the Factory
    class ExcelFunctionRegistrationRegistry: public singleton<ExcelFunctionRegistrationRegistry>
    {
    friend class singleton<ExcelFunctionRegistrationRegistry>;
    public:
        void DoTheRegistrations() const;
        void DoTheDeregistrations() const;
        void AddFunction(const XLFunctionRegistrationData&);
        void AddCommand(const XLCommandRegistrationData&);
        void GenerateDocumentation(const std::string& outputDir);
    private:
        typedef std::map<std::string,xlw_tr1::shared_ptr<xlw::XlfFuncDesc> > functionCache;
        typedef std::map<std::string,xlw_tr1::shared_ptr<XlfCmdDesc> > commandCache;
        ExcelFunctionRegistrationRegistry(){}
        void GenerateChmBuilderConfig(const std::string& fileName);
        void GenerateToc(const std::string& outputDir);
        std::map<std::string,xlw_tr1::shared_ptr<XlfFuncDesc> > Functions;
        std::map<std::string,xlw_tr1::shared_ptr<XlfCmdDesc> >  Commands;

    };

    }

}

#endif

