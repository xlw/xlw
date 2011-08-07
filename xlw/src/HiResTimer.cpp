
/*
Copyright (C) 2011 John Adcock

This file is part of xlw, a free-software/open-source C++ wrapper of the
Excel C API - http://xlw.sourceforge.net/

xlw is free software: you can redistribute it and/or modify it under the
terms of the xlw license.  You should have received a copy of the
license along with this program; if not, please email xlw-users@lists.sf.net

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <xlw/HiResTimer.h>

xlw::HiResTimer::HiResTimer()
{
    QueryPerformanceCounter(&m_start);
}

xlw::HiResTimer::~HiResTimer()
{
}

double xlw::HiResTimer::elapsed() const
{
    LARGE_INTEGER stop;
    QueryPerformanceCounter(&stop);
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    return double(stop.QuadPart - m_start.QuadPart) / double(frequency.QuadPart);
}
