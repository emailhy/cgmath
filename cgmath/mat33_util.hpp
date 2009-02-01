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
#ifndef CGMATH_INCLUDED_MAT33_UTIL_HPP
#define CGMATH_INCLUDED_MAT33_UTIL_HPP

#include <cgmath/mat33.hpp>
#include <iostream>

namespace cgmath {

    template <typename T> std::ostream& operator<<( std::ostream& os, const mat33<T>& m ) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                os << m[i][j];
                if ((i != 2) || (j != 2)) os << " ";
            }
        }
        return os;
    }


    template <typename T> std::istream& operator>>( std::istream& is, mat33<T>& m ) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                is >> m[i][j];
            }
        }
        return is;
    }

#if 0
    mat33::mat33( const float *src, bool column_major /*= true */ ) {
        if (column_major) {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) m[i][j] = static_cast<float>(src[3*i+j]);
        } else {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) m[j][i] = static_cast<float>(src[3*i+j]);
        }
    }


    mat33::mat33( const double *src, bool column_major /*= true */ ) {
        if (column_major) {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) m[i][j] = src[3*i+j];
        } else {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) m[j][i] = src[3*i+j];
        }
    }

    mat33::mat33( double angle, const vec<3,double>& axis ) {
        vec<3,double> u(axis);
        if (u.normalize() > 0) {
            const double rangle = radians(angle);
            const double c = cos(rangle);
            const double s = sin(rangle);
            
            m[0][0] = c + (1 - c) * u.x * u.x;
            m[0][1] = (1 - c) * u.x * u.y - s * u.z;    
            m[0][2] = (1 - c) * u.x * u.z + s * u.y;
            m[1][0] = (1 - c) * u.y * u.x + s * u.z;
            m[1][1] = c + (1 - c) * u.y * u.y;    
            m[1][2] = (1 - c) * u.y * u.z - s * u.x;
            m[2][0] = (1 - c) * u.z * u.x - s * u.y;
            m[2][1] = (1 - c) * u.z * u.y + s * u.x;
            m[2][2] = c + (1 - c) * u.z * u.z;
        } else  {
            identity();
        }
    }


    mat33::mat33( const quat<double>& q ) {
        double s, xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz, l;
        l = q.length2();
        if (l > 0) {
            s = 2.0 / l;

            xs = q.x * s;   ys = q.y * s;  zs = q.z * s;
            wx = q.w * xs;  wy = q.w * ys; wz = q.w * zs;
            xx = q.x * xs;  xy = q.x * ys; xz = q.x * zs;
            yy = q.y * ys;  yz = q.y * zs; zz = q.z * zs;

            m[0][0] = 1.0 - (yy + zz);
            m[0][1] = xy - wz;
            m[0][2] = xz + wy;
            m[1][0] = xy + wz;
            m[1][1] = 1.0 - (xx + zz);
            m[1][2] = yz - wx;
            m[2][0] = xz - wy;
            m[2][1] = yz + wx;
            m[2][2] = 1.0 - (xx + yy);
        } else {
            identity();
        }
    }

    bool mat33::is_valid() const {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (!cgmath::is_valid(m[i][j])) return false;
            }
        }
        return true;
    }


    bool mat33::is_zero( double epsilon ) const {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (!almost_equal(m[i][j], 0.0, epsilon)) return false;
            }
        }
        return true;
    }


    bool mat33::is_identity( double epsilon ) const {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (!almost_equal(m[i][j], ((i == j)? 1.0 : 0.0), epsilon)) return false;
            }
        }
        return true;
    }


    bool mat33::equal_to( const mat33& rhs, double epsilon) {
        for (int i = 0; i < 3; ++i) 
            for (int j = 0; j < 3; ++j) 
                if (!almost_equal(m[i][j], rhs.m[i][j], epsilon)) return false;
        return true;
    }


    double mat33::det() const {
        return det3x3(m[0][0], m[0][1], m[0][2],  m[1][0], m[1][1], m[1][2],  m[2][0], m[2][1], m[2][2]);
    }


    double mat33::norm2() const {
        double n2 = 0;
        for (int i = 0; i < 3; ++i) 
            for (int j = 0; j < 3; ++j) n2 += m[i][j] * m[i][j];
        return n2;
    }


    double mat33::norm() const {
        return sqrt(norm2());
    }


    quat<double> mat33::to_quat() const
    {
        double tr,s;
        int i,j,k;
        static int nxt[3] = {1,2,0};
        quat<double> q;

        tr = m[0][0] + m[1][1] + m[2][2];
        if (tr > 0.0) {
            q[3] = 0.5 * sqrt(tr + 1.0);
            s = 0.25 / q[3];
            q[0] = (m[2][1] - m[1][2]) * s;
            q[1] = (m[0][2] - m[2][0]) * s;
            q[2] = (m[1][0] - m[0][1]) * s;
        }
        else {
            i = 0;
            if (m[1][1] > m[0][0]) i = 1;
            if (m[2][2] > m[i][i]) i = 2;
            j = nxt[i];
            k = nxt[j];
            q[i] = 0.5 * sqrt(m[i][i] - m[j][j] - m[k][k] + 1.0);
            s = 0.25f / q[i];
            q[3] = (m[k][j] - m[j][k]) * s;
            q[j] = (m[j][i] + m[i][j]) * s;
            q[k] = (m[k][i] + m[i][k]) * s;
        }

        return q;
    }


    mat33& mat33::adjoint() {
        mat33 M(*this);

        m[0][0] =  det2x2(M[1][1], M[1][2], M[2][1], M[2][2]);
        m[0][1] = -det2x2(M[1][0], M[1][2], M[2][0], M[2][2]);
        m[0][2] =  det2x2(M[1][0], M[1][1], M[2][0], M[2][1]);

        m[1][0] = -det2x2(M[0][1], M[0][2], M[2][1], M[2][2]);
        m[1][1] =  det2x2(M[0][0], M[0][2], M[2][0], M[2][2]);
        m[1][2] = -det2x2(M[0][0], M[0][1], M[2][0], M[2][1]);

        m[2][0] =  det2x2(M[0][1], M[0][2], M[1][1], M[1][2]);
        m[2][1] = -det2x2(M[0][0], M[0][2], M[1][0], M[1][2]);
        m[2][2] =  det2x2(M[0][0], M[0][1], M[1][0], M[1][1]);

        return *this;
    }


    bool mat33::invert() {
        mat33 in(*this);
        double det_1;
        double pos, neg, temp;

        pos = neg = 0.0;
        for (int i = 0; i < 3; ++i) {
            temp =  in[i][0] * in[(i+1)%3][1] * in[(i+2)%3][2];
            if (temp >= 0.0) 
                pos += temp; 
            else 
                neg += temp;

            temp =  -in[i][0] * in[(i+2)%3][1] * in[(i+1)%3][2];
            if (temp >= 0.0) 
                pos += temp; 
            else 
                neg += temp;
        }

        det_1 = pos + neg;
        if ((det_1 == 0.0) || (fabs(det_1 / (pos - neg)) < 1e-15)) {
            return false;
        }

        det_1 = 1.0 / det_1;
        m[0][0] =   ( in[1][1] * in[2][2] - in[2][1] * in[1][2] ) * det_1;
        m[0][1] = - ( in[0][1] * in[2][2] - in[2][1] * in[0][2] ) * det_1;
        m[0][2] =   ( in[0][1] * in[1][2] - in[1][1] * in[0][2] ) * det_1;
        m[1][0] = - ( in[1][0] * in[2][2] - in[2][0] * in[1][2] ) * det_1;
        m[1][1] =   ( in[0][0] * in[2][2] - in[2][0] * in[0][2] ) * det_1;
        m[1][2] = - ( in[0][0] * in[1][2] - in[1][0] * in[0][2] ) * det_1;
        m[2][0] =   ( in[1][0] * in[2][1] - in[2][0] * in[1][1] ) * det_1;
        m[2][1] = - ( in[0][0] * in[2][1] - in[2][0] * in[0][1] ) * det_1;
        m[2][2] =   ( in[0][0] * in[1][1] - in[1][0] * in[0][1] ) * det_1;

        return true;
    }


    mat33& mat33::scale( double sx, double sy, double sz ) {
        for (int i = 0; i < 3; ++i) {
            m[i][0] *= sx;
            m[i][1] *= sy;
            m[i][2] *= sz;
        }
        return *this;
    }

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
#endif
}

#endif
