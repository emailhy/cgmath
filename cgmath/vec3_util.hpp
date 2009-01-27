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
#ifndef CGMATH_INCLUDED_VEC3_UTIL_HPP
#define CGMATH_INCLUDED_VEC3_UTIL_HPP

#include <cgmath/vec3.hpp>
#include <cmath>

namespace cgmath {

    /// \related vec3
    template<typename T> std::ostream& operator<<(std::ostream& os, const vec3<T>& v) {
        return (os << v.x << " " << v.y << " " << v.z);
    }

    /// \related vec3
    template<typename T> std::istream& operator>>(std::istream& is, vec3<T>& v) {
        return is >> v.x >> v.y >> v.z;
    }

    /// \related vec3
    template <typename T> T length2(const vec3<T>& v) {
        return v.x * v.x + v.y * v.y + v.z * v.z;
    }

    /// \related vec3
    template <typename T> T length(const vec3<T>& v) {
        return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    /// \related vec3
    template <typename T> vec3<T> normalize(const vec3<T>& v) {
        return v / length(v);
    }

    /// \related vec3
    template <typename T> T dot(const vec3<T>& v1, const vec3<T>& v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

} 

#endif