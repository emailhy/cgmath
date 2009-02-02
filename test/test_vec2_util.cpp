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
#include <cgmath/vec2_util.hpp>

using namespace cgmath;


template <typename T> void test_vec2_util() {
    // length2, length
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


BOOST_AUTO_TEST_CASE( test_float_vec2_util ) {
    test_vec2_util<float>();
}


BOOST_AUTO_TEST_CASE( test_double_vec2_util ) {
    test_vec2_util<double>();
}
