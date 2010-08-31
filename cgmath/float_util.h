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
#ifndef CGMATH_INCLUDED_UTIL_H
#define CGMATH_INCLUDED_UTIL_H

#include <cgmath/types.h>

namespace cgmath {

    inline double radians(double deg) { 
        return deg * PI / 180.0; 
    }

    inline float radians(float deg) { 
        return static_cast<float>(deg * PI / 180.0 ); 
    }
    
    inline double degrees(double rad) { 
        return rad * 180.0 / PI;    
    }
    
    inline float degrees(float rad) { 
        return static_cast<float>(rad * 180.0 / PI); 
    }

    template <typename T> inline T abs(T v) {
        return (v < 0)? -v : v;
    }

    template<typename T> inline T sign(T v) { 
        return v<0? (T)-1 : (T)1; 
    }

    template <typename T> T min(T a, T b) {
        return (a < b)?  a :  b;
    }

    template <typename T> T max(T a, T b) {
        return (a > b)?  a :  b;
    }

    template <typename T> T clamp(T x, T a, T b) {
        return (x < a)?  a : ((x > b)? b : x);
    }

    inline bool almost_equal(float a, float b, float epsilon=EPSILON) {
        return abs(a - b) <= epsilon;
    }

    inline bool almost_equal(double a, double b, double epsilon=EPSILON) {
        return abs(a - b) <= epsilon;
    }

	template<typename T> inline T smoothstep(T a, T b, T x) {
		T t = (x - a) / (b - a);
		if (t < 0) t = 0;
		if (t > 1) t = 1;
		return t * t * (3 - 2 * t);
	}
}

#endif
