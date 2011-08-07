/*
 Copyright (C) 2005 Mark Joshi


 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef WRAPPER_H
#define WRAPPER_H


    template< class T>
    class Wrapper
    {
    public:

        Wrapper()
        { DataPtr =0;}

        Wrapper(T* DataPtr_ ) // takes ownership of object pointed to by DataPtr_
        { DataPtr =DataPtr_;}

        Wrapper(const T& inner)
        {
            DataPtr = inner.clone();
        }

        ~Wrapper()
        {
            if (DataPtr !=0)
                delete DataPtr;
        }

        Wrapper(const Wrapper<T>& original)
        {
            if (original.DataPtr !=0)
                DataPtr = original.DataPtr->clone();
            else
                DataPtr=0;
        }

        Wrapper& operator=(const Wrapper<T>& original)
        {
            if (this != &original)
            {
                if (DataPtr!=0)
                    delete DataPtr;

                DataPtr = (original.DataPtr !=0) ? original.DataPtr->clone() : 0;
            }

            return *this;
        }


        T& operator*()
        {
            return *DataPtr;
        }

        const T& operator*() const
        {
            return *DataPtr;
        }

        const T* const operator->() const
        {
            return DataPtr;
        }

        T* operator->()
        {
            return DataPtr;
        }


    private:
        T* DataPtr;


    };

#endif
