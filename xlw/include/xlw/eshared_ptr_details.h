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

#ifndef DEEP_COPY_PTR_DETAILS
#define DEEP_COPY_PTR_DETAILS


#include<memory>
#include<xlw/xlwshared_ptr.h>



namespace xlw
{
    namespace impl
    {
        namespace details
        {
    ///////////////// These Cloners

    // These are the cloners. The are wrappeed in std::tr1::functions
    // and live inside eshared_ptr. The eshared_ptr is templated of the Base Class
    // so has no knowledge of the derived class it may ACTUALY be pointing to, explicitly
    // This is where the cloners come in. They have that information. The are able to
    // able to construct the deribed class by calling the copy constructor.

    // Assuming we want a new derived class allocated by the standard new operator


    struct eshared_ptr_new
    {
        virtual xlw_tr1::shared_ptr<void> operator()( const xlw_tr1::shared_ptr<void> &p)=0;
        virtual ~eshared_ptr_new(){}
    };

    template<class Y>
    struct vanilla_new:public eshared_ptr_new
    {
        xlw_tr1::shared_ptr<void> operator()( const xlw_tr1::shared_ptr<void> &p)
        {
            if(!p) return xlw_tr1::shared_ptr<void>();

            const Y * ptr  = static_cast<const Y *>(p.get());

            // use the standard, global new operator to allocate and construct the
            // object
            return  xlw_tr1::shared_ptr<void>(new Y(*ptr));
        }
    };


    // forward declaration needed as allocator_new will
    // MAY need to invoke it
    template<class A>
    struct allocator_delete;

    // Assuming there is a dedicated allocator for allocation for new
    // derived classes.
    template<class A>
    struct allocator_new:public eshared_ptr_new
    {
        typedef typename A::value_type Y;
        allocator_new(A a_):a(a_){}

        xlw_tr1::shared_ptr<void> operator()( const xlw_tr1::shared_ptr<void> &p)
        {
            if(!p) return xlw_tr1::shared_ptr<void>();

            const Y * ptr  = static_cast<const Y *>(p.get());

            // Going to request the memory from the allocator for the new object
            // but give ownership to a shared_ptr IMMEDITIALEY. Also need to tell
            // the shared_ptr about our designated destroyer
            xlw_tr1::shared_ptr<Y>  clone_ptr(a.allocate(1),allocator_delete<A>(a));

            // If we had left the pointer received from the allocator above, naked, then
            // if the following threw we would have a leak.
            a.construct(clone_ptr.get(),*ptr);

            return xlw_tr1::static_pointer_cast<void,Y>(clone_ptr);
        }
    private:
        A a;
    };


    // A no-op ... when eshared_ptr has no pointee such as when the default constructor
    // is called to construct the eshared_ptr
    struct null_new:public eshared_ptr_new
    {
        xlw_tr1::shared_ptr<void> operator()( const xlw_tr1::shared_ptr<void> &p)
        {
            return xlw_tr1::shared_ptr<void>();
        }
    };


    /////////////// Constructors when given an allocator

    // eshared_ptr is able to ( and wants to ) construct the pointee itself in the presence
    // of a dedciated allocator. The following are the middle men.
    template<class U>
    struct constructors {

        template<class A>
        static xlw_tr1::shared_ptr<U> construct(A a)
        {
            typedef typename A::value_type T;
            xlw_tr1::shared_ptr<T>  clone_ptr(a.allocate(1),allocator_delete<A>(a));
            new ((void*)clone_ptr.get()) T ();
            return xlw_tr1::static_pointer_cast<U,T>(clone_ptr);
        }

        template<class A,class T1>
        static xlw_tr1::shared_ptr<U> construct(A a,const T1 &p1)
        {
            typedef typename A::value_type T;
            xlw_tr1::shared_ptr<T>  clone_ptr(a.allocate(1),allocator_delete<A>(a));
            new ((void*)clone_ptr.get()) T (p1);
            return xlw_tr1::static_pointer_cast<U,T>(clone_ptr);
        }

        template<class A,class T1,class T2>
        static xlw_tr1::shared_ptr<U> construct(A a,const T1 &p1,const T2 &p2)
        {
            typedef typename A::value_type T;
            xlw_tr1::shared_ptr<T>  clone_ptr(a.allocate(1),allocator_delete<A>(a));
            new ((void*)clone_ptr.get()) T (p1,p2);
            return xlw_tr1::static_pointer_cast<U,T>(clone_ptr);
        }
    };

    //     Dedicated deleter

    // when using a dedicated allocator, a straight forward delete may be insufficient
    // so we need to give the internal shared_ptr a dedicated deleter that is aware
    // of the allocator used for the initial allocation.
    template<class A>
    struct allocator_delete
    {
        typedef typename A::value_type Y;
        allocator_delete (A a_):a(a_){}

        void operator()(Y *p)
        {
            if(!p) return;

            // I wonder of the following 2 calls are the right way round ?
            // Maybe I want the de-allocation done first, since if the destructor throws
            // .. IT SHOULDN'T .. then at least the de-allocation has already happened
            a.destroy(p);
            a.deallocate(p,1);

        }
    private:
        A a;
    };

    } // namespace details

    }//    namespace impl


}//    namespace xlw

#endif
