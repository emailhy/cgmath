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
#ifndef CGMATH_INCLUDED_VEC4_HPP
#define CGMATH_INCLUDED_VEC4_HPP

namespace cgmath {

    /// 4-dimensional vector template (T = float|double)
    template <typename T> class vec4 {
    public:
        enum { dim = 4 };
        typedef T value_type;

        vec4() { }

        vec4(T vx) 
            : x(vx), y(vx), z(vx), w(vx) { }

        vec4(T vx, T vy, T vz, T vw) 
            : x(vx), y(vy), z(vz), w(vw) { }

        template <typename U> vec4(const vec4<U>& src)
            : x(static_cast<T>(src.x)), y(static_cast<T>(src.y)), 
			  z(static_cast<T>(src.z)), w(static_cast<T>(src.w)) { }

        template <typename U> explicit vec4(const U *src) 
            : x(static_cast<T>(src[0])), y(static_cast<T>(src[1])), 
			  z(static_cast<T>(src[2])), w(static_cast<T>(src[3])) { }

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
			dst[3] = static_cast<U>(w);
        }

        bool operator==(const vec4& v) const {
            return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
        }

        bool operator!=(const vec4& v) const {
            return !this->operator==(v);
        }

        const vec4& operator+=(const vec4& v) {
            x += v.x; 
            y += v.y; 
            z += v.z;
			w += v.w;
            return *this;
        }

        vec4 operator+(const vec4& v) const {
            return vec4(x + v.x, y + v.y, z + v.z, w + v.w);
        }

        const vec4& operator-=(const vec4& v) {
            x -= v.x; 
            y -= v.y; 
            z -= v.z;
			w -= v.w;
            return *this;
        }

        vec4 operator-(const vec4& v) const {
            return vec4(x - v.x, y - v.y, z - v.z, w - v.w);
        }

        vec4 operator-() const {
            return vec4(-x, -y, -z, -w);
        }

        const vec4 operator*=(T k) {
            x *= k; 
            y *= k; 
            z *= k;
			w *= k;
            return *this;
        }

        const vec4& operator*=(const vec4& v) {
            x *= v.x; 
            y *= v.y; 
            z *= v.z; 
			w *= v.w; 
            return *this;
        }

        const vec4 operator/=(T d) {
            return this->operator*=(1 / d);
        }

        vec4 operator/(T d) const {
            return operator*(*this, 1 / d);
        }

        T x;              
        T y;            
        T z;
		T w;
    };

    /// \related vec4
    template <typename T> vec4<T> operator*(const vec4<T> v, T k) {
        return vec4<T>(v.x * k, v.y * k, v.z * k, v.w * k);
    }

    /// \related vec4
    template <typename T> vec4<T> operator*(T k, const vec4<T>& v) {
        return vec4<T>(v.x * k, v.y * k, v.z * k, v.w * k);
    }

    /// \related vec4
    template <typename T> T length(const vec4<T>& v) {
        return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
    }

    /// \related vec4
    template <typename T> vec4<T> normalize(const vec4<T>& v) {
        return v / length(v);
    }

} 

#endif