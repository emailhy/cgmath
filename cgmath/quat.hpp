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
#ifndef CGMATH_INCLUDED_QUAT_HPP
#define CGMATH_INCLUDED_QUAT_HPP

#include <cgmath/vec3.hpp>

namespace cgmath {

    /// Quaternion template (T = float|double)
    template <typename T> class quat {
    public:
        typedef T value_type;

        quat(void) 
            : x(0), y(0), z(0), w(1) { }

        quat(T qx, T qy, T qz, T qw) 
            : x(qx), y(qy), z(qz), w(qw) { }
       
        quat(T angle, const vec<3,T>& axis ) {
            double len = axis.length();
            double omega = 0.5 * radians(angle);
            double s = sin(omega) / len;
            x = s * axis.x;
            y = s * axis.y;
            z = s * axis.z;
            w = cos(omega);
        }

        template <typename U> explicit quat(const U *src) 
            : x(src[0]), y(src[1]), z(src[2]), w(src[3]) { }

        quat(const quat& p, const quat& q) {
            x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
            y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
            z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
            w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
        }

        bool operator==(const quat& q) const {
            return (x == q.x) && (y == q.y) && (z == q.z) && (w == q.w);
        }

        bool operator!=(const quat& q) const {
            return !this->operator==(q);
        }

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

        const quat& operator+=(const quat& q) {
            x += q.x; 
            y += q.y; 
            z += q.z;
            w += q.w;
            return *this;
        }

        quat operator+(const quat& q) const {
            return quat(x + q.x, y + q.y, z + q.z, w + q.w);
        }

        const quat& operator-=(const quat& q) {
            x -= q.x; 
            y -= q.y; 
            z -= q.z;
            w -= q.w;
            return *this;
        }

        quat operator-(const quat& q) const {
            return quat(x - q.x, y - q.y, z - q.z, w - q.w);
        }

        quat operator-() const {
            return quat(-x, -y, -z, -w);
        }

        const quat& operator*=(const quat& q) {
            return (*this = quat(*this, q));
        }

        quat operator*(const quat& q) {
            return quat(*this, q);
        }

        const quat& operator*=(T k) {
            x *= k; 
            y *= k; 
            z *= k;
            w *= k;
            return *this;
        }

        const quat& operator/=(T d) {
            return this->operator*=(static_cast<T>(1) / d);
        }

        quat operator/(T d) const {
            return this->operator*(static_cast<T>(1) / d);
        }

        T r() const {
            return w;
        }

        vec<3,T> v() const {
            return vec<3,T>(x, y, z);
        }

        T angle() const {
            return to_deg(2.0 * atan2(sqrt(x * x + y * y + z * z), w));
        }

        vec<3,T> axis() const { //FIXME
            vec<3,T> axis(x, y, z);
            return normalize(axis);
        }

        T length2() const {
            return (x * x + y * y + z * z + w * w);
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
        T w;
    };

    template <typename T> 
    quat<T> operator*(T k, const quat<T>& q) {
        return quat<T>(q.x * k, q.y * k, q.z * k, q.w * k);
    }

    template <typename T> 
    quat<T> operator*(const quat<T>& q, T k) {
        return quat<T>(q.x * k, q.y * k, q.z * k, q.w * k);
    }

    template <typename T> 
    T dot(const quat<T>& p, const quat<T>& q) {
        return (p.x * q.x + p.y * q.y + p.z * q.z + p.w * q.w);
    }

    template <typename T> 
    quat<T> normalize(const quat<T>& q) {
        return q.operator/(q.length());
    }

    template <typename T> 
    quat<T> conjugate(const quat<T>& q) {
        return quat<T>(-q.x, -q.y, -q.z, q.w);
    }

    template <typename T> 
    quat<T> inverse(const quat<T>& q) {
        double l2 = q.length2();
        if (l2 > 0) {
            double s = 1 / l2;
            return quat<T>(-q.x * s, -q.y * s, -q.z * s, q.w * s);
        }
        return quat<T>();
    }

    template <typename T> 
    quat<T> log(const quat<T>& q) {
        double lv = sqrt(q.x * q.x + q.y * q.y + q.z * q.z);
        if (lv > 0) {
            double s = atan2(lv, q.w) / lv;
            return quat<T>(0, q.x * s, q.y * s, q.z * s);
        }
        return quat<T>(0, 0, 0, 0);
    }

    template <typename T> 
    quat<T> exp(const quat<T>& q) {
        double omega = sqrt(q.x * q.x + q.y * q.y + q.z * q.z);
        if (omega > 0) {
            double s = sin(omega) / omega;
            return quat(q.x * s, q.y * s, q.z * s, cos(omega));
        }
        return quat(0, 0, 0, 1);
    }

    template <typename T> 
    std::ostream& operator<<(std::ostream& os, const quat<T>& q) {
        return (os << q.x << " " << q.y << " " << q.z << " " << q.w);
    }

    template <typename T> 
    std::istream& operator>>(std::istream& is, quat<T>& q) {
        return is >> q.x >> q.y >> q.z >> q.w;
    }
} 

#endif
