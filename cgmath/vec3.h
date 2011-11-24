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
#pragma once

namespace cgmath {

    /// 3-dimensional vector template (T = float|double)
    template <typename T> class Vec3 {
    public:
        enum { dim = 3 };
        typedef T value_type;

        Vec3() { }

        Vec3(T vx) 
            : x(vx), y(vx), z(vx) { }

        Vec3(T vx, T vy, T vz) 
            : x(vx), y(vy), z(vz) { }

        template <typename U> Vec3(const Vec3<U>& src)
            : x(static_cast<T>(src.x)), y(static_cast<T>(src.y)), z(static_cast<T>(src.z)) { }

        template <typename U> explicit Vec3(const U *src) 
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

        bool operator==(const Vec3& v) const {
            return (x == v.x) && (y == v.y) && (z == v.z);
        }

        bool operator!=(const Vec3& v) const {
            return !this->operator==(v);
        }

        const Vec3& operator+=(const Vec3& v) {
            x += v.x; 
            y += v.y; 
            z += v.z;
            return *this;
        }

        Vec3 operator+(const Vec3& v) const {
            return Vec3(x + v.x, y + v.y, z + v.z);
        }

        const Vec3& operator-=(const Vec3& v) {
            x -= v.x; 
            y -= v.y; 
            z -= v.z;
            return *this;
        }

        Vec3 operator-(const Vec3& v) const {
            return Vec3(x - v.x, y - v.y, z - v.z);
        }

        Vec3 operator-() const {
            return Vec3(-x, -y, -z);
        }

        const Vec3 operator*=(T k) {
            x *= k; 
            y *= k; 
            z *= k;
            return *this;
        }

        const Vec3& operator*=(const Vec3& v) {
            x *= v.x; 
            y *= v.y; 
            z *= v.z; 
            return *this;
        }

        const Vec3 operator/=(T d) {
            return this->operator*=(1 / d);
        }

        Vec3 operator/(T d) const {
            return operator*(*this, 1 / d);
        }

        T x;              
        T y;            
        T z;
    };

    template <typename T> Vec3<T> operator*(const Vec3<T> v, T k) {
        return Vec3<T>(v.x * k, v.y * k, v.z * k);
    }

    template <typename T> Vec3<T> operator*(T k, const Vec3<T>& v) {
        return Vec3<T>(v.x * k, v.y * k, v.z * k);
    }

    template <typename T> T dot(const Vec3<T>& v1, const Vec3<T>& v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    template <typename T> T length(const Vec3<T>& v) {
        return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    template <typename T> T distance(const Vec3<T>& a, const Vec3<T>& b) {
        return length(a - b);
    }

    template <typename T> Vec3<T> normalize(const Vec3<T>& v) {
        return v / length(v);
    }

    template <typename T> Vec3<T> cross(const Vec3<T>& v1, const Vec3<T>& v2) {
        return Vec3<T>( 
            v1.y * v2.z - v1.z * v2.y, 
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x
        );
    }

    template <typename T> Vec3<T> clamp(const Vec3<T>& v, T a, T b) {
        return Vec3<T>( clamp(v.x, a, b), clamp(v.y, a, b), clamp(v.z, a, b) );
    }

    /*
    template<typename T> std::ostream& operator<<(std::ostream& os, const vec3<T>& v) {
        return (os << v.x << " " << v.y << " " << v.z);
    }

    template<typename T> std::istream& operator>>(std::istream& is, vec3<T>& v) {
        return is >> v.x >> v.y >> v.z;
    }
    */

    typedef Vec3<float> Vec3f;
    typedef Vec3<float> Point3f;
    typedef Vec3<double> Vec3d;
    typedef Vec3<double> Point3d;
} 
