/* Copyright (C) 2011 Narinder S Claire

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef DEEP_COPY_PTR
#define DEEP_COPY_PTR

// STD INCLUDES
#include <ostream>

// LOCAL INCLUDES
#include"eshared_ptr_details.h"

namespace xlw
{

    // This smart pointer has it's roots in the snipplets of code that were posted here:
    // http://groups.google.com/group/comp.lang.c++/browse_thread/thread/bc2e72a1b909af25/89e5c18bc6bb5c7e?hl=en&pli=1#89e5c18bc6bb5c7e
    // http://groups.google.com/group/comp.lang.c++/browse_thread/thread/ddb72a3bf2033362/bc21e5b7a3f355b9?hl=en&q=#bc21e5b7a3f355b9




    template<class T>
    class eshared_ptr {


        template<class U>
        friend bool operator==(xlw::eshared_ptr<T> const & a, xlw_tr1::shared_ptr<U> const & b);

        template<class U>
        friend bool operator<(xlw::eshared_ptr<T> const & a, xlw_tr1::shared_ptr<U> const & b);

        template<class E, class Y>
            friend std::basic_ostream<E, Y> & operator<< (std::basic_ostream<E, Y> & os, xlw::eshared_ptr<T> const & p);


    public:
        template<class Y>
        friend class eshared_ptr;

        typedef T element_type;

        //////////////            The Constructors                               /////

        // The Default constructor has a cloner that does nothing
        eshared_ptr()
            :ptr_imp(),the_cloner(new impl::details::null_new()){}

        // This is the copy constructor BUT does not do a deep copy
        // This is a shared pointer that is capable of deep copying
        // rather than a deep copy pointer
        eshared_ptr( const eshared_ptr & r)
            :ptr_imp(r.ptr_imp),the_cloner(r.the_cloner){}


        // The standard Constructor that takes ownership of p
        // The p MUST have resulted from a new. eshared_ptr
        // is now responsible for deallocation
        template<class Y> explicit eshared_ptr(Y * p)
            :ptr_imp(p),the_cloner(new impl::details::vanilla_new<Y>()){}

        // The following constructors all use set the given allocator
        // for allocating new objects for deep copying and de-allocating
        // those objects.
        // Since ehared_ptr will be using the specified allocator for destroying the
        // pointee, the pointee MUST have been allocated using the same allocator.
        // The original constructor here was :
        //    template<class A, class T> eshared_ptr(T *p, A a )
        // which would take ownership of p whilst 'assuming' memory at p was
        // allocated by a. However, that was deemed a bit risky, what if p was not
        // given my the allocator ? The destruction would still be attempted by the allocator !
        // So now the constructor takes care of allocating & constructing the object
        // for you ! Just pass it your parameters and it will forward them to the constructor
        // of the object.

        template<class A> eshared_ptr( A a )
            :ptr_imp(impl::details::constructors<T>::construct(a)),the_cloner(new impl::details::allocator_new<A>(a)){}

        template<class A,class T1> eshared_ptr( A a, const T1 & p1)
            :ptr_imp(impl::details::constructors<T>::construct(a,p1)),the_cloner(new impl::details::allocator_new<A>(a)){}

        template<class A,class T1,class T2> eshared_ptr( A a, const T1 &p1, const T2 & p2)
            :ptr_imp(impl::details::constructors<T>::construct(a,p1,p2)),the_cloner(new impl::details::allocator_new<A>(a)){}


        // Y* must be (statically) convertable to T* ( Y is derived from T )
        template<class Y> eshared_ptr(eshared_ptr<Y> const & r)
            :ptr_imp(r.ptr_imp),the_cloner(r.the_cloner){}


        //////////////     Assignment Operators            /////////////

        eshared_ptr & operator=(eshared_ptr const & r)
        {
            eshared_ptr(r).swap(*this);
            return *this;
        }

        // Y* must be (statically) convertable to T* ( Y is derived from T )
        template<class Y> eshared_ptr & operator=(eshared_ptr<Y> const & r)
        {
            eshared_ptr(r).swap(*this);
            return *this;
        }

        //////////////     reset modifiers            /////////////

        void reset()
        {
            eshared_ptr().swap(*this);
        }

        // The standard reset that takes ownership of p
        // The p MUST have resulted from a new. eshared_ptr
        // is now responsible for deallocation
        template<class A> void reset(A a)
        {
            eshared_ptr(a).swap(*this);
        }

        // See corresponding constructor above
        template<class A,class T1> void reset( A a, const T1 & p1)
        {
            eshared_ptr(a,p1).swap(*this);
        }


        // See corresponding constructor above
        template<class A,class T1,class T2> void reset( A a, const T1 & p1, const T2 &p2)
        {
            eshared_ptr(a,p1,p2).swap(*this);
        }


        /////////            Observing services      /////////////////////////

        // The deep copier. This service was originally ( in the deep copy pointer)
        // embedded in the copy cnstructor and copy assigment. But now the are given
        // shared semantics and the deep copy has been seperated out into a seperate
        // service of it's own. I think it's better this way, it's more explicit.
        // The service is still part of the smart pointer but now has to be explicity
        // requested by the use
        eshared_ptr copy()const
        {
            // Instantiate the copy
            eshared_ptr<T> the_copy;

            // Call the cloner ( which has knowledge about the type of the derived class)
            // to make a copy by calling the copy constructor
            xlw_tr1::shared_ptr<void> the_inner_void_ptr( xlw_tr1::static_pointer_cast<void,T>( ptr_imp ) );

            // Statically cast it to the Base pointer (T*)
            the_copy.ptr_imp = xlw_tr1::static_pointer_cast<T,void>( the_cloner->operator()( the_inner_void_ptr ));

            // remember to set the cloner in the copy
            the_copy.the_cloner = the_cloner;

            return the_copy;

        }

        //// casting operators
        // We want to be able to behave like a standard shared pointer
        operator xlw_tr1::shared_ptr<T>()const
        {
            return ptr_imp;
        }

        // T* must be convertable to Y*
        template<class Y>
        operator xlw_tr1::shared_ptr<Y>()const
        {
            return xlw_tr1::shared_ptr<Y>(ptr_imp);
        }


        //////////////////// Usual smart pointer services

        T & operator*() const
        {
            return ptr_imp.operator*();
        }

        T * operator->() const
        {
            return ptr_imp.get();
        }

        T * get() const
        {
            return ptr_imp.get();
        }

        bool unique() const
        {
            return ptr_imp.unique();
        }

        long use_count()  const
        {
            return ptr_imp.use_count();
        }

        operator bool() const
        {
            return ptr_imp;
        }



        /////////////////     SWAP that doesn't throw           //////
        void swap(eshared_ptr & b)
        {
            ptr_imp.swap(b.ptr_imp);
            the_cloner.swap(b.the_cloner);
        }



    private:
        xlw_tr1::shared_ptr<T> ptr_imp;
        xlw_tr1::shared_ptr<impl::details::eshared_ptr_new> the_cloner;


    };

    template<class T, class U>
    bool operator==(eshared_ptr<T> const & a, xlw_tr1::shared_ptr<U> const & b)
    {
        return a.ptr_imp == b ;
    }

    template<class T, class U>
    bool operator!=(eshared_ptr<T> const & a, xlw_tr1::shared_ptr<U> const & b)
    {
        return !(a == b) ;
    }

    template<class T, class U>
    bool operator<(eshared_ptr<T> const & a, xlw_tr1::shared_ptr<U> const & b)
    {
        return a.ptr_imp < b ;
    }
    template<class T> void swap(eshared_ptr<T> & a, eshared_ptr<T> & b)
    {
        return a.swap(b);
    }

    template<class T> T * get_pointer(eshared_ptr<T> const & p)
    {
        return p.get();
    }


    template<class T, class U>
    eshared_ptr<T> static_pointer_cast(eshared_ptr<U> const & r)
    {
        return eshared_ptr<T>(r);
    }




} // namespace xlw


namespace std
{
    template<class E, class T, class Y>
    std::basic_ostream<E, T> & operator<< (std::basic_ostream<E, T> & os, xlw::eshared_ptr<Y> const & p)
    {
        return os << p.ptr_imp;
    }

    namespace tr1
    {

        template<class T, class U>
        bool operator==(xlw_tr1::shared_ptr<U> const & b,xlw::eshared_ptr<T> const & a )
        {
            return a == b ;
        }

        template<class T, class U>
        bool operator!=(xlw_tr1::shared_ptr<U> const & b,xlw::eshared_ptr<T> const & a )
        {
            return !(b==a) ;
        }

        template<class T, class U>
        bool operator<(xlw_tr1::shared_ptr<U> const & b, xlw::eshared_ptr<T> const & a)
        {
            return ! ( (a < b) || (b==a) ) ;
        }
    }
}

#endif // DEEP_COPY_PTR

