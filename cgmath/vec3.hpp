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
#ifndef CGMATH_INCLUDED_VEC3_HPP
#define CGMATH_INCLUDED_VEC3_HPP

#include <cgmath/vecn.hpp>

namespace cgmath {

    /// 3-dimensional vector template (T = float|double)
    template <typename T> class vec<3, T> {
    public:
        enum { dim = 3 };
        typedef T value_type;

        vec() { }

        vec(T vx) 
            : x(vx), y(vx), z(vx) { }

        vec(T vx, T vy, T vz) 
            : x(vx), y(vy), z(vz) { }

        template <typename U> vec(const vec<3,U>& src)
            : x(static_cast<T>(src.x)), y(static_cast<T>(src.y)), z(static_cast<T>(src.z)) { }

        template <typename U> explicit vec(const U *src) 
            : x(static_cast<T>(src[0])), y(static_cast<T>(src[1])), z(static_cast<T>(src[2])) { }

        T& operator[](int index) {
            return (&x)[index];
        }

        const T& operator[](int index) const {
            return (&x)[index];
        }

        template <typename U> void get(U *dst) const {
            dst[0] = static_cast<U>(x);
            dst[1] = static_cast<U>(y);
            dst[2] = static_cast<U>(z);
        }

        bool operator==(const vec& v) const {
            return (x == v.x) && (y == v.y) && (z == v.z);
        }

        bool operator!=(const vec& v) const {
            return !this->operator==(v);
        }

        const vec& operator+=(const vec& v) {
            x += v.x; 
            y += v.y; 
            z += v.z;
            return *this;
        }

        vec operator+(const vec& v) const {
            return vec(x + v.x, y + v.y, z + v.z);
        }

        const vec& operator-=(const vec& v) {
            x -= v.x; 
            y -= v.y; 
            z -= v.z;
            return *this;
        }

        vec operator-(const vec& v) const {
            return vec(x - v.x, y - v.y, z - v.z);
        }

        vec operator-() const {
            return vec(-x, -y, -z);
        }

        const vec operator*=(T k) {
            x *= k; 
            y *= k; 
            z *= k;
            return *this;
        }

        const vec operator/=(T d) {
            return this->operator*=(1 / d);
        }

        vec operator/(T d) const {
            return operator*(*this, 1 / d);
        }

        T length2() const {
            return (x * x + y * y + z * z);
        }

        T length() const {
            return sqrt(length2());
        }

        T normalize() {
            T len = length();
            if (len > 0) this->operator/=(len);
            return len;
        }

        T x;              
        T y;            
        T z;
    };

    template <typename T> vec<3,T> operator*(const vec<3,T> v, T k) {
        return vec<3,T>(v.x * k, v.y * k, v.z * k);
    }

    template <typename T> vec<3,T> operator*(T k, const vec<3,T>& v) {
        return vec<3,T>(v.x * k, v.y * k, v.z * k);
    }

    template<typename T> std::ostream& operator<<(std::ostream& os, const vec<3,T>& v) {
        return (os << v.x << " " << v.y << " " << v.z);
    }

    template<typename T> std::istream& operator>>(std::istream& is, vec<3,T>& v) {
        return is >> v.x >> v.y >> v.z;
    }
} 

#endif