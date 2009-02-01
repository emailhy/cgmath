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
#ifndef CGMATH_INCLUDED_VEC2_UTIL_HPP
#define CGMATH_INCLUDED_VEC2_UTIL_HPP

#include <cgmath/vec2.hpp>
#include <cmath>

namespace cgmath {

    /// \related vec2
    template<typename T> std::ostream& operator<<(std::ostream& os, const vec2<T>& v) {
        return (os << v.x << " " << v.y);
    }

    /// \related vec2
    template<typename T> std::istream& operator>>(std::istream& is, vec2<T>& v) {
        return is >> v.x >> v.y;
    }

    /// \related vec2
    template <typename T> T dot(const vec2<T>& v1, const vec2<T>& v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

    /// \related vec2
    template <typename T> T distance(const vec2<T>& a, const vec2<T>& b) {
        return length(a - b);
    }

} 

#endif