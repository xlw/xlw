/*
 Copyright (C) 1998, 1999, 2001, 2002, 2003, 2004 Jérôme Lecomte
 Copyright (C) 2007 Eric Ehlers

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
\brief Declares class XlfFuncDesc.
*/

// $Id$

#include <xlw/XlfAbstractCmdDesc.h>

#if defined(_MSC_VER)
#pragma once
#endif

class XlfArgDescList;

//! Encapsulates a function to be registered to Excel.
/*!
By registering your function, you make it available under Excel in
any spreadsheet as well as in the function wizard.
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

  //! Ctor
  XlfFuncDesc(const std::string& name, const std::string& alias,
              const std::string& comment, const std::string& category,
			  RecalcPolicy recalcPolicy = NotVolatile, bool Threadsafe = false);
  //! Dtor.
  ~XlfFuncDesc();

  //! Sets the category where your function will appear in the function wizard.
  void SetCategory(const std::string& category);
  //! Gets the category where your function will appear in the function wizard.
  const std::string& GetCategory() const;
  //! Sets the arguments definition.
  void SetArguments(const XlfArgDescList& arguments);
  //! Gets the index into our list of UDFs
  int GetIndex() const;
  //! Sets in the index into our list of UDFs
  void SetIndex(int i_);

protected:
  //! Registers the function (template method).
  int DoRegister(const std::string& dllName) const;
  //! Unregisters the function (template method).
  int DoUnregister(const std::string& dllName) const;

private:
  //! Copy ctor is declared private but not defined.
  XlfFuncDesc(const XlfFuncDesc&);
  //! Assignment operator is declared private but not defined.
  XlfFuncDesc& operator=(const XlfFuncDesc&);
  //! Pointer to implementation (pimpl idiom, see \ref HS).
  struct XlfFuncDescImpl * impl_;
  //! Shared registration code
  int RegisterAs(const std::string& dllName, double mode_, double* funcId = NULL) const;
  //! Is this function currently live, or has it been faux-unregistered?
  //bool live_;
  //! Index into our list of UDFs
  int index_;
};

#endif

