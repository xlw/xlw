/*
 Copyright (C) 2011  John Adcock

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

/*!
\file xlcall32.h
\brief creates a stub dll so that we can load up xlls outside Excel
*/

extern "C" 
{
    int __stdcall _DllMainCRTStartup(void* hinstDLL, unsigned int dwReason, void* lpvReserved)
    {
        return 1;
    }

    int _cdecl Excel4(int xlfn, void* operRes, int count, ... )
    {
        return 0;
    }

    int __stdcall Excel4v(int xlfn, void* operRes, int count, void* opers[])
    {
        return 0;
    }

    int __stdcall XLCallVer(void)
    {
        return 0x0C00;
    }

    long __stdcall LPenHelper(int wCode, void* lpv)
    {
        return 0;
    }
}