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
        Range<T> r(1, 2);
        BOOST_REQUIRE_EQUAL( r.start(), 1 );
        BOOST_REQUIRE_EQUAL( r.end(), 2 );
    }
    {
        Range<T> r(2, 1);
        BOOST_REQUIRE_EQUAL( r.start(), 1 );
        BOOST_REQUIRE_EQUAL( r.end(), 2 );
    }

    {
        Range<T> r12(1,2);
        Range<T> r36(3,6);
        Range<T> r14(1,4);
        Range<T> r17(1,7);
        Range<T> r45(4,5);
        Range<T> r57(5,7);
        Range<T> r78(7,8);
        //BOOST_REQUIRE_EQUAL( r12.intersected(r36), Range<T>() );
        BOOST_REQUIRE_EQUAL( r14.intersected(r36), Range<T>(3,4) );
        BOOST_REQUIRE_EQUAL( r17.intersected(r36), Range<T>(3,6) );
        BOOST_REQUIRE_EQUAL( r45.intersected(r36), Range<T>(4,5) );
        BOOST_REQUIRE_EQUAL( r57.intersected(r36), Range<T>(5,6) );
        //BOOST_REQUIRE_EQUAL( r78.intersected(r36), Range<T>() );
    }
}


BOOST_AUTO_TEST_CASE( test_int_range ) {
    test_range<int>();
}


BOOST_AUTO_TEST_CASE( test_float_range ) {
    test_range<float>();
}
