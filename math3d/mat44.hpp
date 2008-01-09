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
#ifndef MATH3D_INCLUDED_MAT44_HPP
#define MATH3D_INCLUDED_MAT44_HPP

#include <math3d/vec3.hpp>
#include <math3d/quat.hpp>

namespace math3d {

    class mat33;

    class mat44 {
    public:
        typedef double value_type;

        mat44() {
            for (int i = 0; i < 4; ++i) 
                for (int j = 0; j < 4; ++j) m[i][j] = (i == j)? 1 : 0;
        }

        mat44( double a00, double a01, double a02, double a03, 
               double a10, double a11, double a12, double a13,
               double a20, double a21, double a22, double a23,
               double a30, double a31, double a32, double a33) {
               m[0][0] = a00; m[0][1] = a01; m[0][2] = a02; m[0][3] = a03;
               m[1][0] = a10; m[1][1] = a11; m[1][2] = a12; m[1][3] = a13;
               m[2][0] = a20; m[2][1] = a21; m[2][2] = a22; m[2][3] = a23;
               m[3][0] = a30; m[3][1] = a31; m[3][2] = a32; m[3][3] = a33;
        }

        explicit mat44( const float *src, bool column_major = true );
        explicit mat44( const double *src, bool column_major = true );
        explicit mat44( const mat33& M );
        explicit mat44( double angle, const vec3<double>& axis );
        explicit mat44( const quat<double>& q );

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

        double* operator[]( int row ) {
            return m[row];
        }

        const double* operator[](int row) const {
            return m[row];
        }

        void set( const float *src, bool column_major = true );
        void set( const double *src, bool column_major = true );
        void get( float *dst, bool column_major = true ) const;
        void get( double *dst, bool column_major = true ) const;

        mat44 operator*( const mat44& rhs ) const {
            return mat44(*this, rhs);
        }

        const mat44& operator*=(const mat44& rhs) {
            return (*this = mat44(*this, rhs));
        }

        bool is_valid() const;
        bool is_affine() const;
        bool is_almost_zero(double epsilon=EPSILON) const;
        bool is_almost_identity(double epsilon=EPSILON) const;
        
        double det() const;
        double norm2() const;
        double norm() const;

        mat44& zero() {
            for (int i = 0; i < 4; ++i) 
                for (int j = 0; j < 4; ++j) m[i][j] = 0;
            return *this;
        }

        mat44& identity() {
            for (int i = 0; i < 4; ++i) 
                for (int j = 0; j < 4; ++j) m[i][j] = (i == j)? 1 : 0;
            return *this;
        }

        mat44& transpose() {
            for (int i = 1; i < 4; ++i)
                for (int j = 0; j < i; ++j) std::swap(m[i][j], m[j][i]);
            return *this;
        }

        mat44& adjoint();

        bool invert_gauss_jordan();
        bool invert_direct();
        bool invert_affine();

        mat44& scale(double sx, double sy, double sz);
        
        mat44& scale(const vec3<double>& s) {
            return this->scale(s.x, s.y, s.z);
        }

        mat44& rotate( double angle, double ax, double ay, double az ) {
            return this->rotate(angle, vec3<double>(ax, ay, az));
        }

        mat44& rotate( double angle, const vec3<double>& axis ) {
            this->operator*=(mat44(angle, axis));
            return *this;
        }

        mat44& rotate( const quat<double>& q ) {
            this->operator*=(mat44(q));
            return *this;
        }

        mat44& translate( double tx, double ty, double tz );

        mat44& translate( const vec3<double>& t ) {
            return this->translate(t.x, t.y, t.z);
        }

        mat44& ortho_project( double left, double right, double bottom, double top, double z_near, double z_far );
        mat44& persp_project( double fov, double aspect_ratio, double z_near, double z_far );
        mat44& frustum( double left, double right, double bottom, double top, double z_near, double z_far );
        mat44& viewport( double x, double y, double width, double height );

        template <typename T> vec3<T> transform( const vec3<T>& v ) {
            T x = static_cast<T>(m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z);
            T y = static_cast<T>(m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z);
            T z = static_cast<T>(m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z);
            T w = static_cast<T>(m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z);
            return vec3<T>(x / w, y / w, z / w);
        }

        static mat44 look_at( const vec3<double>& pos, const vec3<double>& tgt, const vec3<double>& up );

        double m[4][4];
    };

    std::ostream& operator<<(std::ostream& os, const mat44& m);
    std::istream& operator>>(std::istream& is, mat44& m);
} 

#endif