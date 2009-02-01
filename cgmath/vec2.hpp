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
#ifndef CGMATH_INCLUDED_VEC2_HPP
#define CGMATH_INCLUDED_VEC2_HPP

namespace cgmath {

    /// 2-dimensional vector template (T = int|float|double)
    template <typename T> class vec2 {
    public:
        enum { dim = 2 };
        typedef T value_type;

        vec2() { }

        vec2(T vx) 
            : x(vx), y(vx){ }

        vec2(T vx, T vy) 
            : x(vx), y(vy){ }

        template <typename U> vec2(const vec2<U>& src)
            : x(static_cast<T>(src.x)), y(static_cast<T>(src.y)) { }

        template <typename U> explicit vec2(const U *src) 
            : x(static_cast<T>(src[0])), y(static_cast<T>(src[1])) { }

        T& operator[](int index) {
            return (&x)[index];
        }

        const T& operator[](int index) const {
            return (&x)[index];
        }

        template <typename U> void get(U *dst) const {
            dst[0] = static_cast<U>(x);
            dst[1] = static_cast<U>(y);
        }

        bool operator==(const vec2& v) const {
            return (x == v.x) && (y == v.y);
        }

        bool operator!=(const vec2& v) const {
            return !this->operator==(v);
        }

        const vec2& operator+=(const vec2& v) {
            x += v.x; 
            y += v.y; 
            return *this;
        }

        vec2 operator+(const vec2& v) const {
            return vec2(x + v.x, y + v.y);
        }

        const vec2& operator-=(const vec2& v) {
            x -= v.x; 
            y -= v.y; 
            return *this;
        }

        vec2 operator-(const vec2& v) const {
            return vec2(x - v.x, y - v.y);
        }

        vec2 operator-() const {
            return vec2(-x, -y);
        }

        const vec2& operator*=(T k) {
            x *= k; 
            y *= k; 
            return *this;
        }

        const vec2& operator*=(const vec2& v) {
            x *= v.x; 
            y *= v.y; 
            return *this;
        }

        const vec2& operator/=(T d) {
            return this->operator*=(1 / d);
        }

        vec2 operator/(T d) const {
            return operator*(*this, 1 / d);
        }

        T x;              
        T y;            
    };

    /// \related vec2
    template <typename T> vec2<T> operator*(const vec2<T> v, T k) {
        return vec2<T>(v.x * k, v.y * k);
    }

    /// \related vec2
    template <typename T> vec2<T> operator*(T k, const vec2<T>& v) {
        return vec2<T>(v.x * k, v.y * k);
    }

    /// \related vec2
    template <typename T> T length(const vec2<T>& v) {
        return sqrt(v.x * v.x + v.y * v.y);
    }

    /// \related vec2
    template <typename T> vec2<T> normalize(const vec2<T>& v) {
        return v / length(v);
    }

} 

#endif