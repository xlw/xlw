/*
Copyright (C) 2011 Narinder S Claire
Copyright (C) 2011 John Adcock
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
#ifndef XLFSERVICES_HEADER_GUARD
#define XLFSERVICES_HEADER_GUARD 
#include<string>
#include <xlw/XlfOper.h>

namespace xlw
{
    struct StatusBar_t
    {
        //! sets the status bar text
        StatusBar_t & operator=(const std::string &message);
        //! resets the status bar text
        void clear();
    };

    struct Notes_t
    {
        //! gets the text of the note attached to the cell from startCharacter (zero-based)
        XlfOper GetNote(const XlfOper& cellRef, int startCharacter = 0, int numChars = 0);
        //! sets the text of the note attached to the cell
        void SetNote(const XlfOper& cellRef, const std::string& note);
        //! clears the note attached to the cell
        void ClearNote(const XlfOper& cellRef);
    };

    struct Information_t
    {
        //! gets the reference of the calling cell
        XlfOper GetCallingCell();
        //! gets the reference of the active cell
        XlfOper GetActiveCell();
        //! sets the reference of the active cell
        void SetActiveCell(const XlfOper& ref);
        //! gets the formula in the supplied cell ref in R1C1 notation
        std::string GetFormula(const XlfOper& cellRef);
        //! convert a formula from A1 to R1C1 notation
        std::string ConvertA1FormulaToR1C1(std::string a1Formula);
        //! convert a formula from R1C1 to A1 notation
        std::string ConvertR1C1FormulaToA1(std::string r1c1Formula, bool fixRows = false, bool fixColums = false);
        //! convert A1 style string to a reference
        XlfOper GetCellRefA1(std::string a1Location);
        //! convert R1C1 string to a reference
        XlfOper GetCellRefR1C1(std::string r1c1Location);
        //! convert R[-1]C[1] string to a reference given another cell
        XlfOper GetCellRefR1C1(XlfOper referenceCell, std::string r1c1RelativeLocation);
        //! convert a reference to A1 style text
        std::string GetRefTextA1(const XlfOper& ref);
        //! convert a reference to R1C1 style text
        std::string GetRefTextR1C1(const XlfOper& ref);
        //! get sheet name for a reference
        std::string GetSheetName(const XlfOper& ref);
        //! get current sheet id
        int GetCurrentSheetId();
        //! gets the reference of the active range
		XlfOper GetActiveRange();
    };

    struct Cell_t
    {
        //! get Cell's contents
        XlfOper GetContents(const XlfOper& ref);
        //! set Cell's contents
        void SetContents(const XlfOper& ref, const XlfOper& newValue);
        //! get Cell's height in points
        double GetHeight(const XlfOper& ref);
        //! set Cell's height in points
        void SetHeight(const XlfOper& ref, double newPoints);
        //! get Cell's width in points
        double GetWidth(const XlfOper& ref);
        //! set Cell's width in points
        void SetWidth(const XlfOper& ref, double newPoints);
        //! get Cell's font name
        std::string GetFont(const XlfOper& ref);
        //! set Cell's font name
        void SetFont(const XlfOper& ref, const std::string& newFont);
        //! get Cell's font size in points
        double GetFontSize(const XlfOper& ref);
        //! set Cell's font size in points
        void SetFontSize(const XlfOper& ref, double newFontSize);
    };

    struct Commands_t
    {
        //! Sends an Excel alert message box
        void Alert(const std::string& message);
        //! Asks the user to input a forumla
        std::string InputFormula(const std::string& message, const std::string& title, const std::string& defaultValue = "");
        //! Asks the user to input a number
        double InputNumber(const std::string& message, const std::string& title, double defaultValue = 0);
        //! Asks the user to input a string
        std::string InputText(const std::string& message, const std::string& title, const std::string& defaultValue = "");
        //! Asks the user to input a boolean
        bool InputBool(const std::string& message, const std::string& title);
        //! Asks the user to input a reference
        XlfOper InputReference(const std::string& message, const std::string& title, const std::string& defaultValue = "");
        //! Sets the current selection
        void Select(const XlfOper& ref);
        //! Asks the user to input an array
        XlfOper InputArray(const std::string& message, const std::string& title);
        /** Display a Dialog Box
            Uses array in the format required for the Xlm DIALOG.BOX function.
            For more details on this function see MacroFun.hlp 
            http://support.microsoft.com/kb/128185
            The value in the dialog items are returned in the 7th column
        */
        XlfOper ShowDialogBox(const XlfOper& dialogData);
        //! Inserts a new worksheet to left of current selection
        void InsertWorkSheet();
        //! Inserts a XL 2.0 Macro Sheet
        void InsertMacroWorkSheet();
        //! Select Previous Worksheet
        void SelectPreviousSheet();
        //! Select Next Worksheet
        void SelectNextSheet();
        //! Sets screen updates status
        void SetScreenUpdates(bool doesScreenUpdate);

    };

    struct Services_t
    {
        StatusBar_t StatusBar;
        Notes_t Notes;
        Information_t Information;
        Cell_t Cell;
        Commands_t Commands;
    };

    //! Macro functions
    //! These are wrappers for Excel4 macro functions that
    //! are callable from commands or functions defined as 
    //! macros sheet functions
    extern struct Services_t XlfServices;

    //! RAII class to disable screen updates while variable in scope
    class DisableScreenUpdates
    {
    public:
        DisableScreenUpdates()
        {
            XlfServices.Commands.SetScreenUpdates(false);
        }
        ~DisableScreenUpdates()
        {
            XlfServices.Commands.SetScreenUpdates(true);
        }
    };

    //! RAII class to disable calculation while varaible in scope
    class DisableCalculation
    {
    public:
        DisableCalculation();
        ~DisableCalculation();
    private:
        short calulationState_;
    };

}

#endif //  XLFSERVICES_HEADER_GUARD

