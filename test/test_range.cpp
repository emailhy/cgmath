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
#include <cgmath/range.h>

using namespace cgmath;


template <typename T> void test_range() {
    {
        range<T> r(1, 2);
        BOOST_REQUIRE_EQUAL( r.get_min(), 1 );
        BOOST_REQUIRE_EQUAL( r.get_max(), 2 );
    }
    {
        range<T> r(2, 1);
        BOOST_REQUIRE_EQUAL( r.get_min(), 1 );
        BOOST_REQUIRE_EQUAL( r.get_max(), 2 );
    }

    {
        range<T> r12(1,2);
        range<T> r36(3,6);
        range<T> r14(1,4);
        range<T> r17(1,7);
        range<T> r45(4,5);
        range<T> r57(5,7);
        range<T> r78(7,8);
        BOOST_REQUIRE_EQUAL( intersect(r12, r36), range<T>() );
        BOOST_REQUIRE_EQUAL( intersect(r14, r36), range<T>(3,4) );
        BOOST_REQUIRE_EQUAL( intersect(r17, r36), range<T>(3,6) );
        BOOST_REQUIRE_EQUAL( intersect(r45, r36), range<T>(4,5) );
        BOOST_REQUIRE_EQUAL( intersect(r57, r36), range<T>(5,6) );
        BOOST_REQUIRE_EQUAL( intersect(r78, r36), range<T>() );
    }
}


BOOST_AUTO_TEST_CASE( test_int_range ) {
    test_range<int>();
}


BOOST_AUTO_TEST_CASE( test_float_range ) {
    test_range<float>();
}
