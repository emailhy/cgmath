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
#include <cgmath/vec3.hpp>
#include <cgmath/vec3_util.hpp>

using namespace cgmath;

template <typename T> void test_basic_vec3() {
    float src_f[3] = { 1, 2, 3 };
    double src_d[3] = { 1, 2, 3 };

    // constructors
    {
        vec<3,T> a(1, 2, 3);
        BOOST_REQUIRE_EQUAL( a.x, 1 );
        BOOST_REQUIRE_EQUAL( a.y, 2 );
        BOOST_REQUIRE_EQUAL( a.z, 3 );
    }
    {
        vec<3,T> a(src_f);
        BOOST_REQUIRE_EQUAL( a.x, 1 );
        BOOST_REQUIRE_EQUAL( a.y, 2 );
        BOOST_REQUIRE_EQUAL( a.z, 3 );
    }
    {
        vec<3,T> a(src_d);
        BOOST_REQUIRE_EQUAL( a.x, 1 );
        BOOST_REQUIRE_EQUAL( a.y, 2 );
        BOOST_REQUIRE_EQUAL( a.z, 3 );
    }
    {
        vec<3,float> v(1, 2, 3);
        vec<3,T> a(v);
        BOOST_REQUIRE_EQUAL( a.x, 1 );
        BOOST_REQUIRE_EQUAL( a.y, 2 );
        BOOST_REQUIRE_EQUAL( a.z, 3 );
    }
    {
        vec<3,double> v(1, 2, 3);
        vec<3,T> a(v);
        BOOST_REQUIRE_EQUAL( a.x, 1 );
        BOOST_REQUIRE_EQUAL( a.y, 2 );
        BOOST_REQUIRE_EQUAL( a.z, 3 );
    }

    // operators
    {
        vec<3,T> a(1, 2, 3);
        const vec<3,T> b(4, 5, 6);
        const vec<3,T> e(3, 2, 1);
        float f[3];
        double d[3];

        BOOST_CHECK_EQUAL( a == a, true );
        BOOST_CHECK_EQUAL( a == b, false );

        BOOST_CHECK_EQUAL( a[0], 1 );
        BOOST_CHECK_EQUAL( a[1], 2 );
        BOOST_CHECK_EQUAL( a[2], 3 );

        BOOST_CHECK_EQUAL( b[0], 4 );
        BOOST_CHECK_EQUAL( b[1], 5 );
        BOOST_CHECK_EQUAL( b[2], 6 );

        b.get(f);
        BOOST_CHECK_EQUAL( f[0], 4 );
        BOOST_CHECK_EQUAL( f[1], 5 );
        BOOST_CHECK_EQUAL( f[2], 6 );

        b.get(d);
        BOOST_CHECK_EQUAL( d[0], 4 );
        BOOST_CHECK_EQUAL( d[1], 5 );
        BOOST_CHECK_EQUAL( d[2], 6 );

        vec<3,T> c(7, 8, 9);
        c = a;
        BOOST_CHECK_EQUAL( c.x, 1 );
        BOOST_CHECK_EQUAL( c.y, 2 );
        BOOST_CHECK_EQUAL( c.z, 3 );

        c += a;
        BOOST_CHECK_EQUAL( c.x, 2 );
        BOOST_CHECK_EQUAL( c.y, 4 );
        BOOST_CHECK_EQUAL( c.z, 6 );

        c = a + b;
        BOOST_CHECK_EQUAL( c.x, 5 );
        BOOST_CHECK_EQUAL( c.y, 7 );
        BOOST_CHECK_EQUAL( c.z, 9 );

        c = b;
        c -= e;
        BOOST_CHECK_EQUAL( c.x, 1 );
        BOOST_CHECK_EQUAL( c.y, 3 );
        BOOST_CHECK_EQUAL( c.z, 5 );

        c = b - e;
        BOOST_CHECK_EQUAL( c.x, 1 );
        BOOST_CHECK_EQUAL( c.y, 3 );
        BOOST_CHECK_EQUAL( c.z, 5 );

        c = -a;
        BOOST_CHECK_EQUAL( c.x, -1 );
        BOOST_CHECK_EQUAL( c.y, -2 );
        BOOST_CHECK_EQUAL( c.z, -3 );

        c = a;
        c *= 2;
        BOOST_CHECK_EQUAL( c.x, 2 );
        BOOST_CHECK_EQUAL( c.y, 4 );
        BOOST_CHECK_EQUAL( c.z, 6 );

        c = static_cast<T>(2) * a;
        BOOST_CHECK_EQUAL( c.x, 2 );
        BOOST_CHECK_EQUAL( c.y, 4 );
        BOOST_CHECK_EQUAL( c.z, 6 );

        c = a * static_cast<T>(2);
        BOOST_CHECK_EQUAL( c.x, 2 );
        BOOST_CHECK_EQUAL( c.y, 4 );
        BOOST_CHECK_EQUAL( c.z, 6 );

        c = a;
        c /= 2;
        BOOST_CHECK_EQUAL( c.x, 0.5 );
        BOOST_CHECK_EQUAL( c.y, 1 );
        BOOST_CHECK_EQUAL( c.z, 1.5 );

        c = a / 2;
        BOOST_CHECK_EQUAL( c.x, 0.5 );
        BOOST_CHECK_EQUAL( c.y, 1 );
        BOOST_CHECK_EQUAL( c.z, 1.5 );
    }

    // length2, length
    {
        const vec<3,T> a(2, 3, 5);
        BOOST_CHECK_EQUAL( a.length2(), 38 );
        BOOST_CHECK_EQUAL( a.length(), sqrt(static_cast<T>(38)) );
    }


    {
        const vec<3,T> a(2, 3, 5);
        vec<3,T> b;
        T s = 1 / sqrt(static_cast<T>(38));

        b = a;
        T len = b.normalize();
        BOOST_CHECK_EQUAL( len, sqrt(static_cast<T>(38)) );
        BOOST_CHECK_CLOSE_FRACTION( b.length2(), static_cast<T>(1), std::numeric_limits<T>::epsilon());
        BOOST_CHECK_EQUAL( b.x, 2 * s);
        BOOST_CHECK_EQUAL( b.y, 3 * s);
        BOOST_CHECK_EQUAL( b.z, 5 * s);

        len = a.length();
        b = normalize(a);
        BOOST_CHECK_EQUAL( len, sqrt(static_cast<T>(38)) );
        BOOST_CHECK_CLOSE_FRACTION( b.length2(), static_cast<T>(1), std::numeric_limits<T>::epsilon());
        BOOST_CHECK_EQUAL( b.x, 2 * s );
        BOOST_CHECK_EQUAL( b.y, 3 * s );
        BOOST_CHECK_EQUAL( b.z, 5 * s );
    }
}


BOOST_AUTO_TEST_CASE( test_float_vec3 ) {
    test_basic_vec3<float>();
}


BOOST_AUTO_TEST_CASE( test_double_vec3 ) {
    test_basic_vec3<double>();
}
