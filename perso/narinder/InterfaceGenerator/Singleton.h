//
//
//                                                Singleton.h
//
//
/*
 Copyright (C) 2006 Mark Joshi

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/
#ifndef SINGLETON_H
#define SINGLETON_H
/*
Curiously recurring template pattern.
*/

template<class T>
class Singleton
{
public:
    static T& Instance()
    {
        static T one;
        return one;
    }
protected:
        Singleton() {}
        Singleton(const Singleton&){}

};

#endif

