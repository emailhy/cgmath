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
#ifndef CGMATH_INCLUDED_MAT33_HPP
#define CGMATH_INCLUDED_MAT33_HPP

#include <cgmath/vec3.hpp>

namespace cgmath {

    /// 3 x 3 matrix class (T=float|double)
    template <typename T> class mat33 {
    public:
        typedef T value_type;

        mat33() {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) m[i][j] = (i == j)? 1 : 0;
        }

        template <typename U> mat33(
            U a00, U a01, U a02, 
            U a10, U a11, U a12,
            U a20, U a21, U a22) {
            m[0][0] = static_cast<T>(a00); m[0][1] = static_cast<T>(a01); m[0][2] = static_cast<T>(a02);
            m[1][0] = static_cast<T>(a10); m[1][1] = static_cast<T>(a11); m[1][2] = static_cast<T>(a12);
            m[2][0] = static_cast<T>(a20); m[2][1] = static_cast<T>(a21); m[2][2] = static_cast<T>(a22);
        }

        template <typename U> explicit mat33( const U *src, bool row_major=true ) {
            set(src, row_major);
        }

        explicit mat33( const vec3<T>& a, const vec3<T>& b, const vec3<T>& c ) {
            m[0][0] = a.x; m[0][1] = b.x; m[0][2] = b.x;
            m[1][0] = a.y; m[1][1] = b.y; m[1][2] = b.y;
            m[2][0] = a.z; m[2][1] = b.z; m[2][2] = b.z;
        }

        mat33( const mat33& A, const mat33& B ) {
            for (int i = 0; i < 3; ++i) {
                m[i][0] =  A.m[i][0] * B.m[0][0] + A.m[i][1] * B.m[1][0] + A.m[i][2] * B.m[2][0];
                m[i][1] =  A.m[i][0] * B.m[0][1] + A.m[i][1] * B.m[1][1] + A.m[i][2] * B.m[2][1];
                m[i][2] =  A.m[i][0] * B.m[0][2] + A.m[i][1] * B.m[1][2] + A.m[i][2] * B.m[2][2];
            }
        }

        bool operator==(const mat33& rhs) const {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) if (m[i][j] != rhs.m[i][j]) return false;
            return true;
        }

        bool operator!=(const mat33& rhs) const {
            return !this->operator ==(rhs);
        }

        T* operator[]( int row ) {
            return m[row];
        }

        const T* operator[]( int row ) const {
            return m[row];
        }

        template <typename U> void set(const U *src, bool row_major= true) {
            if (row_major) {
                for (int i = 0; i < 3; ++i) 
                    for (int j = 0; j < 3; ++j) m[i][j] = static_cast<float>(src[i*4+j]);
            } else {
                for (int i = 0; i < 3; ++i) 
                    for (int j = 0; j < 3; ++j) m[i][j] = static_cast<float>(src[i+j*4]);
            }
        }

        template <typename U>  void get(U *dst, bool row_major=true) const {
            if (row_major) {
                for (int i = 0; i < 3; ++i) 
                    for (int j = 0; j < 3; ++j) dst[i*4+j] = static_cast<float>(m[i][j]);
            } else {
                for (int i = 0; i < 3; ++i) 
                    for (int j = 0; j < 3; ++j) dst[i+j*4] = static_cast<float>(m[i][j]);
            }
        }
        
        void set_column( int column, const vec3<T>& v ) {
            m[0][column] = v.x;
            m[1][column] = v.y;
            m[2][column] = v.z;
        }

        vec3<T> get_column( int column ) const {
            return vec3<T>(m[0][column], m[1][column], m[2][column]);
        }

        void set_row( int row, const vec3<T>& v ){
            m[row][0] = v.x;
            m[row][1] = v.y;
            m[row][2] = v.z;
        }

        vec3<T> get_row( int row ) const {
            return vec3<T>(m[row][0], m[row][1], m[row][2]);
        }

        mat33 operator*( const mat33& rhs ) const {
            return mat33(*this, rhs);
        }

        const mat33& operator*=( const mat33& rhs ) {
            return (*this = mat33(*this, rhs));
        }

        const mat33& operator*=( T k ) {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) m[i][j] *= k; 
            return *this;
        }

        const mat33& operator+=( const mat33& rhs ) {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) m[i][j] += rhs.m[i][j]; 
            return *this;
        }

        mat33 operator+( const mat33& rhs ) const {
            return mat(*this) += rhs;
        }

        const mat33& operator-=( const mat33& rhs ) {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) m[i][j] -= rhs.m[i][j]; 
            return *this;
        }

        mat33 operator-( const mat33& rhs ) const {
            return mat33(*this) -= rhs;
        }

        mat33 operator-() const {
            return mat33(*this) *= -1;
        }

        vec3<T> transform( const vec3<T>& v ) {
            return vec3<T>(
                static_cast<T>(m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z),
                static_cast<T>(m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z),
                static_cast<T>(m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z)
            );
        }

    private:
        T m[3][3];
    };

    template <typename T> mat33<T> operator*( const mat33<T>& lhs, T k ) {
        return mat(lhs) *= k;
    }

    template <typename T> mat33<T> operator*( T k, const mat33<T>& rhs ) {
        return mat(rhs) *= k;
    }
} 

#endif
