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
#include <cgmath/quat.hpp>

namespace cgmath {

    class mat44;

    /// 3 x 3 matrix class (double precision)
    class mat33 {
    public:
        typedef double value_type;

        mat33() {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) m[i][j] = (i == j)? 1 : 0;
        }

        mat33( double a00, double a01, double a02, 
               double a10, double a11, double a12, 
               double a20, double a21, double a22) {
           m[0][0] = a00; m[0][1] = a01; m[0][2] = a02;
           m[1][0] = a10; m[1][1] = a11; m[1][2] = a12;
           m[2][0] = a20; m[2][1] = a21; m[2][2] = a22;
        }

        explicit mat33( const float *src, bool column_major = true );
        explicit mat33( const double *src, bool column_major = true );
        explicit mat33( const vec3<double>& a, const vec3<double>& b, const vec3<double>& c );
        explicit mat33( const mat44& M );
        explicit mat33( double angle, const vec3<double>& axis );
        explicit mat33( const quat<double>& q );

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

        double* operator[]( int row ) {
            return m[row];
        }

        const double* operator[]( int row ) const {
            return m[row];
        }

        void set( const float *dst, bool column_major = true );
        void set( const double *dst, bool column_major = true );
        void get( float *dst, bool column_major = true ) const;
        void get( double *dst, bool column_major = true ) const;

        void set_column( int column, const vec3<double>& v );
        vec3<double> get_column( int column ) const;
        void set_row( int row, const vec3<double>& v );
        vec3<double> get_row( int row ) const;

        mat33 operator*( const mat33& rhs ) const {
            return mat33(*this, rhs);
        }

        const mat33& operator*=( const mat33& rhs ) {
            return (*this = mat33(*this, rhs));
        }

        const mat33& operator*=( double k ) {
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
            return mat33(*this) += rhs;
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
                                
        bool is_valid() const;
        bool is_zero( double epsilon=0 ) const;
        bool is_identity( double epsilon=0 ) const;
        bool equal_to( const mat33& rhs, double epsilon=0 );
        
        double det() const;
        double norm2() const;
        double norm() const;
        quat<double> to_quat() const;

        mat33& zero() {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) m[i][j] = 0;
            return *this;
        }

        mat33& identity() {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) m[i][j] = (i == j)? 1 : 0;
            return *this;
        }
                                            
        mat33& transpose() {
            for (int i = 1; i < 3; ++i)
                for (int j = 0; j < i; ++j) std::swap(m[i][j], m[j][i]);
            return *this;
        }

        mat33& adjoint();
        bool invert();
        //mat33& reorthogonalize();

        mat33& scale( double sx, double sy, double sz );
        
        mat33& scale( const vec3<double>& s ) {
            return this->scale(s.x, s.y, s.z);
        }

        mat33& rotate( double angle, double ax, double ay, double az ) {
            return this->rotate(angle, vec3<double>(ax, ay, az));
        }

        mat33& rotate( double angle, const vec3<double>& axis ) {
            this->operator*=(mat33(angle, axis));
            return *this;
        }

        mat33& rotate( const quat<double>& q ) {
            this->operator*=(mat33(q));
            return *this;
        }

        template <typename T> vec3<T> transform( const vec3<T>& v ) {
            return vec3<T>(
                static_cast<T>(m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z),
                static_cast<T>(m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z),
                static_cast<T>(m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z)
            );
        }

        double m[3][3];
    };

    inline mat33 operator*( const mat33& lhs, double k ) {
        return mat33(lhs) *= k;
    }

    inline mat33 operator*( double k, const mat33& rhs ) {
        return mat33(rhs) *= k;
    }

    template <typename T> mat33 dyadic_prod( const vec3<T>& u, const vec3<T>& v ) {
        mat33 m;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                m[i][j] = u[i] * v[j];
            }
        }
        return m;
    }

    std::ostream& operator<<( std::ostream& os, const mat33& m );
    std::istream& operator>>( std::istream& is, mat33& m );
} 

#endif