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
#ifndef CGMATH_INCLUDED_MAT44_HPP
#define CGMATH_INCLUDED_MAT44_HPP

namespace cgmath {

    /// 4 x 4 matrix class (T=float|double)
    template <typename T> class mat44 {
    public:
        typedef double value_type;

        mat44() {
            for (int i = 0; i < 4; ++i) 
                for (int j = 0; j < 4; ++j) m[i][j] = (i == j)? 1 : 0;
        }

        mat44( T a00, T a01, T a02, T a03, 
               T a10, T a11, T a12, T a13,
               T a20, T a21, T a22, T a23,
               T a30, T a31, T a32, T a33) {
               m[0][0] = a00; m[0][1] = a01; m[0][2] = a02; m[0][3] = a03;
               m[1][0] = a10; m[1][1] = a11; m[1][2] = a12; m[1][3] = a13;
               m[2][0] = a20; m[2][1] = a21; m[2][2] = a22; m[2][3] = a23;
               m[3][0] = a30; m[3][1] = a31; m[3][2] = a32; m[3][3] = a33;
        }

        template<typename U> mat44( const mat44<U>& src ) {
            for (int i = 0; i < 4; ++i) 
                for (int j = 0; j < 4; ++j) m[i][j] = static_cast<T>(src.m[i*4+j]);
        }

        template<typename U> mat44( const U *src, bool row_major=true ) {
            if (row_major) {
                for (int i = 0; i < 4; ++i) 
                    for (int j = 0; j < 4; ++j) m[i][j] = static_cast<T>(src[i*4+j]);
            } else {
                for (int i = 0; i < 4; ++i) 
                    for (int j = 0; j < 4; ++j) m[i][j] = static_cast<T>(src[i+j*4]);
            }
        }

        mat44( const mat44& A, const mat44& B ) {
            for (int i = 0; i < 4; ++i) {
                m[i][0] =  A.m[i][0] * B.m[0][0] + A.m[i][1] * B.m[1][0] + A.m[i][2] * B.m[2][0] + A.m[i][3] * B.m[3][0];
                m[i][1] =  A.m[i][0] * B.m[0][1] + A.m[i][1] * B.m[1][1] + A.m[i][2] * B.m[2][1] + A.m[i][3] * B.m[3][1];
                m[i][2] =  A.m[i][0] * B.m[0][2] + A.m[i][1] * B.m[1][2] + A.m[i][2] * B.m[2][2] + A.m[i][3] * B.m[3][2];
                m[i][3] =  A.m[i][0] * B.m[0][3] + A.m[i][1] * B.m[1][3] + A.m[i][2] * B.m[2][3] + A.m[i][3] * B.m[3][3];
            }
        }

        bool operator==( const mat44& rhs ) const {
            for (int i = 0; i < 4; ++i) 
                for (int j = 0; j < 4; ++j) if (m[i][j] != rhs.m[i][j]) return false;
            return true;
        }

        bool operator!=( const mat44& rhs ) const {
            return !this->operator==(rhs);
        }

        T* operator[]( int row ) {
            return m[row];
        }

        const T* operator[](int row) const {
            return m[row];
        }

        template <typename U> void set(const U *src, bool row_major= true) {
            if (row_major) {
                for (int i = 0; i < 4; ++i) 
                    for (int j = 0; j < 4; ++j) m[i][j] = static_cast<float>(src[i*4+j]);
            } else {
                for (int i = 0; i < 4; ++i) 
                    for (int j = 0; j < 4; ++j) m[i][j] = static_cast<float>(src[i+j*4]);
            }
        }

        template <typename U>  void get(U *dst, bool row_major=true) const {
            if (row_major) {
                for (int i = 0; i < 4; ++i) 
                    for (int j = 0; j < 4; ++j) dst[i*4+j] = static_cast<float>(m[i][j]);
            } else {
                for (int i = 0; i < 4; ++i) 
                    for (int j = 0; j < 4; ++j) dst[i+j*4] = static_cast<float>(m[i][j]);
            }
        }

        mat44 operator*( const mat44& rhs ) const {
            return mat44(*this, rhs);
        }

        const mat44& operator*=(const mat44& rhs) {
            return (*this = mat44(*this, rhs));
        }

    private:
        T m[4][4];
    };
} 

#endif