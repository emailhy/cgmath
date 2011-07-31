/*
    Copyright (C) 2007-2008 by Jan Eric Kyprianidis <www.kyprianidis.com>
    All rights reserved.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <cgmath/timer.h>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace cgmath {

    static bool s_init = true;
    static uint64_t s_freq = 0;


    timer::timer() {
        if (s_init) {
            s_init = false;
            LARGE_INTEGER li;
            QueryPerformanceFrequency(&li);
            s_freq = li.QuadPart;
        }
        reset();
    }


    void timer::reset() {
        LARGE_INTEGER li;
        QueryPerformanceCounter(&li);
        m_current = li.QuadPart;
    }


    double timer::get_elapsed_time( bool reset ) {
        LARGE_INTEGER li;
        QueryPerformanceCounter(&li);
        double dt = (double)(li.QuadPart - m_current) / s_freq;
        if (reset) {
            m_current = li.QuadPart;
        }
        return dt;
    }
            
}

#endif

