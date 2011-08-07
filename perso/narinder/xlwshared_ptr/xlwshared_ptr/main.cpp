//          Copyright Narinder S Claire 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include<vector>
#include<iostream>
#include<cctype>

#include"xlwshared_ptr.h"


using xlw::impl::shared_ptr;

#include"test_classes.h"

const int B = 0;
const int D = 1;
const int DS = 2;
const int DC = 3;


int main()
{
    // we will count manualy all the instances
    // of the classes we create
    int bc = 0;
    int dc = 0; 
    int dsc = 0; 
    int dcc = 0; 
    try
    {
        //////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////
        ////////// CONSTRUCTORS /////////////////////////////////

        {

            // pointer is templated on Bas but
            // pointee is Derived
            shared_ptr<Base> the_ptr_B(new Derived<'B'>);

            ++bc;
            ++dc;
            test_all_counts<'B'>(bc,dc,dsc,dcc);

            // Check our derived class is not spliced 
            check_splice(the_ptr_B,D);

            //////////////////////////////////////////////////////////////

            // Copy constructor .. should share
            shared_ptr<Base> the_ptr_B2(the_ptr_B);

            // the counts do not change
            test_all_counts<'B'>(bc,dc,dsc,dcc);

            // and should not splice
            check_splice(the_ptr_B2,D);

            ///////////////////////////////////////////////////////////////
            shared_ptr<Derived<'B'> > the_ptr_D1(new Derived<'B'>);

            ++bc;
            ++dc;
            test_all_counts<'B'>(bc,dc,dsc,dcc);
            check_splice(the_ptr_D1,D);

            ///////////////////////////////////////////////////////////////

            // Can we 'upcast' without splicing ? i.e
            // can we get shared_ptr<Base> from shared_ptr<derived> 
            // without splicing ?

            shared_ptr<Base> the_ptr_B3(the_ptr_D1);


            test_all_counts<'B'>(bc,dc,dsc,dcc);
            check_splice(the_ptr_B3,D);

            ///////////////////////////////

            // Get grandchild 
            shared_ptr<DerivedSquared<'B'> > the_ptr_DS1(new DerivedSquared<'B'>);

            ++bc;
            ++dc;
            ++dsc;
            test_all_counts<'B'>(bc,dc,dsc,dcc);
            check_splice(the_ptr_DS1,DS);

            ///////////////////////////////

            // Ok lets upcast one level 
            shared_ptr<Derived<'B'> > the_ptr_D2(the_ptr_DS1);

            test_all_counts<'B'>(bc,dc,dsc,dcc);
            check_splice(the_ptr_D2,DS);

            // is upcasting transistive 
            shared_ptr<Base> the_ptr_B4(the_ptr_DS1);

            test_all_counts<'B'>(bc,dc,dsc,dcc);
            check_splice(the_ptr_B4,DS);


            //////////////////////////////////////////

            // can we take it from the auto_ptr ?
            std::auto_ptr<DerivedSquared<'B'> > the_ap_DS2(new DerivedSquared<'B'>());

            // Ok lets upcast one level 
            shared_ptr<DerivedSquared<'B'> > the_ap_D1(the_ap_DS2);

            ++bc;
            ++dc;
            ++dsc;

            test_all_counts<'B'>(bc,dc,dsc,dcc);
            check_splice(the_ptr_D2,DS);


        }
        // they should all have disappeared
        bc=0;
        dc=0;
        dsc=0;
        test_all_counts<'B'>(bc,dc,dsc,dcc);




        //////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////
        ////////// ASSIGNMENTS AND RESET ////////////////////////

        {

            // pointer is templated on Baes
            shared_ptr<Base> the_ptr_B;
            
            // but pointee is Derived
            the_ptr_B.reset(new Derived<'B'>);

            ++bc;
            ++dc;
            test_all_counts<'B'>(bc,dc,dsc,dcc);

            // Check our derived class is not spliced 
            check_splice(the_ptr_B,D);

            //////////////////////////////////////////////////////////////

            // Copy Asignment .. should share
            shared_ptr<Base> the_ptr_B2;
            
            the_ptr_B2 = the_ptr_B;

            // the counts do not change
            test_all_counts<'B'>(bc,dc,dsc,dcc);

            // and should not splice
            check_splice(the_ptr_B2,D);

            ///////////////////////////////////////////////////////////////

            // the in the followoing 2 lines the count shuld only
            // go up by one
            shared_ptr<Derived<'B'> > the_ptr_D1(new Derived<'B'>());
            the_ptr_D1.reset( new Derived<'B'>());

            ++bc;
            ++dc;
            test_all_counts<'B'>(bc,dc,dsc,dcc);
            check_splice(the_ptr_D1,D);

            ///////////////////////////////////////////////////////////////

            // Can we 'upcast' without splicing ? i.e
            // can we get shared_ptr<Base> from shared_ptr<derived> 
            // without splicing ?

            shared_ptr<Base> the_ptr_B3;
            the_ptr_B3 = the_ptr_D1;


            test_all_counts<'B'>(bc,dc,dsc,dcc);
            check_splice(the_ptr_B3,D);

            ///////////////////////////////

            // Get grandchild 
            shared_ptr<DerivedSquared<'B'> > the_temp_DS1(new DerivedSquared<'B'>);
            shared_ptr<DerivedSquared<'B'> > the_ptr_DS1(new DerivedSquared<'B'>);

            bc+=2;
            dc+=2;
            dsc+=2;
            test_all_counts<'B'>(bc,dc,dsc,dcc);
            check_splice(the_ptr_DS1,DS);


            the_ptr_DS1  =the_temp_DS1 ;
            // count should have gone down by one 
            --bc;
            --dc;
            --dsc;
            test_all_counts<'B'>(bc,dc,dsc,dcc);
            check_splice(the_ptr_DS1,DS);

            ///////////////////////////////

            // Ok lets upcast one level 
            shared_ptr<Derived<'B'> > the_ptr_D2;
            the_ptr_D2 = the_ptr_DS1;

            test_all_counts<'B'>(bc,dc,dsc,dcc);
            check_splice(the_ptr_D2,DS);

            // is upcasting transistive 
            shared_ptr<Base> the_ptr_B4;
            the_ptr_B4 = the_ptr_DS1;

            test_all_counts<'B'>(bc,dc,dsc,dcc);
            check_splice(the_ptr_B4,DS);


            //////////////////////////////////////////

            // can we take it from the auto_ptr ?
            std::auto_ptr<DerivedSquared<'B'> > the_ap(new DerivedSquared<'B'>());

            shared_ptr<DerivedSquared<'B'> > the_ap_DS1;
            the_ap_DS1 = the_ap;

            ++bc;
            ++dc;
            ++dsc;

            test_all_counts<'B'>(bc,dc,dsc,dcc);
            check_splice(the_ptr_D2,DS);


            //////////////////////////////////////////
            // What about self-assignment
            the_ap_DS1 = the_ap_DS1;
            test_all_counts<'B'>(bc,dc,dsc,dcc);
            check_splice(the_ptr_D2,DS);

            the_ap_DS1.reset();
            --bc;
            --dc;
            --dsc;

            test_all_counts<'B'>(bc,dc,dsc,dcc);




            throw(int(0));
        }
        // they should all have disappeared


    }
    catch(const char *str)
    {
        std::cout << str;
    }
    catch(int)
    {}
    catch(...)
    {
        std::cout << "UNKNOWN EXCEPTION !\n";
    }
    bc=0;
    dc=0;
    dsc=0;
    test_all_counts<'B'>(bc,dc,dsc,dcc);



    char ch;
    std::cin >> ch;
    return 0;
}

