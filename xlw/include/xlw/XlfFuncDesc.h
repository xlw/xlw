
/*
Copyright (C) 1998, 1999, 2001, 2002, 2003, 2004 Jérôme Lecomte
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

#ifndef INC_XlfFuncDesc_H
#define INC_XlfFuncDesc_H

/*!
\file XlfFuncDesc.h
\brief Class XlfFuncDesc - Encapsulate a function to be registered to Excel
*/

// $Id$

#include <xlw/XlfAbstractCmdDesc.h>
#include <xlw/XlfExcel.h>
#include <xlw/xlwshared_ptr.h>

#if defined(_MSC_VER)
#pragma once
#endif

namespace xlw {

    class XlfArgDescList;

    //! Encapsulate a function to be registered to Excel.
    /*!
    By registering your function, you make it available under Excel in
    any spreadsheet as well as in the function wizard.

    \deprecated Consider using XLRegistration::XLFunctionRegistrationHelper
    instead.
    */
    class EXCEL32_API XlfFuncDesc: public XlfAbstractCmdDesc
    {
    public:
        //! Policy to reclalculate cells.
        enum RecalcPolicy {
            //! Function gets recalculated if one of the argument has changed.
            NotVolatile,
            //! Function gets recalculated unconditionally each time the sheet is calculated.
            Volatile
        } ;

        //! \name Structors
        //@{
        //! Ctor
        XlfFuncDesc(const std::string& name, const std::string& alias,
            const std::string& comment, const std::string& category,
            RecalcPolicy recalcPolicy = NotVolatile, bool Threadsafe = false,
            const std::string &returnTypeCode = XlfExcel::Instance().xlfOperType(),
            const std::string &helpID = "",
            bool Asynchronous = false, bool MacroSheetEquivalent = false,
            bool ClusterSafe = false);
        //! Dtor.
        ~XlfFuncDesc();
        //@}

        //! \name Get and set properties
        //@{
        //! Sets the category where your function will appear in the function wizard.
        void SetCategory(const std::string& category);
        //! Gets the category where your function will appear in the function wizard.
        const std::string& GetCategory() const;
        //! Sets the arguments definition.
        void SetArguments(const XlfArgDescList& arguments);
        // Gets the index into our list of UDFs (not used?).
        //int GetIndex() const;
        // Sets in the index into our list of UDFs (not used?).
        //void SetIndex(int i_);
        //@}
    protected:
        //! \name Concrete implementation of function registration
        //@{
        //! Registers the function.
        int DoRegister(const std::string& dllName, const std::string& suggestedHelpId) const;
        //! Unregisters the function.
        int DoUnregister(const std::string& dllName) const;
        //!Generates the documentation in Sandcastle format
        virtual void DoMamlDocs(std::ostream& ostream) const;
        //@}

    private:
        //! Internal implementation of XlfFuncDesc.
        struct XlfFuncDescImpl
        {
            //! Ctor.
            XlfFuncDescImpl(xlw::XlfFuncDesc::RecalcPolicy recalcPolicy, bool Threadsafe,
                const std::string& category, bool Asynchronous, bool MacroSheetEquivalent,
                bool ClusterSafe) : recalcPolicy_(recalcPolicy), category_(category),
                Threadsafe_(Threadsafe), Asynchronous_(Asynchronous), MacroSheetEquivalent_(MacroSheetEquivalent),
                ClusterSafe_(ClusterSafe)
            {}
            //! Recalculation policy.
            xlw::XlfFuncDesc::RecalcPolicy recalcPolicy_;
            //! Category where the function is displayed in the function wizard.
            std::string category_;
            //! List of the argument descriptions of the function.
            XlfArgDescList arguments_;
            //! Flag indicating whether this function is threadsafe in Excel 2007.
            bool Threadsafe_;
            //! Flag indicating whether this function is can be called Asynchronously in Excel 2010.
            bool Asynchronous_;
            //! Flag indicating whether this function get uncaled cells and can call XLM macro functions.
            bool MacroSheetEquivalent_;
            //! Flag indicating whether this function is can be called over a cluster in Excel 2010.
            bool ClusterSafe_;
        };
        //! Copy ctor is declared private but not defined.
        XlfFuncDesc(const XlfFuncDesc&);
        //! Assignment operator is declared private but not defined.
        XlfFuncDesc& operator=(const XlfFuncDesc&);

        //! Shared registration code
        int RegisterAs(const std::string& dllName, const std::string& suggestedHelpId, double mode_) const;
        std::string helpID_;
        //! Excel code for the datatype of this function's return value.
        // I know it's mutable .. and it's not angelic BUT we may only
        // be able to get the returnType AFTER XlfExcel instance has been initialised
        // so not at the static constructor level.
        mutable std::string returnTypeCode_;
        //! Pointer to implementation (pimpl idiom, see \ref HS).
        xlw_tr1::shared_ptr<XlfFuncDescImpl> impl_;
        //! function ID returned from register
        mutable double funcId_;


    };

}

#endif

