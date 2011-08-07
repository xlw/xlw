
/*
 Copyright (C) 2011 Narunder S Claire


 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/


#ifndef TEST_H
#define TEST_H


#include<xlw/CellMatrix.h>
#include"type_conversions.h"
#include "reftest.h"

using namespace xlw;
using namespace std;


//<xlw:libraryname=TypeRegisterDemo
//<xlw:typeregister(vector<double> MyArray GetSTDVector)
//<xlw:typeregister(student CellMatrix GetStudent)


double  // GAdds all the elements of the vector
AccSTDVector(const vector<double> &v // The vector
       );

double // Gets the students exam result
ExamResult (const student &s // The student
);



#endif
