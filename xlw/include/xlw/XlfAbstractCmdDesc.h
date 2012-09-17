
/*
 Copyright (C) 1998, 1999, 2001, 2002, 2003, 2004 Jérôme Lecomte

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef INC_XlfAbstractCmdDesc_H
#define INC_XlfAbstractCmdDesc_H

/*!
\file XlfAbstractCmdDesc.h
\brief Class XlfAbstractCmdDesc - Consolidate some properties common to multiple command classes
*/

// $Id$

#include <xlw/EXCEL32_API.h>
#include <string>
#include <ostream>
#include <xlw/XlfArgDescList.h>

#if defined(_MSC_VER)
#pragma once
#endif

namespace xlw {

    //! Consolidate some properties common to multiple command classes.
    class EXCEL32_API XlfAbstractCmdDesc
    {
    public:
        //! \name Structors
        //@{
        //! Ctor.
        XlfAbstractCmdDesc(const std::string& name, const std::string& alias, const std::string& comment);
        //! Dtor.
        virtual ~XlfAbstractCmdDesc();
        //@}

        //! \name Registration
        //@{
        //! Registers the command to Excel.
        void Register(int functionId) const;
        //! Unregister the command from Excel.
        void Unregister() const;
        //@}

        //! \name Get and set class properties
        //@{
        //! Sets the name of the command in the XLL
        void SetName(const std::string& name);
        //! Gets the name of the command in the XLL.
        const std::string& GetName() const;
        //! Sets the alias to be shown in Excel
        void SetAlias(const std::string& alias);
        //! Gets the alias to be shown in Excel.
        const std::string& GetAlias() const;
        //! Sets the comment string to be shown in the function wizard.
        void SetComment(const std::string& comment);
        //! Gets the comment string to be shown in the function wizard.
        const std::string& GetComment() const;
        //! Sets the arguments definition.
        void SetArguments(const XlfArgDescList& arguments);
        //! Gets the arguments definition.
        const XlfArgDescList& GetArguments() const;
        //!Generates the documentation in Sandcastle format
        void GenerateMamlDocs(const std::string outputDir, int itemId) const;
        //@}
    protected:
        //! Actually registers the command (see template method in \ref DP)
        virtual int DoRegister(const std::string& dllName, const std::string& suggestedHelpId) const = 0;
        //! Actually unregisters the command (see template method in \ref DP)
        virtual int DoUnregister(const std::string& dllName) const = 0;
        virtual void DoMamlDocs(std::ostream& ostream) const = 0;
        //! Name of the command in the XLL.
        std::string name_;
        //! Alias for the command in Excel.
        std::string alias_;
        //!used to check if registation has happened
        static const double InvalidFunctionId;
    private:
        //! Comment associated to the command.
        std::string comment_;
        //! List of the argument descriptions of the function.
        XlfArgDescList arguments_;
    };

}

#endif

