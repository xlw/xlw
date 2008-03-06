//
//
//                                                                    reftest.h
//

#ifndef REFTEST_H
#define REFTEST_H

// Can't put this in Test.h because InterfaceGenerator doesn't like it
using namespace xlw;

#include <xlw/XlfOper.h>

// Experimental feature to distinguish OPER from XLOPER
typedef xlw::XlfOper reftest;

#endif
