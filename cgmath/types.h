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
#ifndef CGMATH_INCLUDED_TYPES_H
#define CGMATH_INCLUDED_TYPES_H

#ifndef _MSC_VER
#include <stdint.h>
#endif

#include <limits>

#ifdef M_PI
#undef M_PI
#endif
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

/// Global namespace of cgmath 
namespace cgmath {

	#ifdef _MSC_VER
	typedef unsigned __int8 uint8_t;
	typedef unsigned __int16 uint16_t;
	typedef unsigned __int32 uint32_t;
	typedef unsigned __int64 uint64_t;
	typedef signed __int8 int8_t;
	typedef signed __int16 int16_t;
	typedef signed __int32 int32_t;
	typedef signed __int64 int64_t;
	#endif

    static const double PI = 3.14159265358979323846;
    static const double PI_2 = 1.57079632679489661923;
    static const double PI_4 = 0.785398163397448309616;
    static const float EPSILON  = 1e-5f;

}

#endif
