/*
    Copyright (C) 2007-2011 by Jan Eric Kyprianidis <www.kyprianidis.com>
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
    static LONGLONG s_freq = 0;

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
        m_current = (1000.0 * li.QuadPart) / s_freq;
    }

    double timer::get_elapsed_time( bool reset ) {
        LARGE_INTEGER li;
        QueryPerformanceCounter(&li);
        double x = (1000.0 * li.QuadPart) / s_freq;
        double dt = x - m_current;
        if (reset) {
            m_current = x;
        }
        return dt;
    }
}

#else

#include <sys/time.h>

namespace cgmath {

    timer::timer() {
        reset();
    }

    void timer::reset() {
        timeval x;
        gettimeofday(&x, NULL);
        m_current = 1000.0 * x.tv_sec + x.tv_usec / 1000.0;
    }

    double timer::get_elapsed_time( bool reset ) {
        timeval tv;
        gettimeofday(&tv, NULL);
        double x = 1000.0 * tv.tv_sec + tv.tv_usec / 1000.0;
        double dt = x - m_current;
        if (reset) {
            m_current = x;
        }
        return dt;
    }
}

#endif
