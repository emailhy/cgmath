/*
    Copyright (C) 2007-2010 by Jan Eric Kyprianidis <www.kyprianidis.com>
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
#ifndef CGMATH_INCLUDED_MAT22_H
#define CGMATH_INCLUDED_MAT22_H

#include <cgmath/vec2.h>

namespace cgmath {

    /// 2 x 2 matrix class (T=float|double)
    template <typename T> class mat22 {
    public:
        typedef T value_type;

        mat22() {}

		mat22(T s) {
			m[0][0] = m[1][1] = s;
			m[0][1] = = m[1][0] = 0;
		}

		mat22(T sx, T sy) {
			m[0][0] = sx;
			m[1][1] = sy;
			m[0][1] = m[1][0] = 0;
		}

        template <typename U> mat22(
            U a00, U a01, 
            U a10, U a11 ) {
            m[0][0] = static_cast<T>(a00); m[0][1] = static_cast<T>(a01); 
            m[1][0] = static_cast<T>(a10); m[1][1] = static_cast<T>(a11); 
        }

        template <typename U> explicit mat22( const U *src, bool row_major=true ) {
            set(src, row_major);
        }

        explicit mat22( const mat22& A, const mat22& B ) {
            for (int i = 0; i < 2; ++i) {
                m[i][0] =  A.m[i][0] * B.m[0][0] + A.m[i][1] * B.m[1][0];
                m[i][1] =  A.m[i][0] * B.m[0][1] + A.m[i][1] * B.m[1][1];
            }
        }

        bool operator==(const mat22& rhs) const {
            for (int i = 0; i < 2; ++i) 
                for (int j = 0; j < 2; ++j) if (m[i][j] != rhs.m[i][j]) return false;
            return true;
        }

        bool operator!=(const mat22& rhs) const {
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
                for (int i = 0; i < 2; ++i) 
                    for (int j = 0; j < 2; ++j) m[i][j] = static_cast<float>(src[i*2+j]);
            } else {
                for (int i = 0; i < 2; ++i) 
                    for (int j = 0; j < 2; ++j) m[i][j] = static_cast<float>(src[i+j*2]);
            }
        }

        template <typename U>  void get(U *dst, bool row_major=true) const {
            if (row_major) {
                for (int i = 0; i < 2; ++i) 
                    for (int j = 0; j < 2; ++j) dst[i*2+j] = static_cast<float>(m[i][j]);
            } else {
                for (int i = 0; i < 2; ++i) 
                    for (int j = 0; j < 2; ++j) dst[i+j*2] = static_cast<float>(m[i][j]);
            }
        }
        
        void set_column( int column, const vec2<T>& v ) {
            m[0][column] = v.x;
            m[1][column] = v.y;
        }

        vec2<T> get_column( int column ) const {
            return vec2<T>(m[0][column], m[1][column]);
        }

        void set_row( int row, const vec2<T>& v ){
            m[row][0] = v.x;
            m[row][1] = v.y;
        }

        vec2<T> get_row( int row ) const {
            return vec2<T>(m[row][0], m[row][1]);
        }

        mat22 operator*( const mat22& rhs ) const {
            return mat22(*this, rhs);
        }

        const mat22& operator*=( const mat22& rhs ) {
            return (*this = mat22(*this, rhs));
        }

        const mat22& operator*=( T k ) {
            for (int i = 0; i < 2; ++i) 
                for (int j = 0; j < 2; ++j) m[i][j] *= k; 
            return *this;
        }

        const mat22& operator+=( const mat22& rhs ) {
            for (int i = 0; i < 2; ++i) 
                for (int j = 0; j < 2; ++j) m[i][j] += rhs.m[i][j]; 
            return *this;
        }

        mat22 operator+( const mat22& rhs ) const {
            return mat22(*this) += rhs;
        }

        const mat22& operator-=( const mat22& rhs ) {
            for (int i = 0; i < 2; ++i) 
                for (int j = 0; j < 2; ++j) m[i][j] -= rhs.m[i][j]; 
            return *this;
        }

        mat22 operator-( const mat22& rhs ) const {
            return mat22(*this) -= rhs;
        }

        mat22 operator-() const {
            return mat22(*this) *= -1;
        }

        mat22& zero() {
            for (int i = 0; i < 2; ++i) 
                for (int j = 0; j < 2; ++j) m[i][j] = 0;
            return *this;
        }

		mat22& identity() {
			m[0][0] = m[1][1] = 1;
			m[0][1] = m[1][0] = 0;
            return *this;
		}

		mat22& scale(T sx, T sy) {
            for (int i = 0; i < 2; ++i) {
                m[i][0] *= sx;
                m[i][1] *= sy;
            }
            return *this;
		}

		//mat22& rotate(T angle) {
        //    return *this;
		//}

        template <typename U> vec2<U> transform( const vec2<U>& v ) const {
            return vec3<U>(
                static_cast<U>(m[0][0] * v.x + m[0][1] * v.y),
                static_cast<U>(m[1][0] * v.x + m[1][1] * v.y)
            );
        }

    private:
        T m[2][2];
    };


    template <typename T> mat22<T> operator*( const mat22<T>& lhs, T k ) {
        return mat33<T>(lhs) *= k;
    }

    template <typename T> mat22<T> operator*( T k, const mat22<T>& rhs ) {
        return mat33<T>(rhs) *= k;
    }

    template <typename T> T det( const mat22<T>& m ) {
        return m[0][0]*m[1][1] - m[0][1]*m[1][0];
    }

    template <typename T> T norm2( const mat22<T>& m ) {
        T n2 = 0;
        for (int i = 0; i < 2; ++i) 
            for (int j = 0; j < 2; ++j) n2 += m[i][j] * m[i][j];
        return n2;
    }

    template <typename T> T norm( const mat22<T>& m ) {
        return sqrt(norm2(m));
    }

    template <typename T> mat22<T> transpose( const mat22<T>& m ) {
        return mat22<T>( m[0][0], m[1][0],
                         m[0][1], m[1][1] );
    }

    //template <typename T> bool invert( mat33<T> *m ) {
    //}

    template <typename T> std::ostream& operator<<( std::ostream& os, const mat22<T>& m ) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                os << m[i][j];
                if ((i != 1) || (j != 1)) os << " ";
            }
        }
        return os;
    }

    template <typename T> std::istream& operator>>( std::istream& is, mat22<T>& m ) {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                is >> m[i][j];
            }
        }
        return is;
    }
} 

#endif
