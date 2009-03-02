/*
    Copyright (C) 2007-2009 by Jan Eric Kyprianidis <www.kyprianidis.com>
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
#include <cgmath/vec4.hpp>

using namespace cgmath;


template <typename T> void test_vec4() {
    float src_f[4] = { 1, 2, 3, 4 };
    double src_d[4] = { 1, 2, 3, 4 };

    // constructors
    {
        vec4<T> a(1, 2, 3, 4);
        BOOST_REQUIRE_EQUAL( a.x, 1 );
        BOOST_REQUIRE_EQUAL( a.y, 2 );
        BOOST_REQUIRE_EQUAL( a.z, 3 );
		BOOST_REQUIRE_EQUAL( a.w, 4 );
    }
    {
        vec4<T> a(src_f);
        BOOST_REQUIRE_EQUAL( a.x, 1 );
        BOOST_REQUIRE_EQUAL( a.y, 2 );
        BOOST_REQUIRE_EQUAL( a.z, 3 );
		BOOST_REQUIRE_EQUAL( a.w, 4 );
    }
    {
        vec4<T> a(src_d);
        BOOST_REQUIRE_EQUAL( a.x, 1 );
        BOOST_REQUIRE_EQUAL( a.y, 2 );
        BOOST_REQUIRE_EQUAL( a.z, 3 );
		BOOST_REQUIRE_EQUAL( a.w, 4 );
    }
    {
        vec4<float> v(1, 2, 3, 4);
        vec4<T> a(v);
        BOOST_REQUIRE_EQUAL( a.x, 1 );
        BOOST_REQUIRE_EQUAL( a.y, 2 );
        BOOST_REQUIRE_EQUAL( a.z, 3 );
		BOOST_REQUIRE_EQUAL( a.w, 4 );
    }
    {
        vec4<double> v(1, 2, 3, 4);
        vec4<T> a(v);
        BOOST_REQUIRE_EQUAL( a.x, 1 );
        BOOST_REQUIRE_EQUAL( a.y, 2 );
        BOOST_REQUIRE_EQUAL( a.z, 3 );
		BOOST_REQUIRE_EQUAL( a.w, 4 );
    }

    // operators
    {
        vec4<T> a(1, 2, 3, 4);
        const vec4<T> b(5, 6, 7, 8);
        const vec4<T> e(4, 3, 2, 1);
        float f[4];
        double d[4];

        BOOST_CHECK_EQUAL( a == a, true );
        BOOST_CHECK_EQUAL( a == b, false );

        BOOST_CHECK_EQUAL( a[0], 1 );
        BOOST_CHECK_EQUAL( a[1], 2 );
        BOOST_CHECK_EQUAL( a[2], 3 );
		BOOST_CHECK_EQUAL( a[3], 4 );

        BOOST_CHECK_EQUAL( b[0], 5 );
        BOOST_CHECK_EQUAL( b[1], 6 );
        BOOST_CHECK_EQUAL( b[2], 7 );
		BOOST_CHECK_EQUAL( b[3], 8 );

        b.get(f);
        BOOST_CHECK_EQUAL( f[0], 5 );
        BOOST_CHECK_EQUAL( f[1], 6 );
        BOOST_CHECK_EQUAL( f[2], 7 );
		BOOST_CHECK_EQUAL( f[3], 8 );

        b.get(d);
        BOOST_CHECK_EQUAL( d[0], 5 );
        BOOST_CHECK_EQUAL( d[1], 6 );
        BOOST_CHECK_EQUAL( d[2], 7 );
		BOOST_CHECK_EQUAL( d[3], 8 );

        vec4<T> c(7, 8, 9, 10);
        c = a;
        BOOST_CHECK_EQUAL( c.x, 1 );
        BOOST_CHECK_EQUAL( c.y, 2 );
        BOOST_CHECK_EQUAL( c.z, 3 );
		BOOST_CHECK_EQUAL( c.w, 4 );

        c += a;
        BOOST_CHECK_EQUAL( c.x, 2 );
        BOOST_CHECK_EQUAL( c.y, 4 );
        BOOST_CHECK_EQUAL( c.z, 6 );
		BOOST_CHECK_EQUAL( c.w, 8 );

        c = a + b;
        BOOST_CHECK_EQUAL( c.x, 6 );
        BOOST_CHECK_EQUAL( c.y, 8 );
        BOOST_CHECK_EQUAL( c.z, 10 );
		BOOST_CHECK_EQUAL( c.w, 12 );

        c = b;
        c -= e;
        BOOST_CHECK_EQUAL( c.x, 1 );
        BOOST_CHECK_EQUAL( c.y, 3 );
        BOOST_CHECK_EQUAL( c.z, 5 );
		BOOST_CHECK_EQUAL( c.w, 7 );

        c = b - e;
        BOOST_CHECK_EQUAL( c.x, 1 );
        BOOST_CHECK_EQUAL( c.y, 3 );
        BOOST_CHECK_EQUAL( c.z, 5 );
		BOOST_CHECK_EQUAL( c.w, 7 );

        c = -a;
        BOOST_CHECK_EQUAL( c.x, -1 );
        BOOST_CHECK_EQUAL( c.y, -2 );
        BOOST_CHECK_EQUAL( c.z, -3 );
		BOOST_CHECK_EQUAL( c.w, -4 );

        c = a;
        c *= 2;
        BOOST_CHECK_EQUAL( c.x, 2 );
        BOOST_CHECK_EQUAL( c.y, 4 );
        BOOST_CHECK_EQUAL( c.z, 6 );
		BOOST_CHECK_EQUAL( c.w, 8 );

        c = static_cast<T>(2) * a;
        BOOST_CHECK_EQUAL( c.x, 2 );
        BOOST_CHECK_EQUAL( c.y, 4 );
        BOOST_CHECK_EQUAL( c.z, 6 );
		BOOST_CHECK_EQUAL( c.w, 8 );

        c = a * static_cast<T>(2);
        BOOST_CHECK_EQUAL( c.x, 2 );
        BOOST_CHECK_EQUAL( c.y, 4 );
        BOOST_CHECK_EQUAL( c.z, 6 );
		BOOST_CHECK_EQUAL( c.w, 8 );

        c = a;
        c /= 2;
        BOOST_CHECK_EQUAL( c.x, 0.5 );
        BOOST_CHECK_EQUAL( c.y, 1 );
        BOOST_CHECK_EQUAL( c.z, 1.5 );
		BOOST_CHECK_EQUAL( c.w, 2 );

        c = a / 2;
        BOOST_CHECK_EQUAL( c.x, 0.5 );
        BOOST_CHECK_EQUAL( c.y, 1 );
        BOOST_CHECK_EQUAL( c.z, 1.5 );
		BOOST_CHECK_EQUAL( c.w, 2 );
    }
}


BOOST_AUTO_TEST_CASE( test_float_vec4 ) {
    test_vec4<float>();
}


BOOST_AUTO_TEST_CASE( test_double_vec4 ) {
    test_vec4<double>();
}
