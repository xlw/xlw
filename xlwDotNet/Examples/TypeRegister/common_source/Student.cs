/*
 Copyright (C) 2011 Mark P Owen

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

namespace TypeRegDemo
{
    public class Student
    {
        private readonly string _name;
        private readonly double _age;

        public Student(string Name, double Age)
        {
            _name = Name;
            _age = Age;
        }

        public string Name
        {
            get { return _name; }
        }

        public double Age
        {
            get { return _age; }
        }

        public double ExamResult
        {
            get { return _age * 0.7; }
        }
    }
}
