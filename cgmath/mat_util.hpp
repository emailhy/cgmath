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
#ifndef CGMATH_INCLUDED_MAT_UTIL_HPP
#define CGMATH_INCLUDED_MAT_UTIL_HPP

#include <cgmath/mat33.hpp>
#include <cgmath/mat44.hpp>

namespace cgmath {

        quat<double> to_quat() const;

        bool is_valid() const;
        bool is_zero( double epsilon=0 ) const;
        bool is_identity( double epsilon=0 ) const;
        bool equal_to( const mat33& rhs, double epsilon=0 );
        
        double det() const;
        double norm2() const;
        double norm() const;

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
        
        mat33& scale( const vec<3,double>& s ) {
            return this->scale(s.x, s.y, s.z);
        }

        mat33& rotate( double angle, double ax, double ay, double az ) {
            return this->rotate(angle, vec<3,double>(ax, ay, az));
        }

        mat33& rotate( double angle, const vec<3,double>& axis ) {
            this->operator*=(mat33(angle, axis));
            return *this;
        }

        mat33& rotate( const quat<double>& q ) {
            this->operator*=(mat33(q));
            return *this;
        }

    template <typename T> mat33 dyadic_prod( const vec<3,T>& u, const vec<3,T>& v ) {
        mat33 m;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                m[i][j] = u[i] * v[j];
            }
        }
        return m;
    }
} 

#endif