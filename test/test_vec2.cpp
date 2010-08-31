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
#include <cgmath/vec2.h>

using namespace cgmath;


template <typename T> void test_vec2() {
    float src_f[2] = { 1, 2 };
    double src_d[2] = { 1, 2 };

    // constructors
    {
        vec2<T> a(1, 2);
        BOOST_REQUIRE_EQUAL( a.x, 1 );
        BOOST_REQUIRE_EQUAL( a.y, 2 );
    }
    {
        vec2<T> a(src_f);
        BOOST_REQUIRE_EQUAL( a.x, 1 );
        BOOST_REQUIRE_EQUAL( a.y, 2 );
    }
    {
        vec2<T> a(src_d);
        BOOST_REQUIRE_EQUAL( a.x, 1 );
        BOOST_REQUIRE_EQUAL( a.y, 2 );
    }
    {
        vec2<float> v(1, 2);
        vec2<T> a(v);
        BOOST_REQUIRE_EQUAL( a.x, 1 );
        BOOST_REQUIRE_EQUAL( a.y, 2 );
    }
    {
        vec2<double> v(1, 2);
        vec2<T> a(v);
        BOOST_REQUIRE_EQUAL( a.x, 1 );
        BOOST_REQUIRE_EQUAL( a.y, 2 );
    }

    // operators
    {
        vec2<T> a(1, 2);
        const vec2<T> b(4, 5);
        const vec2<T> e(3, 2);
        float f[2];
        double d[2];

        BOOST_CHECK_EQUAL( a == a, true );
        BOOST_CHECK_EQUAL( a == b, false );

        BOOST_CHECK_EQUAL( a[0], 1 );
        BOOST_CHECK_EQUAL( a[1], 2 );

        BOOST_CHECK_EQUAL( b[0], 4 );
        BOOST_CHECK_EQUAL( b[1], 5 );

        b.get(f);
        BOOST_CHECK_EQUAL( f[0], 4 );
        BOOST_CHECK_EQUAL( f[1], 5 );

        b.get(d);
        BOOST_CHECK_EQUAL( d[0], 4 );
        BOOST_CHECK_EQUAL( d[1], 5 );

        vec2<T> c(7, 8);
        c = a;
        BOOST_CHECK_EQUAL( c.x, 1 );
        BOOST_CHECK_EQUAL( c.y, 2 );

        c += a;
        BOOST_CHECK_EQUAL( c.x, 2 );
        BOOST_CHECK_EQUAL( c.y, 4 );

        c = a + b;
        BOOST_CHECK_EQUAL( c.x, 5 );
        BOOST_CHECK_EQUAL( c.y, 7 );

        c = b;
        c -= e;
        BOOST_CHECK_EQUAL( c.x, 1 );
        BOOST_CHECK_EQUAL( c.y, 3 );

        c = b - e;
        BOOST_CHECK_EQUAL( c.x, 1 );
        BOOST_CHECK_EQUAL( c.y, 3 );

        c = -a;
        BOOST_CHECK_EQUAL( c.x, -1 );
        BOOST_CHECK_EQUAL( c.y, -2 );

        c = a;
        c *= 2;
        BOOST_CHECK_EQUAL( c.x, 2 );
        BOOST_CHECK_EQUAL( c.y, 4 );

        c = static_cast<T>(2) * a;
        BOOST_CHECK_EQUAL( c.x, 2 );
        BOOST_CHECK_EQUAL( c.y, 4 );

        c = a * static_cast<T>(2);
        BOOST_CHECK_EQUAL( c.x, 2 );
        BOOST_CHECK_EQUAL( c.y, 4 );

        c = a;
        c /= 2;
        BOOST_CHECK_EQUAL( c.x, 0.5 );
        BOOST_CHECK_EQUAL( c.y, 1 );

        c = a / 2;
        BOOST_CHECK_EQUAL( c.x, 0.5 );
        BOOST_CHECK_EQUAL( c.y, 1 );
    }

    // length
    {
        const vec2<T> a(2, 5);
        BOOST_CHECK_EQUAL( length(a), sqrt(static_cast<T>(29)) );
    }

    // normalize
    {
        const vec2<T> a(2, 5);
        vec2<T> b;
        T s = 1 / sqrt(static_cast<T>(29));

        b = normalize(a);
        BOOST_CHECK_EQUAL( b.x, 2 * s);
        BOOST_CHECK_EQUAL( b.y, 5 * s);
    }
}


BOOST_AUTO_TEST_CASE( test_float_vec2 ) {
    test_vec2<float>();
}


BOOST_AUTO_TEST_CASE( test_double_vec2 ) {
    test_vec2<double>();
}
