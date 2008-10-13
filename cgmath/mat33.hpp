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
#ifndef CGMATH_INCLUDED_mat_HPP
#define CGMATH_INCLUDED_mat_HPP

#include <cgmath/mat_base.hpp>
#include <cgmath/vec3.hpp>
#include <cgmath/quat.hpp>

#if 0

namespace cgmath {

    class mat44;

    /// 3 x 3 matrix class (double precision)
    template <typename T> class mat<3, 3, T> {
    public:
        typedef T value_type;

        mat() {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) m[i][j] = (i == j)? 1 : 0;
        }

        template <typename U>
        mat( U a00, U a01, U a02, 
             U a10, U a11, U a12, 
             U a20, U a21, U a22) {
           m[0][0] = a00; m[0][1] = a01; m[0][2] = a02;
           m[1][0] = a10; m[1][1] = a11; m[1][2] = a12;
           m[2][0] = a20; m[2][1] = a21; m[2][2] = a22;
        }

        template <typename U>
        explicit mat( const U *src, bool column_major = true );
        explicit mat( const vec<3,T>& a, const vec<3,T>& b, const vec<3,T>& c );
        explicit mat( const mat<4,4,T>& M );
        explicit mat( double angle, const vec<3,double>& axis );
        explicit mat( const quat<double>& q );

        mat( const mat& A, const mat& B ) {
            for (int i = 0; i < 3; ++i) {
                m[i][0] =  A.m[i][0] * B.m[0][0] + A.m[i][1] * B.m[1][0] + A.m[i][2] * B.m[2][0];
                m[i][1] =  A.m[i][0] * B.m[0][1] + A.m[i][1] * B.m[1][1] + A.m[i][2] * B.m[2][1];
                m[i][2] =  A.m[i][0] * B.m[0][2] + A.m[i][1] * B.m[1][2] + A.m[i][2] * B.m[2][2];
            }
        }

        bool operator==(const mat& rhs) const {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) if (m[i][j] != rhs.m[i][j]) return false;
            return true;
        }

        bool operator!=(const mat& rhs) const {
            return !this->operator ==(rhs);
        }

        double* operator[]( int row ) {
            return m[row];
        }

        const double* operator[]( int row ) const {
            return m[row];
        }

        template <typename U>
        void set( const U *dst, bool column_major = true );

        template <typename U>
        void get( U *dst, bool column_major = true ) const;
        void get( double *dst, bool column_major = true ) const;
        
        void set_column( int column, const vec<3,T>& v );
        vec<3,T> get_column( int column ) const;
        void set_row( int row, const vec<3,T>& v );
        vec<3,T> get_row( int row ) const;

        mat operator*( const mat& rhs ) const {
            return mat(*this, rhs);
        }

        const mat& operator*=( const mat& rhs ) {
            return (*this = mat(*this, rhs));
        }

        const mat& operator*=( double k ) {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) m[i][j] *= k; 
            return *this;
        }

        const mat& operator+=( const mat& rhs ) {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) m[i][j] += rhs.m[i][j]; 
            return *this;
        }

        mat operator+( const mat& rhs ) const {
            return mat(*this) += rhs;
        }

        const mat& operator-=( const mat& rhs ) {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) m[i][j] -= rhs.m[i][j]; 
            return *this;
        }

        mat operator-( const mat& rhs ) const {
            return mat(*this) -= rhs;
        }

        mat operator-() const {
            return mat(*this) *= -1;
        }

        template <typename T> 
        vec<3,T> transform( const vec<3,T>& v ) {
            return vec<3,T>(
                static_cast<T>(m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z),
                static_cast<T>(m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z),
                static_cast<T>(m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z)
            );
        }

        double m[3][3];
    };

    inline mat operator*( const mat& lhs, double k ) {
        return mat(lhs) *= k;
    }

    inline mat operator*( double k, const mat& rhs ) {
        return mat(rhs) *= k;
    }

    std::ostream& operator<<( std::ostream& os, const mat& m );
    std::istream& operator>>( std::istream& is, mat& m );
} 

#endif 
#endif