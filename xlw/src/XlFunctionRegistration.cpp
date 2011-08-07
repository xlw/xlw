/*
Copyright (C) 2006 Mark Joshi
Copyright (C) 2007, 2008 Eric Ehlers
Copyright (C) 2011 Narinder S Claire
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


#include <xlw/XlFunctionRegistration.h>
#include <xlw/xlfFuncDesc.h>
#include <xlw/xlfCmdDesc.h>
#include <xlw/xlfArgDescList.h>
#include <stdio.h>
#include <fstream>
#include <sstream>

using namespace xlw;
using namespace XLRegistration;

XLFunctionRegistrationData::XLFunctionRegistrationData(const std::string& FunctionName_,
    const std::string& ExcelFunctionName_,
    const std::string& FunctionDescription_,
    const std::string& Library_,
    const Arg Arguments[],
    int NoOfArguments_,
    bool Volatile_,
    bool Threadsafe_,
    const std::string& ReturnTypeCode_,
    const std::string& HelpID_,
    bool Asynchronous_,
    bool MacroSheetEquivalent_,
    bool ClusterSafe_)
    :                FunctionName(FunctionName_),
    ExcelFunctionName(ExcelFunctionName_),
    FunctionDescription(FunctionDescription_),
    Library(Library_),
    NoOfArguments(NoOfArguments_),
    Volatile(Volatile_),
    Threadsafe(Threadsafe_),
    ReturnTypeCode(ReturnTypeCode_),
    helpID(HelpID_),
    Asynchronous(Asynchronous_),
    MacroSheetEquivalent(MacroSheetEquivalent_),
    ClusterSafe(ClusterSafe_)
{

    ArgumentNames.reserve(NoOfArguments);
    ArgumentDescriptions.reserve(NoOfArguments);

    for (int i=0; i < NoOfArguments; i++)
    {
        ArgumentNames.push_back(Arguments[i].ArgumentName);
        ArgumentDescriptions.push_back(Arguments[i].ArgumentDescription);
        ArgumentTypes.push_back(Arguments[i].ArgumentType);
    }
}




const std::string & XLFunctionRegistrationData::GetFunctionName() const
{
    return FunctionName;
}
const std::string & XLFunctionRegistrationData::GetExcelFunctionName() const
{
    return ExcelFunctionName;
}
const std::string & XLFunctionRegistrationData::GetFunctionDescription() const
{
    return FunctionDescription;
}

const std::string &  XLFunctionRegistrationData::GetReturnTypeCode() const
{
    return ReturnTypeCode;
}

const std::string & XLFunctionRegistrationData::GetHelpID() const
{
    return helpID;
}

const std::string & XLFunctionRegistrationData::GetLibrary() const
{
    return Library;
}

int XLFunctionRegistrationData::GetNoOfArguments() const{
    return NoOfArguments;
}

const std::vector<std::string> & XLFunctionRegistrationData::GetArgumentNames() const
{
    return ArgumentNames;
}

const std::vector<std::string> & XLFunctionRegistrationData::GetArgumentDescriptions() const
{
    return ArgumentDescriptions;
}

const std::vector<std::string> & XLFunctionRegistrationData::GetArgumentTypes() const
{
    return ArgumentTypes;
}



const std::string& XLCommandRegistrationData::GetCommandName() const
{
    return CommandName ; 
}


const std::string& XLCommandRegistrationData::GetExcelCommandName() const
{
    return ExcelCommandName ; 
}


const std::string& XLCommandRegistrationData::GetCommandComment() const
{
    return Comment ; 
}


const std::string& XLCommandRegistrationData::GetMenu() const
{
    return  Menu; 
}

const std::string& XLCommandRegistrationData::GetMenuText() const
{
    return  MenuText; 
}


XLFunctionRegistrationHelper::XLFunctionRegistrationHelper(const std::string& FunctionName,
    const std::string& ExcelFunctionName,
    const std::string& FunctionDescription,
    const std::string& Library,
    const Arg Args[],
    int NoOfArguments,
    bool Volatile,
    bool Threadsafe,
    const std::string& returnTypeCode,
    const std::string& helpID,
    bool Asynchronous,
    bool MacroSheetEquivalent,
    bool ClusterSafe)
{
    XLFunctionRegistrationData tmp(FunctionName,
        ExcelFunctionName,
        FunctionDescription,
        Library,
        Args,
        NoOfArguments,
        Volatile,
        Threadsafe,
        returnTypeCode,
        helpID,
        Asynchronous,
        MacroSheetEquivalent,
        ClusterSafe);

    ExcelFunctionRegistrationRegistry::Instance().AddFunction(tmp);
}

XLCommandRegistrationHelper::XLCommandRegistrationHelper(const std::string& CommandName,
    const std::string& ExcelCommandName,
    const std::string& Comment,
    const std::string& Menu,
    const std::string& MenuText)
{
    XLCommandRegistrationData tmp(CommandName,
        ExcelCommandName,
        Comment,
        Menu,
        MenuText);

    ExcelFunctionRegistrationRegistry::Instance().AddCommand(tmp);
}

void ExcelFunctionRegistrationRegistry::DoTheRegistrations() const
{
    int counter(1);

    for (functionCache::const_iterator it = Functions.begin(); it !=  Functions.end(); ++it)
    {
        it->second->Register(counter);
        ++counter;
    }


    for (commandCache::const_iterator it = Commands.begin(); it !=  Commands.end(); ++it)
    {
        it->second->Register(counter);
        it->second->AddToMenuBar();
        ++counter;
    }
}

void ExcelFunctionRegistrationRegistry::DoTheDeregistrations() const
{
    for (functionCache::const_iterator it = Functions.begin(); it !=  Functions.end(); ++it)
    {
        it->second->Unregister();
    }


    for (commandCache::const_iterator it = Commands.begin(); it !=  Commands.end(); ++it)
    {
        it->second->RemoveFromMenuBar();
        it->second->Unregister();
    }


}

void ExcelFunctionRegistrationRegistry::AddFunction(const XLFunctionRegistrationData& data)
{
    
    XlfFuncDesc::RecalcPolicy policy = data.GetVolatile() ? XlfFuncDesc::Volatile : XlfFuncDesc::NotVolatile;
    xlw_tr1::shared_ptr<XlfFuncDesc>  xlFunction( new XlfFuncDesc(
            data.GetFunctionName(),
            data.GetExcelFunctionName(),
            data.GetFunctionDescription(),
            data.GetLibrary(),
            policy,
            data.GetThreadsafe(),
            data.GetReturnTypeCode(),
            data.GetHelpID(),
            data.GetAsynchronous(),
            data.GetMacroSheetEquivalent(),
            data.GetClusterSafe()));
        XlfArgDescList xlFunctionArgs;

        for (int i=0; i < data.GetNoOfArguments(); ++i)
        {
            XlfArgDesc ThisArgumentDescription(data.GetArgumentNames()[i],
                data.GetArgumentDescriptions()[i],
                data.GetArgumentTypes()[i]);
            xlFunctionArgs + ThisArgumentDescription;
            
        }
 
    xlFunction->SetArguments(xlFunctionArgs);
    Functions[data.GetExcelFunctionName()] = xlFunction;
}
void ExcelFunctionRegistrationRegistry::AddCommand(const XLCommandRegistrationData& data)
{
    
        xlw_tr1::shared_ptr<XlfCmdDesc>  
            theCommand(new XlfCmdDesc(data.GetCommandName(),
            data.GetExcelCommandName(),
            data.GetCommandComment(),
            data.GetMenu(),
            data.GetMenuText(),
            !data.GetMenu().empty()));

        Commands[data.GetExcelCommandName()] = theCommand;
}

void ExcelFunctionRegistrationRegistry::GenerateChmBuilderConfig(const std::string& fileName)
{
    std::ofstream outFile(fileName.c_str());

    outFile << "<?xml version=\"1.0\" encoding=\"utf-8\" ?>" << std::endl;
    outFile << "<configuration>" << std::endl;
    outFile << "<languages>" << std::endl;
    outFile << "<language id=\"1033\" codepage=\"65001\" name=\"0x409 English (United States)\" />" << std::endl;
    outFile << "</languages>" << std::endl;
    outFile << "<chmTitles>" << std::endl;
    outFile << "<title projectName=\"Xlw\">Add-in Help</title>" << std::endl;
    outFile << "</chmTitles>" << std::endl;
    outFile << "<hhpTemplate>" << std::endl;
    outFile << "<line>[OPTIONS]</line>" << std::endl;
    outFile << "<line>Compatibility=1.1 or later</line>" << std::endl;
    outFile << "<line>Compiled file={0}.chm</line>" << std::endl;
    outFile << "<line>Contents file={0}.hhc</line>" << std::endl;
    outFile << "<line>Default Topic={1}</line>" << std::endl;
    outFile << "<line>Full-text search=Yes</line>" << std::endl;
    outFile << "<line>Language={2}</line>" << std::endl;
    outFile << "<line>Title={3}</line>" << std::endl;
    outFile << "<line>[FILES]</line>" << std::endl;
    outFile << "<line>icons\\*.gif</line>" << std::endl;
    outFile << "<line>art\\*.gif</line>" << std::endl;
    outFile << "<line>media\\*.gif</line>" << std::endl;
    outFile << "<line>scripts\\*.js</line>" << std::endl;
    outFile << "<line>styles\\*.css</line>" << std::endl;
    outFile << "<line>html\\*.htm</line>" << std::endl;
    outFile << "<line>[ALIAS]</line>" << std::endl;
    int counter(1);
    for (functionCache::const_iterator it = Functions.begin(); it !=  Functions.end(); ++it)
    {
        outFile << "<line>A" << counter << "=html\\" << it->second->GetAlias() << ".htm</line>" << std::endl;
        ++counter;
    }
    for (commandCache::const_iterator it = Commands.begin(); it !=  Commands.end(); ++it)
    {
        outFile << "<line>A" << counter << "=html\\" << it->second->GetAlias() << ".htm</line>" << std::endl;
        ++counter;
    }
    outFile << "<line>[MAP]</line>" << std::endl;
    outFile << "<line>#include alias.h</line>" << std::endl;
    outFile << "<line>[INFOTYPES]</line>" << std::endl;
    outFile << "</hhpTemplate>" << std::endl;
    outFile << "</configuration>" << std::endl;
}

void ExcelFunctionRegistrationRegistry::GenerateToc(const std::string& fileName)
{
    std::ofstream outFile(fileName.c_str());

    outFile << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << std::endl;
    outFile << "<topics>" << std::endl;
    int counter(1);
    if(Functions.size() > 0)
    {
        outFile << "<topic id=\"Functions\" file=\"Functions\">" << std::endl;
        for (functionCache::const_iterator it = Functions.begin(); it !=  Functions.end(); ++it)
        {
            outFile << "<topic id=\"" << it->second->GetAlias() << "\" file=\"" << it->second->GetAlias() << "\" />" << std::endl;
            ++counter;
        }
        outFile << "</topic>" << std::endl;
    }
    if(Commands.size() > 0)
    {
        outFile << "<topic id=\"Commands\" file=\"Commands\">" << std::endl;
        for (commandCache::const_iterator it = Commands.begin(); it !=  Commands.end(); ++it)
        {
            outFile << "<topic id=\"" << it->second->GetAlias() << "\" file=\"" << it->second->GetAlias() << "\" />" << std::endl;
            ++counter;
        }
        outFile << "</topic>" << std::endl;
    }
    outFile << "</topics>" << std::endl;

}

void ExcelFunctionRegistrationRegistry::GenerateDocumentation(const std::string& outputDir)
{
    GenerateChmBuilderConfig(outputDir + "\\ChmBuilder.config");
    GenerateToc(outputDir + "\\toc.xml");
    int counter(1);
    for (functionCache::const_iterator it = Functions.begin(); it !=  Functions.end(); ++it)
    {
        it->second->GenerateMamlDocs(outputDir, counter);
        ++counter;
    }

    for (commandCache::const_iterator it = Commands.begin(); it !=  Commands.end(); ++it)
    {
        it->second->GenerateMamlDocs(outputDir, counter);
        ++counter;
    }
}

extern "C"
{
    // only do documentation in the debug build to avoid bloating up the released xlls
    void EXCEL_EXPORT xlwGenDoc(const char* outputDir)
    {
#ifndef NDEBUG
        ExcelFunctionRegistrationRegistry::Instance().GenerateDocumentation(outputDir);
#endif
    }
}


