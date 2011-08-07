
/*
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

#ifndef SINGLETON_HEADER_GUARD
#define SINGLETON_HEADER_GUARD


namespace xlw {
template<class Object>
class singleton 
{
public:

    static Object & Instance()
    {
        static Object theObject;
        return theObject;
    }
    virtual ~singleton() {} 

protected:
    singleton(){}
private:
    singleton(const singleton &);
    singleton & operator=(const singleton &);
} ;
}





#endif //  SINGLETON_HEADER_GUARD
