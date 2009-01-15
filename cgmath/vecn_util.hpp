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
#ifndef CGMATH_INCLUDED_VECN_UTIL_HPP
#define CGMATH_INCLUDED_VECN_UTIL_HPP

#include <cgmath/vecn.hpp>

namespace cgmath {

    template <size_t N, typename T> 
    vec<N,T> normalize(const vec<N,T>& v) {
        return v.operator/(v.length());
    }

    template <size_t N, typename T> 
    T distance(const vec<N,T>& a, const vec<N,T>& b) {
        return (a - b).length();
    }

} 

#endif