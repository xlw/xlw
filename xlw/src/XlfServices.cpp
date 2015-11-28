/*
Copyright (C) 1998, 1999, 2001, 2002, 2003, 2004 Jérôme Lecomte
Copyright (C) 2007, 2008 Eric Ehlers
Copyright (C) 2009 2011 Narinder S Claire
Copyright (C) 2011, 2013 John Adcock
Copyright (C) 2013 Anjum Raheel

This file is part of XLW, a free-software/open-source C++ wrapper of the
Excel C API - http://xlw.sourceforge.net/

XLW is free software: you can redistribute it and/or modify it under the
terms of the XLW license.  You should have received a copy of the
license along with this program; if not, please email xlw-users@lists.sf.net

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <xlw/XlfServices.h>
#include <xlw/XlfExcel.h>
#include <xlw/XlfOper.h>
#include <string>
#include <cstdio>
#include <stdexcept>

namespace xlw
{
    struct Services_t XlfServices;

    // create a series of CallFunction and CallCommand function with variable
    // numbers of XlfOper arguments to simplify the calling of Xlm macros
    // by getting the compiler to create any temporary XlfOpers if we pass in 
    // native types
    namespace
    {
        inline XlfOper CallFunction(int xlfn, const char* errorString)
        {
            XlfOper result;
            int err = XlfExcel::Instance().Callv(xlfn, result, 0, 0);
            if(err != xlretSuccess)
            {
                THROW_XLW(errorString << " failed with result code " << err);
            }
            return result;
        }

        inline XlfOper CallFunction(int xlfn, const XlfOper& param1, const char* errorString)
        {
            XlfOper result;
            const LPXLFOPER params[] = {param1};
            int err = XlfExcel::Instance().Callv(xlfn, result, 1, params);
            if(err != xlretSuccess)
            {
                THROW_XLW(errorString << " failed with result code " << err);
            }
            return result;
        }

        inline XlfOper CallFunction(int xlfn, const XlfOper& param1, const XlfOper& param2, const char* errorString)
        {
            XlfOper result;
            const LPXLFOPER params[] = {param1, param2};
            int err = XlfExcel::Instance().Callv(xlfn, result, 2, params);
            if(err != xlretSuccess)
            {
                THROW_XLW(errorString << " failed with result code " << err);
            }
            return result;
        }

        inline XlfOper CallFunction(int xlfn, const XlfOper& param1, const XlfOper& param2, const XlfOper& param3, const char* errorString)
        {
            XlfOper result;
            const LPXLFOPER params[] = {param1, param2, param3};
            int err = XlfExcel::Instance().Callv(xlfn, result, 3, params);
            if(err != xlretSuccess)
            {
                THROW_XLW(errorString << " failed with result code " << err);
            }
            return result;
        }

        inline XlfOper CallFunction(int xlfn, const XlfOper& param1, const XlfOper& param2, const XlfOper& param3, const XlfOper& param4, const char* errorString)
        {
            XlfOper result;
            const LPXLFOPER params[] = {param1, param2, param3, param4};
            int err = XlfExcel::Instance().Callv(xlfn, result, 4, params);
            if(err != xlretSuccess)
            {
                THROW_XLW(errorString << " failed with result code " << err);
            }
            return result;
        }

        inline void CallCommand(int xlcmd, const char* errorString)
        {
            XlfOper result;
            int err = XlfExcel::Instance().Callv(xlcmd, result, 0, 0);
            if(err != xlretSuccess)
            {
                THROW_XLW(errorString << " failed with result code " << err);
            }
        }

        inline void CallCommand(int xlcmd, const XlfOper& param1, const char* errorString)
        {
            XlfOper result;
            const LPXLFOPER params[] = {param1};
            int err = XlfExcel::Instance().Callv(xlcmd, result, 1, params);
            if(err != xlretSuccess)
            {
                THROW_XLW(errorString << " failed with result code " << err);
            }
        }

        inline void CallCommand(int xlcmd, const XlfOper& param1, const XlfOper& param2, const char* errorString)
        {
            XlfOper result;
            const LPXLFOPER params[] = {param1, param2};
            int err = XlfExcel::Instance().Callv(xlcmd, result, 2, params);
            if(err != xlretSuccess)
            {
                THROW_XLW(errorString << " failed with result code " << err);
            }
        }

        inline void CallCommand(int xlcmd, const XlfOper& param1, const XlfOper& param2, const XlfOper& param3, const char* errorString)
        {
            XlfOper result;
            const LPXLFOPER params[] = {param1, param2, param3};
            int err = XlfExcel::Instance().Callv(xlcmd, result, 3, params);
            if(err != xlretSuccess)
            {
                THROW_XLW(errorString << " failed with result code " << err);
            }
        }

        inline void CallCommand(int xlcmd, const XlfOper& param1, const XlfOper& param2, const XlfOper& param3, const XlfOper& param4, const char* errorString)
        {
            XlfOper result;
            const LPXLFOPER params[] = {param1, param2, param3, param4};
            int err = XlfExcel::Instance().Callv(xlcmd, result, 4, params);
            if(err != xlretSuccess)
            {
                THROW_XLW(errorString << " failed with result code " << err);
            }
        }
    }


    StatusBar_t & StatusBar_t::operator=(const std::string &message)
    {
        CallCommand(xlcMessage, true, message, "Set Status Bar");
        return *this;
    }

    void StatusBar_t::clear()
    {
        CallCommand(xlcMessage, 0, false, "Clear Status Bar");
    }

    XlfOper Notes_t::GetNote(const XlfOper& cellRef, int startCharacter, int numChars)
    {
        if(numChars == 0)
        {
            return CallFunction(xlfGetNote, cellRef, startCharacter + 1, "Get Note");
        }
        else
        {
            return CallFunction(xlfGetNote, cellRef, startCharacter + 1, numChars, "Get Note");
        }
    }

    void Notes_t::SetNote(const XlfOper& cellRef, const std::string& note)
    {
        CallCommand(xlcNote, note, cellRef, "Set Note");
    }
    
    void Notes_t::ClearNote(const XlfOper& cellRef)
    {
        CallCommand(xlcNote, XlfOper(), cellRef, "Clear Note");
    }

    XlfOper Information_t::GetCallingCell()
    {
        return CallFunction(xlfCaller, "Calling Cell");
    }

    XlfOper Information_t::GetActiveCell()
    {
        return CallFunction(xlfActiveCell, "Get Active Cell");
    }

    XlfOper Information_t::GetActiveRange()
    {
        return CallFunction(xlfSelection, "Get Active Range");
    }

    void Information_t::SetActiveCell(const XlfOper& ref)
    {
        CallCommand(xlcSelect, ref, "Set Active Cell");
    }

    std::string Information_t::GetFormula(const XlfOper& cellRef)
    {
        int flag = (XlfExcel::Instance().isEnglish()?0:xlIntl);
        return CallFunction(xlfGetFormula | flag, cellRef, "Get Formula").AsString();
    }

    std::string Information_t::ConvertA1FormulaToR1C1(std::string a1Formula)
    {
        return CallFunction(xlfFormulaConvert, a1Formula, true, false, 1, "Formula Convert").AsString();
    }

    std::string Information_t::ConvertR1C1FormulaToA1(std::string r1c1Formula, bool fixRows, bool fixColums)
    {
        int toRefType(4 - fixRows?2:0 - fixColums?1:0);
        return CallFunction(xlfFormulaConvert, r1c1Formula, false, true, toRefType, "Formula Convert").AsString();
    }

    XlfOper Information_t::GetCellRefA1(std::string a1Location)
    {
        return CallFunction(xlfTextref, a1Location, true, "Text Ref");
    }

    XlfOper Information_t::GetCellRefR1C1(std::string r1c1Location)
    {
        return CallFunction(xlfTextref, r1c1Location, false, "Text Ref");
    }

    XlfOper Information_t::GetCellRefR1C1(XlfOper referenceCell, std::string r1c1RelativeLocation)
    {
        return CallFunction(xlfAbsref, r1c1RelativeLocation, referenceCell, "Abs Ref");
    }

    std::string Information_t::GetRefTextA1(const XlfOper& ref)
    {
        return CallFunction(xlfReftext, ref, true, "Ref Text").AsString();
    }
    
    std::string Information_t::GetRefTextR1C1(const XlfOper& ref)
    {
        return CallFunction(xlfReftext, ref, false, "Ref Text").AsString();
    }

    std::string Information_t::GetSheetName(const XlfOper& ref)
    {
        return CallFunction(xlSheetNm, ref, "Get Sheet Name").AsString();
    }

    IDSHEET Information_t::GetCurrentSheetId()
    {

        XLFOPER result;
        int err = XlfExcel::Instance().Callv(xlSheetId, &result, 0, 0);
        if(err != xlretSuccess)
        {
            THROW_XLW("xlSheetId failed with result code " << err);
        }
        if (XlfExcel::Instance().excel12())
            return result.oper12.val.mref.idSheet;
        else
            return result.oper4.val.mref.idSheet;
    }

    XlfOper Cell_t::GetContents(const XlfOper& ref)
    {
        int flag = (XlfExcel::Instance().isEnglish()?0:xlIntl);
        return CallFunction(xlfGetFormula | flag, "Get Cell Formula");
    }

    void Cell_t::SetContents(const XlfOper& ref, const XlfOper& newValue)
    {
        int flag = (XlfExcel::Instance().isEnglish()?0:xlIntl);
        CallCommand(xlcFormula | flag, newValue, ref, "Set Cell Contents");
    }

    double Cell_t::GetHeight(const XlfOper& ref)
    {
        return CallFunction(xlfGetCell, 17, ref, "Get Cell Height").AsDouble();
    }

    void Cell_t::SetHeight(const XlfOper& ref, double newPoints)
    {
        CallCommand(xlcRowHeight, newPoints, "Set Row Height");
    }

    double Cell_t::GetWidth(const XlfOper& ref)
    {
        // there is no get width function so we work it
        // out using the distances from far left
        double distRight(CallFunction(xlfGetCell, 44, ref, "Get Right Position").AsDouble());
        double distLeft(CallFunction(xlfGetCell, 42, ref, "Get Left Position").AsDouble());
        return distRight - distLeft;
    }
    
    void Cell_t::SetWidth(const XlfOper& ref, double newPoints)
    {
        CallCommand(xlcColumnWidth, newPoints, "Set Cell Width");
    }

    std::string Cell_t::GetFont(const XlfOper& ref)
    {
        return CallFunction(xlfGetCell, 18, ref, "Get Cell Font").AsString();
    }

    namespace
    {
        void setFontProperties(const XlfOper& ref, const XlfOper& fontName, const XlfOper& fontSize)
        {
            XlfOper currentCell(XlfServices.Information.GetActiveCell());
            XlfServices.Commands.Select(ref);

            XlfOper missingValue;
            const LPXLFOPER params[] = {
                                    fontName, missingValue,
                                    fontSize, missingValue, missingValue, missingValue,
                                    missingValue, missingValue, missingValue, missingValue,
                                    missingValue, missingValue, missingValue, missingValue
                                 };
            int err = XlfExcel::Instance().Callv(xlcFontProperties, 0, 14, params);
            XlfServices.Commands.Select(currentCell);
            if(err != xlretSuccess)
            {
                THROW_XLW("Set Font Properties failed with code " << err);
            }
        }
    }

    void Cell_t::SetFont(const XlfOper& ref, const std::string& newFont)
    {
        setFontProperties(ref, newFont, XlfOper());
    }

    double Cell_t::GetFontSize(const XlfOper& ref)
    {
        return CallFunction(xlfGetCell, 19, ref, "Get Cell Font").AsDouble();
    }

    void Cell_t::SetFontSize(const XlfOper& ref, double newFontSize)
    {
        setFontProperties(ref, XlfOper(), newFontSize);
    }

    void Commands_t::Alert(const std::string& message)
    {
        CallCommand(xlcAlert, message, "Alert Command");
    }

    std::string Commands_t::InputFormula(const std::string& message, const std::string& title, const std::string& defaultValue)
    {
        return CallFunction(xlfInput, message, 0, title, defaultValue, "Input Formula").AsString();
    }

    double Commands_t::InputNumber(const std::string& message, const std::string& title, double defaultValue)
    {
        return CallFunction(xlfInput, message, 1, title, defaultValue, "Input Number").AsDouble();
    }

    std::string Commands_t::InputText(const std::string& message, const std::string& title, const std::string& defaultValue)
    {
        return CallFunction(xlfInput, message, 2, title, defaultValue, "Input Text").AsString();
    }

    bool Commands_t::InputBool(const std::string& message, const std::string& title)
    {
        return CallFunction(xlfInput, message, 4, title, "Input Bool").AsBool();
    }

    XlfOper Commands_t::InputReference(const std::string& message, const std::string& title, const std::string& defaultValue)
    {
        return CallFunction(xlfInput, message, 8, title, defaultValue, "Input Reference");
    }

    XlfOper Commands_t::InputArray(const std::string& message, const std::string& title)
    {
        return CallFunction(xlfInput, message, 64, title, "Input Array");
    }

    void Commands_t::Select(const XlfOper& ref)
    {
        CallCommand(xlcSelect, ref, "Select Range");
    }

    XlfOper Commands_t::ShowDialogBox(const XlfOper& dialogData)
    {
        return CallFunction(xlfDialogBox, dialogData, "Show Dialog Box");
    }

    void Commands_t::InsertWorkSheet()
    {
        CallCommand(xlcWorkbookInsert, 1, "Worksheet Insert");
    }
    
    void Commands_t::InsertMacroWorkSheet()
    {
        CallCommand(xlcWorkbookInsert, 3, "Insert Macro Sheet");
    }
    
    void Commands_t::SelectPreviousSheet()
    {
        CallCommand(xlcWorkbookPrev, "Select Previous Sheet");
    }
    
    void Commands_t::SelectNextSheet()
    {
        CallCommand(xlcWorkbookNext, "Select Next Sheet");
    }

    void Commands_t::SetScreenUpdates(bool doesScreenUpdate)
    {
        CallCommand(xlcEcho, doesScreenUpdate, "Echo");
    }

    DisableCalculation::DisableCalculation()
    {
        calulationState_ = CallFunction(xlfGetDocument, 14, "Get Document properies for calculation").AsInt();
        if(calulationState_ < 3)
        {
            CallCommand(xlcOptionsCalculation, 3, "Set calculation optiosn");
        }
    }

    DisableCalculation::~DisableCalculation()
    {
        if(calulationState_ < 3)
        {
            CallCommand(xlcOptionsCalculation, calulationState_, "Set calculation optiosn");
        }
    }
}
