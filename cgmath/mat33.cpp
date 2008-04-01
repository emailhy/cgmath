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
#include <cgmath/types.hpp>
#include <cgmath/mat33.hpp>
#include <cgmath/mat44.hpp>
#include <cgmath/quat.hpp>
#include <iostream>

namespace cgmath {

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


    mat33::mat33( const vec3<double>& a, const vec3<double>& b, const vec3<double>& c ) {
        for (int i = 0; i < 3; ++i) {
            m[i][0] = a[i];
            m[i][1] = b[i];
            m[i][2] = c[i];
        }
    }


    mat33::mat33( const mat44& M ) {
        for (int i = 0; i < 3; ++i) 
            for (int j = 0; j < 3; ++j) m[i][j] = M.m[i][j];
    }


    mat33::mat33( double angle, const vec3<double>& axis ) {
        vec3<double> u(axis);
        if (u.normalize() > 0) {
            const double rangle = to_rad(angle);
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


    void mat33::set( const float *src, bool column_major /*= true */ ) {
        if (column_major) {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) m[i][j] = static_cast<float>(src[3*i+j]);
        } else {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) m[j][i] = static_cast<float>(src[3*i+j]);
        }
    }


    void mat33::set( const double *src, bool column_major /*= true */ ) {
        if (column_major) {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) m[i][j] = src[3*i+j];
        } else {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) m[j][i] = src[3*i+j];
        }
    }


    void mat33::get( float *dst, bool column_major /*= true */ ) const {
        if (column_major) {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) dst[3*i+j] = static_cast<float>(m[i][j]);
        } else {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) dst[3*i+j] = static_cast<float>(m[j][i]);
        }
    }


    void mat33::get( double *dst, bool column_major /*= true */ ) const {
        if (column_major) {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) dst[3*i+j] = m[i][j];
        } else {
            for (int i = 0; i < 3; ++i) 
                for (int j = 0; j < 3; ++j) dst[3*i+j] = m[j][i];
        }
    }


    void mat33::set_column( int column, const vec3<double>& v ) {
        m[0][column] = v.x;
        m[1][column] = v.y;
        m[2][column] = v.z;
    }


    vec3<double> mat33::get_column( int column ) const {
        return vec3<double>(m[0][column], m[1][column], m[2][column]);
    }


    void mat33::set_row( int row, const vec3<double>& v ){
        m[row][0] = v.x;
        m[row][1] = v.y;
        m[row][2] = v.z;
    }


    vec3<double> mat33::get_row( int row ) const {
        return vec3<double>(m[row][0], m[row][1], m[row][2]);
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


    std::ostream& operator<<( std::ostream& os, const mat33& m ) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                os << m[i][j];
                if ((i != 2) || (j != 2)) os << " ";
            }
        }
        return os;
    }


    std::istream& operator>>( std::istream& is, mat33& m ) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                is >> m[i][j];
            }
        }
        return is;
    }
}


