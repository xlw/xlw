//          Copyright Narinder S Claire 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)



class Base {
public:
    Base():ch('*'){
        BCount++;
    }
    Base(const Base&):ch('*'){
        BCount++;
    }
    virtual int check_splice(){
        return 0;
    }
    virtual ~Base(){BCount--;}
    virtual void v()const=0;
    static unsigned long BCount;
private:
    char ch;
};
unsigned long Base::BCount(0);

/// this will give us lots of derived classes
template<char ch_>
class Derived :public Base {
public:
    Derived():ch(ch_){
        Count++;
    }
    Derived(const Derived<ch_>&):ch(ch_){
        Count++;
    }
    virtual int  check_splice(){
        return 1;
    }
    virtual ~Derived(){Count--;}
    virtual void v()const{}
    static unsigned long Count;
private:
    char ch;

};
template<char ch_>
unsigned long Derived<ch_>::Count(0);

template<char ch_>
class DerivedSquared :public Derived<ch_>{
public:
    DerivedSquared():ch(std::tolower(ch_)){
        SCount++;
    }
    DerivedSquared(const DerivedSquared<ch_>&):ch(std::tolower(ch_)){
        SCount++;
    }
    virtual int  check_splice(){
        return 2;
    }
    virtual ~DerivedSquared(){SCount--;}
    virtual void v()const{}
    static unsigned long SCount;
private:
    char ch;

};
template<char ch_>
unsigned long DerivedSquared<ch_>::SCount(0);


template<char ch_>
class DerivedCubed:public DerivedSquared<ch_>{
public:
    DerivedCubed():ch(std::tolower(ch_)){
        CCount++;
    }
    DerivedCubed(const DerivedCubed<ch_>&):ch(std::tolower(ch_)){
        CCount++;
    }
    virtual int  check_splice(){
        return 3;
    }
    virtual ~DerivedCubed(){CCount--;}
    virtual void v()const{}
    static unsigned long CCount;
private:
    char ch;

};
template<char ch_>
unsigned long DerivedCubed<ch_>::CCount(0);


void test ( int n1, int n2, const char * str)
{
    if(n1==n2)
    {
        std::cout <<  "Pass : count of " << str << " " << n1<< "\n"; 
    }
    else
    {
        std::cout <<  "Fail : count of " << str << n1 << " expected " << n2 << "\n";
        throw "Count Failed !\n";
    }
}



void test_base(int n)
{
    test(n,Base::BCount,"Base          ");
}

template<char ch>
void test_derived(int n)
{
           test(n,Derived<ch>::Count,"Derived       ");
}

template<char ch>
void test_derivedsquared(int n)
{
    test(n,DerivedSquared<ch>::SCount,"DerivedSquared");
}

template<char ch>
void test_derivedcubed(int n)
{
    test(n,DerivedCubed<ch>::CCount,  "DerivedCubed  ");
}

template<char ch>
void test_all_counts(int base_count,int derived_count, int derived_squared_count,int derived_cubed_count)
{
        std::cout << "  -------- \n\n";
        test_base(base_count);
        test_derived<ch>(derived_count);
        test_derivedsquared<ch>(derived_squared_count);
        test_derivedcubed<ch>(derived_cubed_count);
    
}

const char * names[] = {"base","derived","derived_squared","derived_cubed"};

template<class T>
void check_splice(const T &t,int n)
{
    if(t->check_splice() == n)
    {
        std::cout <<  "Pass : no splicing of " << names[n] << "\n"; 
    }
    else
    {
        std::cout <<  "Fail : " << names[n] << " spliced \n"; 
        throw "Spliced !\n";
    }
}
