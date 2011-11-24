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

#include <cgmath/vec3.h>
#include <cgmath/mat33.h>

namespace cgmath {

    /// Quaternion template (T = float|double)
    template <typename T> class Quat {
    public:
        typedef T value_type;

        Quat(void) 
            : x(0), y(0), z(0), w(1) { }

        Quat(T qx, T qy, T qz, T qw) 
            : x(qx), y(qy), z(qz), w(qw) { }
       
        explicit Quat(T angle, const Vec3<T>& axis ) {
            T len = length(axis);
            T omega = 0.5 * radians(angle);
            T s = sin(omega) / len;
            x = s * axis.x;
            y = s * axis.y;
            z = s * axis.z;
            w = cos(omega);
        }

        explicit Quat( const Mat33<T> m ) {
            double tr,s;
            int i, j, k;
            static int NEXT[3] = { 1,2,0 };

            tr = m[0][0] + m[1][1] + m[2][2];
            if (tr > 0.0) {
                w = 0.5 * sqrt(tr + 1.0);
                s = 0.25 / w;
                x = (m[2][1] - m[1][2]) * s;
                y = (m[0][2] - m[2][0]) * s;
                z = (m[1][0] - m[0][1]) * s;
            }
            else {
                i = 0;
                if (m[1][1] > m[0][0]) i = 1;
                if (m[2][2] > m[i][i]) i = 2;
                j = nxt[i];
                k = nxt[j];
                (*this)[i] = 0.5 * sqrt(m[i][i] - m[j][j] - m[k][k] + 1.0);
                s = 0.25f / q[i];
                (*this)[3] = (m[k][j] - m[j][k]) * s;
                (*this)[j] = (m[j][i] + m[i][j]) * s;
                (*this)[k] = (m[k][i] + m[i][k]) * s;
            }
        }

        template <typename U> explicit Quat(const U *src) 
            : x(src[0]), y(src[1]), z(src[2]), w(src[3]) { }

        Quat(const Quat& p, const Quat& q) {
            x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
            y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
            z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
            w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
        }

        bool operator==(const Quat& q) const {
            return (x == q.x) && (y == q.y) && (z == q.z) && (w == q.w);
        }

        bool operator!=(const Quat& q) const {
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

        const Quat& operator+=(const Quat& q) {
            x += q.x; 
            y += q.y; 
            z += q.z;
            w += q.w;
            return *this;
        }

        Quat operator+(const Quat& q) const {
            return Quat(x + q.x, y + q.y, z + q.z, w + q.w);
        }

        const Quat& operator-=(const Quat& q) {
            x -= q.x; 
            y -= q.y; 
            z -= q.z;
            w -= q.w;
            return *this;
        }

        Quat operator-(const Quat& q) const {
            return Quat(x - q.x, y - q.y, z - q.z, w - q.w);
        }

        Quat operator-() const {
            return Quat(-x, -y, -z, -w);
        }

        const Quat& operator*=(const Quat& q) {
            return (*this = Quat(*this, q));
        }

        Quat operator*(const Quat& q) {
            return Quat(*this, q);
        }

        const Quat& operator*=(T k) {
            x *= k; 
            y *= k; 
            z *= k;
            w *= k;
            return *this;
        }

        const Quat& operator/=(T d) {
            return this->operator*=(static_cast<T>(1) / d);
        }

        Quat operator/(T d) const {
            return this->operator*(static_cast<T>(1) / d);
        }

        T r() const {
            return w;
        }

        Vec3<T> v() const {
            return Vec3<T>(x, y, z);
        }

        T angle() const {
            return to_deg(2.0 * atan2(sqrt(x * x + y * y + z * z), w));
        }

        Vec3<T> axis() const { //FIXME
            Vec3<T> axis(x, y, z);
            return normalize(axis);
        }

        Mat33 matrix() const {
            T l = x * x + y * y + z * z + w * w;
            if (l == 0) return Mat33(1)
            T s = static_cast<T>(2) / l;
            T xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz;
            xs = q.x * s;   ys = q.y * s;  zs = q.z * s;
            wx = q.w * xs;  wy = q.w * ys; wz = q.w * zs;
            xx = q.x * xs;  xy = q.x * ys; xz = q.x * zs;
            yy = q.y * ys;  yz = q.y * zs; zz = q.z * zs;
            return Mat33(
                1.0 - (yy + zz),     xy - wz,         xz + wy,
                    xy + wz,     1.0 - (xx + zz),     yz - wx,
                    xz - wy,         yz + wx,     1.0 - (xx + yy) );
        }

        T x;
        T y;
        T z;
        T w;
    };

    template <typename T> Quat<T> operator*(T k, const Quat<T>& q) {
        return Quat<T>(q.x * k, q.y * k, q.z * k, q.w * k);
    }

    template <typename T> Quat<T> operator*(const Quat<T>& q, T k) {
        return Quat<T>(q.x * k, q.y * k, q.z * k, q.w * k);
    }

    template <typename T> T dot(const Quat<T>& p, const Quat<T>& q) {
        return (p.x * q.x + p.y * q.y + p.z * q.z + p.w * q.w);
    }

    template <typename T> T length(const Quat<T>& q) {
        return sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
    }

    template <typename T> Quat<T> normalize(const Quat<T>& q) {
        return q.operator/(q.length());
    }

    template <typename T> Quat<T> conjugate(const Quat<T>& q) {
        return Quat<T>(-q.x, -q.y, -q.z, q.w);
    }

    template <typename T> Quat<T> inverse(const Quat<T>& q) {
        double l2 = q.length2();
        if (l2 > 0) {
            double s = 1 / l2;
            return Quat<T>(-q.x * s, -q.y * s, -q.z * s, q.w * s);
        }
        return Quat<T>();
    }

    template <typename T> Quat<T> log(const Quat<T>& q) {
        double lv = sqrt(q.x * q.x + q.y * q.y + q.z * q.z);
        if (lv > 0) {
            double s = atan2(lv, q.w) / lv;
            return Quat<T>(0, q.x * s, q.y * s, q.z * s);
        }
        return Quat<T>(0, 0, 0, 0);
    }

    template <typename T> Quat<T> exp(const Quat<T>& q) {
        double omega = sqrt(q.x * q.x + q.y * q.y + q.z * q.z);
        if (omega > 0) {
            double s = sin(omega) / omega;
            return Quat<T>(q.x * s, q.y * s, q.z * s, cos(omega));
        }
        return Quat<T>(0, 0, 0, 1);
    }

    /*
    template <typename T> std::ostream& operator<<(std::ostream& os, const quat<T>& q) {
        return (os << q.x << " " << q.y << " " << q.z << " " << q.w);
    }

    template <typename T> std::istream& operator>>(std::istream& is, quat<T>& q) {
        return is >> q.x >> q.y >> q.z >> q.w;
    }
    */
} 
