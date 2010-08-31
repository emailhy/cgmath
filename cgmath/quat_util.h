/*
    Copyright (C) 2007-2009 by Jan Eric Kyprianidis <www.kyprianidis.com>
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
#ifndef CGMATH_INCLUDED_QUAT_UTIL_HPP
#define CGMATH_INCLUDED_QUAT_UTIL_HPP

#include <cgmath/quat.hpp>

namespace cgmath {

    /// \related quat
    template <typename T> 
    std::ostream& operator<<(std::ostream& os, const quat<T>& q) {
        return (os << q.x << " " << q.y << " " << q.z << " " << q.w);
    }

    /// \related quat
    template <typename T> 
    std::istream& operator>>(std::istream& is, quat<T>& q) {
        return is >> q.x >> q.y >> q.z >> q.w;
    }

    /// \related quat
    template <typename T> 
    T dot(const quat<T>& p, const quat<T>& q) {
        return (p.x * q.x + p.y * q.y + p.z * q.z + p.w * q.w);
    }

    /// \related quat
    template <typename T> 
    quat<T> normalize(const quat<T>& q) {
        return q.operator/(q.length());
    }

    /// \related quat
    template <typename T> 
    quat<T> conjugate(const quat<T>& q) {
        return quat<T>(-q.x, -q.y, -q.z, q.w);
    }

    /// \related quat
    template <typename T> 
    quat<T> inverse(const quat<T>& q) {
        double l2 = q.length2();
        if (l2 > 0) {
            double s = 1 / l2;
            return quat<T>(-q.x * s, -q.y * s, -q.z * s, q.w * s);
        }
        return quat<T>();
    }

    /// \related quat
    template <typename T> 
    quat<T> log(const quat<T>& q) {
        double lv = sqrt(q.x * q.x + q.y * q.y + q.z * q.z);
        if (lv > 0) {
            double s = atan2(lv, q.w) / lv;
            return quat<T>(0, q.x * s, q.y * s, q.z * s);
        }
        return quat<T>(0, 0, 0, 0);
    }

    /// \related quat
    template <typename T> 
    quat<T> exp(const quat<T>& q) {
        double omega = sqrt(q.x * q.x + q.y * q.y + q.z * q.z);
        if (omega > 0) {
            double s = sin(omega) / omega;
            return quat<T>(q.x * s, q.y * s, q.z * s, cos(omega));
        }
        return quat<T>(0, 0, 0, 1);
    }

} 

#endif
