
/*
 Copyright (C) 1998, 1999, 2001, 2002 Jérôme Lecomte
 Copyright (C) 2007, 2008 Eric Ehlers
 Copyright (C) 2011 John Adcock
 Copyright (C) 2011 Narinder S Claire

 This file is part of xlw, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 xlw is free software: you can redistribute it and/or modify it under the
 terms of the xlw license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

// $Id$

#include <xlw/xlw.h>
#include <vector>
#include <xlw/XlfServices.h>
using namespace xlw;


extern "C" {

    LPXLFOPER EXCEL_EXPORT xlCirc(LPXLFOPER inDiam) {
        EXCEL_BEGIN;
        XlfOper xlDiam(inDiam);
        // Converts d to a double.
        double ret = xlDiam.AsDouble();
        // Multiplies it.
        ret *= 3.14159;
        // Returns the result as an XlfOper.
        return XlfOper(ret);
        EXCEL_END;
    }

    LPXLFOPER EXCEL_EXPORT xlConcat(LPXLFOPER inStr1, LPXLFOPER inStr2) {
        EXCEL_BEGIN;
        XlfOper xlStr1(inStr1);
        XlfOper xlStr2(inStr2);

        // Converts the 2 strings.
        std::wstring str1 = xlStr1.AsWstring();
        std::wstring str2 = xlStr2.AsWstring();
        // Returns the concatenation of the 2 string as an XlfOper.
        std::wstring ret = str1 + str2;
        return XlfOper(ret);
        EXCEL_END;
    }

    LPXLOPER EXCEL_EXPORT xlConcat4(LPXLOPER inStr1, LPXLOPER inStr2) {
        EXCEL_BEGIN;
        XlfOper4 xlStr1(inStr1);
        XlfOper4 xlStr2(inStr2);

        // Converts the 2 strings.
        std::string str1 = xlStr1.AsString();
        std::string str2 = xlStr2.AsString();
        // Returns the concatenation of the 2 string as an XlfOper.
        std::string ret = str1+str2;
        return XlfOper4(ret);
        EXCEL_END_4;
    }

    LPXLOPER12 EXCEL_EXPORT xlConcat12(LPXLOPER12 inStr1, LPXLOPER12 inStr2) {
        EXCEL_BEGIN;
        XlfOper12 xlStr1(inStr1);
        XlfOper12 xlStr2(inStr2);

        // Converts the 2 strings.
        std::wstring str1 = xlStr1.AsWstring();
        std::wstring str2 = xlStr2.AsWstring();
        // Returns the concatenation of the 2 string as an XlfOper.
        std::wstring ret = str1+str2;
        return XlfOper12(ret);
        EXCEL_END_12;
    }

    LPXLFOPER EXCEL_EXPORT xlStats(LPXLFOPER inTargetRange) {
        EXCEL_BEGIN;
        XlfOper xlTargetRange(inTargetRange);

        // Temporary variables.
        double averageTmp = 0.0;
        double varianceTmp = 0.0;

        // Iterate over the cells in the incoming matrix.
        for (RW i = 0; i < xlTargetRange.rows(); ++i)
        {
            for (RW j = 0; j < xlTargetRange.columns(); ++j)
            {
                // sums the values.
                double value(xlTargetRange(i,j).AsDouble());
                averageTmp += value;
                // sums the squared values.
                varianceTmp += value * value;
            }
        }
        size_t popSize = xlTargetRange.rows() * xlTargetRange.columns();

        // avoid divide by zero
        if(popSize == 0)
        {
            THROW_XLW("Can't calculate stats on empty range");
        }

        // Initialization of the results Array oper.
        XlfOper result(1, 2);
        // compute average.
        double average = averageTmp / popSize;
        result(0, 0) = average;
        // compute variance
        result(0, 1) = varianceTmp / popSize - average * average;
        return result;
        EXCEL_END;
    }

    /*!
     * Demonstrates how to detect that the function is called by
     * the function wizard, and how to retrieve the coordinates
     * of the caller cell
     */
    LPXLFOPER EXCEL_EXPORT xlIsInWiz() {
        EXCEL_BEGIN;

        // Checks if called from the function wizard
        if (XlfExcel::Instance().IsCalledByFuncWiz())
            return XlfOper(true);

        // Gets reference of the called cell
        XlfRef ref = XlfServices.Information.GetCallingCell().AsRef();

        // Returns the reference in A1 format
        // note that we avoid using the functions in XlfServices
        // to do this as most of them require the function to be defined
        // as a macro sheet function
        return XlfOper(ref.GetTextA1());

        EXCEL_END;
    }

    /*!
     * Registered as volatile to demonstrate how functions can be
     * recalculated automatically even if none of the arguments
     * has changed.
     *
     * \return the number of times the function has been called.
     */
    LPXLFOPER EXCEL_EXPORT xlNbCalls() {
        EXCEL_BEGIN;

        static short nbCalls = 0;
        ++nbCalls;
        return XlfOper(nbCalls);

        EXCEL_END;
    }

    LPXLFOPER EXCEL_EXPORT xlManyArguments(LPXLFOPER inVal1,
                                           LPXLFOPER inVal2,
                                           LPXLFOPER inVal3,
                                           LPXLFOPER inVal4,
                                           LPXLFOPER inVal5,
                                           LPXLFOPER inVal6,
                                           LPXLFOPER inVal7,
                                           LPXLFOPER inVal8,
                                           LPXLFOPER inVal9,
                                           LPXLFOPER inVal10,
                                           LPXLFOPER inVal11,
                                           LPXLFOPER inVal12,
                                           LPXLFOPER inVal13,
                                           LPXLFOPER inVal14,
                                           LPXLFOPER inVal15,
                                           LPXLFOPER inVal16,
                                           LPXLFOPER inVal17,
                                           LPXLFOPER inVal18,
                                           LPXLFOPER inVal19,
                                           LPXLFOPER inVal20,
                                           LPXLFOPER inVal21,
                                           LPXLFOPER inVal22,
                                           LPXLFOPER inVal23,
                                           LPXLFOPER inVal24,
                                           LPXLFOPER inVal25,
                                           LPXLFOPER inVal26,
                                           LPXLFOPER inVal27,
                                           LPXLFOPER inVal28,
                                           LPXLFOPER inVal29,
                                           LPXLFOPER inVal30) {
        EXCEL_BEGIN;
        XlfOper xlVal1(inVal1);
        XlfOper xlVal2(inVal2);
        XlfOper xlVal3(inVal3);
        XlfOper xlVal4(inVal4);
        XlfOper xlVal5(inVal5);
        XlfOper xlVal6(inVal6);
        XlfOper xlVal7(inVal7);
        XlfOper xlVal8(inVal8);
        XlfOper xlVal9(inVal9);
        XlfOper xlVal10(inVal10);
        XlfOper xlVal11(inVal11);
        XlfOper xlVal12(inVal12);
        XlfOper xlVal13(inVal13);
        XlfOper xlVal14(inVal14);
        XlfOper xlVal15(inVal15);
        XlfOper xlVal16(inVal16);
        XlfOper xlVal17(inVal17);
        XlfOper xlVal18(inVal18);
        XlfOper xlVal19(inVal19);
        XlfOper xlVal20(inVal20);
        XlfOper xlVal21(inVal21);
        XlfOper xlVal22(inVal22);
        XlfOper xlVal23(inVal23);
        XlfOper xlVal24(inVal24);
        XlfOper xlVal25(inVal25);
        XlfOper xlVal26(inVal26);
        XlfOper xlVal27(inVal27);
        XlfOper xlVal28(inVal28);
        XlfOper xlVal29(inVal29);
        XlfOper xlVal30(inVal30);

        // Add the first and the last.
        double result = xlVal1.AsDouble();
        result += xlVal30.AsDouble();

        return XlfOper(result);
        EXCEL_END;
    }
}

namespace 
{

    // Register the function Circ.

    XLRegistration::Arg CircArgs[] = {
        { "diameter", "Diameter of the circle", "XLF_OPER" }
    };

    XLRegistration::XLFunctionRegistrationHelper registerCirc(
        "xlCirc", "Circ", "Compute the circumference of a circle",
        "xlw Example", CircArgs, 1);

    // Register the function Concat.

    XLRegistration::Arg ConcatArgs[] = {
        { "string1", "First string", "XLF_OPER" },
        { "string2", "Second string", "XLF_OPER" }
    };

    XLRegistration::XLFunctionRegistrationHelper registerConcat(
        "xlConcat", "Concat", "Concatenate two strings",
        "xlw Example", ConcatArgs, 2);

    // Register the function Concat4.

    XLRegistration::Arg Concat4Args[] = {
        { "string1", "First string", "P" },
        { "string2", "Second string", "P" }
    };

    XLRegistration::XLFunctionRegistrationHelper registerConcat4(
        "xlConcat4", "Concat4", "Concatenate two strings",
        "xlw Example", Concat4Args, 2, false, false, "P");

    // Register the function Concat12.

    XLRegistration::Arg Concat12Args[] = {
        { "string1", "First string", "Q" },
        { "string2", "Second string", "Q" }
    };

    XLRegistration::XLFunctionRegistrationHelper registerConcat12(
        "xlConcat12", "Concat12", "Concatenate two strings",
        "xlw Example", Concat12Args, 2, false, false, "Q");

    // Register the function Stats.

    XLRegistration::Arg StatsArgs[] = {
        { "Population", "Target range containing the population", "XLF_OPER" }
    };

    XLRegistration::XLFunctionRegistrationHelper registerStats(
        "xlStats", "Stats", "Return a 1x2 range containing "
        "the average and the variance of a numeric population",
        "xlw Example", StatsArgs, 1);

    // Register the function IsInWiz.

    XLRegistration::XLFunctionRegistrationHelper registerIsInWiz(
        "xlIsInWiz", "IsInWiz", "Return true if the function is called "
        "from the function wizard, and the address of the caller otherwise",
        "xlw Example");

    // Register the function NbCalls as volatile.

    XLRegistration::XLFunctionRegistrationHelper registerNbCalls(
        "xlNbCalls", "NbCalls", "Return the number of times the function "
        "has been calculated since the xll was loaded (volatile)",
        "xlw Example", 0, 0, true);

    // Register the function xlManyArguments.
    // note that the parameter names are deliberately long to
    // trigger the code that truncates the argument list string
    // and prevents the forumla wizard from working properly
    XLRegistration::Arg ManyArgumentsArgs[] = {
        { "numbervalue1", "A parameter", "XLF_OPER" },
        { "numbervalue2", "A parameter", "XLF_OPER" },
        { "numbervalue3", "A parameter", "XLF_OPER" },
        { "numbervalue4", "A parameter", "XLF_OPER" },
        { "numbervalue5", "A parameter", "XLF_OPER" },
        { "numbervalue6", "A parameter", "XLF_OPER" },
        { "numbervalue7", "A parameter", "XLF_OPER" },
        { "numbervalue8", "A parameter", "XLF_OPER" },
        { "numbervalue9", "A parameter", "XLF_OPER" },
        { "numbervalue10", "A parameter", "XLF_OPER" },
        { "numbervalue11", "A parameter", "XLF_OPER" },
        { "numbervalue12", "A parameter", "XLF_OPER" },
        { "numbervalue13", "A parameter", "XLF_OPER" },
        { "numbervalue14", "A parameter", "XLF_OPER" },
        { "numbervalue15", "A parameter", "XLF_OPER" },
        { "numbervalue16", "A parameter", "XLF_OPER" },
        { "numbervalue17", "A parameter", "XLF_OPER" },
        { "numbervalue18", "A parameter", "XLF_OPER" },
        { "numbervalue19", "A parameter", "XLF_OPER" },
        { "numbervalue20", "A parameter", "XLF_OPER" },
        { "numbervalue21", "A parameter", "XLF_OPER" },
        { "numbervalue22", "A parameter", "XLF_OPER" },
        { "numbervalue23", "A parameter", "XLF_OPER" },
        { "numbervalue24", "A parameter", "XLF_OPER" },
        { "numbervalue25", "A parameter", "XLF_OPER" },
        { "numbervalue26", "A parameter", "XLF_OPER" },
        { "numbervalue27", "A parameter", "XLF_OPER" },
        { "numbervalue28", "A parameter", "XLF_OPER" },
        { "numbervalue29", "A parameter", "XLF_OPER" },
        { "numbervalue30", "A parameter", "XLF_OPER" },
    };

    XLRegistration::XLFunctionRegistrationHelper registerManyArguments(
        "xlManyArguments", "ManyArguments", "Uses 30 arguments and breaks function wizard",
        "xlw Example", ManyArgumentsArgs, 30);

}
