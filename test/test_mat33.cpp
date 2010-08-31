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
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <cgmath/mat33.h>
#include <cgmath/vec3.h>


using namespace cgmath;


template <typename T> void test_mat33() { 
    const T id_matrix[3][3] = {
        { 1, 0, 0 },
        { 0, 1, 0 },
        { 0, 0, 1 }
    };

    const T p_lhs[9] = {  2,  3,  5,  7, 11, 13,  17, 19, 23  };
    const T p_rhs[9] = { 29, 31, 37,  41, 43, 47,  53, 59, 61 };
    const T p_add[9] = { 2+29, 3+31, 5+37, 7+41, 11+43, 13+47, 17+53, 19+59, 23+61 };
    const T p_sub[9] = { 2-29, 3-31, 5-37, 7-41, 11-43, 13-47, 17-53, 19-59, 23-61 };
    const T p_mul[9] = {
         2*29 +  3*41 +  5*53,  2*31 +  3*43 +  5*59,  2*37 +  3*47 +  5*61,
         7*29 + 11*41 + 13*53,  7*31 + 11*43 + 13*59,  7*37 + 11*47 + 13*61,
        17*29 + 19*41 + 23*53, 17*31 + 19*43 + 23*59, 17*37 + 19*47 + 23*61
    };

    const T p_lhs_det = 2*11*23 + 3*13*17 + 5*7*19 - 17*11*5 - 19*13*2 - 23*7*3;
    const T p_lhs_adjoint[9] =  {
        11*23 - 19*13, -(7*23 - 17*13), 7*19 - 17*11,
        -(3*23 - 19*5), 2*23 - 17*5, -(2*19 - 17*3),
        3*13 - 11*5, -(2*13 - 7*5), 2*11 - 7*3
    };
    const T p_lhs_norm2 = 2*2 + 3*3 + 5*5 + 7*7 + 11*11 + 13*13 + 17*17 + 19*19 + 23*23;
    const T p_lhs_norm = sqrt(p_lhs_norm2);

    const float src_f[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    const double src_d[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    // constructors
    {
        mat33<T> id(1);
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                BOOST_CHECK_EQUAL(id[i][j], id_matrix[i][j]);
    }
    {
        mat33<T> m_9(1, 2, 3, 4, 5, 6, 7, 8 , 9);
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                BOOST_CHECK_EQUAL(m_9[i][j], 3*i+j+1);
    }
    {
        mat33<T> m_f(src_f);
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                BOOST_CHECK_EQUAL(m_f[i][j], 3*i+j+1);
    }
    {
        mat33<T> m_f(src_f, false);
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                BOOST_CHECK_EQUAL(m_f[i][j], i+j*3+1);
    }
    {
        mat33<T> m_d(src_d);
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                BOOST_CHECK_EQUAL(m_d[i][j], 3*i+j+1);
    }
    {
        mat33<T> m_d(src_d, false);
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                BOOST_CHECK_EQUAL(m_d[i][j], i+3*j+1);
    }
    {
        vec3<T> av(1,4,7);
        vec3<T> bv(2,5,8);
        vec3<T> cv(3,6,9);
        mat33<T> m_3v(av, bv, cv);
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                BOOST_CHECK_EQUAL(m_3v[i][j], 3*i+j+1);
    }
    {
        mat33<T> lhs(p_lhs);
        mat33<T> rhs(p_rhs);
        mat33<T> mul33(lhs, rhs);
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                BOOST_CHECK_EQUAL(mul33[i][j], p_mul[3*i+j]);
    }

    // operators
    {
        mat33<T> A(1,2,3, 4,5,6, 7,8,9);
        BOOST_CHECK_EQUAL(A == A, true);
        BOOST_CHECK_EQUAL(A != A, false);

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                mat33<T> B(A);
                B[i][j] += 1;
                BOOST_CHECK_EQUAL(A == B, false);
                BOOST_CHECK_EQUAL(A != B, true);
            }
        }

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                BOOST_CHECK_EQUAL(A[i][j], 3*i+j+1);

        const mat33<T> C(1,2,3, 4,5,6, 7,8,9);
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                BOOST_CHECK_EQUAL(C[i][j], 3*i+j+1);

        float fbuf[9];
        memset(fbuf, sizeof(fbuf), 0);
        C.get(fbuf);
        for (int i = 0; i < 9; ++i)
            BOOST_CHECK_EQUAL(fbuf[i], i+1);
        memset(fbuf, sizeof(fbuf), 0);
        C.get(fbuf, false);
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                BOOST_CHECK_EQUAL(fbuf[i+j*3], i*3+j+1);

        double dbuf[9];
        C.get(dbuf);
        for (int i = 0; i < 9; ++i)
            BOOST_CHECK_EQUAL(dbuf[i], i+1);
        memset(dbuf, sizeof(fbuf), 0);
        C.get(dbuf, false);
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                BOOST_CHECK_EQUAL(fbuf[i+j*3], i*3+j+1);

        BOOST_CHECK_EQUAL(A.get_column(0), (vec3<T>(1,4,7)));
        BOOST_CHECK_EQUAL(A.get_column(1), (vec3<T>(2,5,8)));
        BOOST_CHECK_EQUAL(A.get_column(2), (vec3<T>(3,6,9)));

        BOOST_CHECK_EQUAL(A.get_row(0), (vec3<T>(1,2,3)));
        BOOST_CHECK_EQUAL(A.get_row(1), (vec3<T>(4,5,6)));
        BOOST_CHECK_EQUAL(A.get_row(2), (vec3<T>(7,8,9)));
    }

    {
        for (int k = 0; k < 3; ++k) {
            mat33<T> A(1,2,3, 4,5,6, 7,8,9);
            A.set_column(k, vec3<T>(-1, -2, -3));

            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    BOOST_CHECK_EQUAL(A[i][j], (j == k)? -(i+1) : 3*i+j+1);
        }

        for (int k = 0; k < 3; ++k) {
            mat33<T> A(1,2,3, 4,5,6, 7,8,9);
            A.set_row(k, vec3<T>(-1, -2, -3));

            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    BOOST_CHECK_EQUAL(A[i][j], (i == k)? -(j+1) : 3*i+j+1);
        }
    }

    {
        mat33<T> lhs(p_lhs);
        mat33<T> rhs(p_rhs);

        {
            mat33<T> mul_result(p_mul);
            BOOST_CHECK_EQUAL(lhs * rhs, mul_result);
            mat33<T> A(lhs);
            A *= rhs;
            BOOST_CHECK_EQUAL(A, mul_result);
        }

        {
            mat33<T> B(1,2,3, 4,5,6, 7,8,9);
            mat33<T> C(B);
            B *= 11;
            mat33<T> D = C * static_cast<T>(11);
            mat33<T> E = static_cast<T>(11) * C;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    BOOST_CHECK_EQUAL(B[i][j], 11 * (3*i+j+1));
                    BOOST_CHECK_EQUAL(D[i][j], 11 * (3*i+j+1));
                    BOOST_CHECK_EQUAL(E[i][j], 11 * (3*i+j+1));
                }
            }
        }

        {
            mat33<T> add_result(p_add);
            BOOST_CHECK_EQUAL(lhs + rhs, add_result);
            mat33<T> A(lhs);
            A += rhs;
            BOOST_CHECK_EQUAL(A, add_result);
        }

        {
            mat33<T> sub_result(p_sub);
            BOOST_CHECK_EQUAL(lhs - rhs, sub_result);
            mat33<T> A(lhs);
            A -= rhs;
            BOOST_CHECK_EQUAL(A, sub_result);

            mat33<T> B(1,2,3, 4,5,6, 7,8,9);
            mat33<T> C = -B;
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    BOOST_CHECK_EQUAL(C[i][j], -(3*i+j+1));
        }
    }

    {
        mat33<T> A(2, 3, 5, 7, 11, 13, 17, 19, 23);

        vec3<float> fv(29, 31, 37);
        vec3<float> fr = A.transform(fv);
        BOOST_CHECK_EQUAL( fr, (vec3<float>(2*29 + 3*31 + 5*37, 7*29 + 11*31 + 13*37, 17*29 + 19*31 + 23*37)));
        
        vec3<double> dv(29, 31, 37);
        vec3<double> dr = A.transform(dv);
        BOOST_CHECK_EQUAL( dr, (vec3<double>(2*29 + 3*31 + 5*37, 7*29 + 11*31 + 13*37, 17*29 + 19*31 + 23*37)));
    }

    /*{
        mat33 A(1,2,3, 4,5,6, 7,8,9);
        BOOST_CHECK_EQUAL(A.is_valid(), true);

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                mat33 B(A);
                B.m[i][j] = std::numeric_limits<double>::signaling_NaN();
                BOOST_CHECK_EQUAL(B.is_valid(), false);

                mat33 C(A);
                C.m[i][j] = std::numeric_limits<double>::quiet_NaN();
                BOOST_CHECK_EQUAL(C.is_valid(), false);

                mat33 D(A);
                D.m[i][j] = std::numeric_limits<double>::infinity();
                BOOST_CHECK_EQUAL(D.is_valid(), false);
            }
        }
    }*/

    {
        mat33<T> A(p_lhs);
        BOOST_CHECK_EQUAL( det(A), p_lhs_det );
        BOOST_CHECK_EQUAL( norm2(A), p_lhs_norm2 );
        BOOST_CHECK_EQUAL( norm(A), p_lhs_norm );
    }

    {
        mat33<T> C(1,2,3, 4,5,6, 7,8,9);
        mat33<T> Ct(1,4,7, 2,5,8, 3,6,9);
        BOOST_CHECK_EQUAL( transpose(C), Ct );
    }

    {
        mat33<T> A(p_lhs);
        mat33<T> adjA(p_lhs_adjoint);
        BOOST_CHECK_EQUAL( adjoint(A), adjA );
    }

    {
        mat33<T> A(3,2,6, 1,1,3, -3,-2,-5);
        mat33<T> invA(1,-2,0, -4,3,-3, 1,0,1);
        bool result = invert(&A);
        BOOST_CHECK( result );
        BOOST_CHECK_EQUAL( A, invA );
    }
}


BOOST_AUTO_TEST_CASE( test_mat33_double ) {
    test_mat33<double>();
}

