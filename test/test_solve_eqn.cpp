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
#include <math3d/solve_eqn.hpp>


using namespace math3d;


BOOST_AUTO_TEST_CASE( test_solve_eqn_quadratic )
{
    double x1, x2;
    bool result;

    // x^2 + x + 1 = 0
    result = solve_eqn_quadratic(1, 1, 1, &x1, &x2);
    BOOST_CHECK(!result);

    // 5x^2 + 5x - 30 = 5(x - 2)(x + 3) = 0
    result = solve_eqn_quadratic(5, 5, -30, &x1, &x2);
    BOOST_CHECK(result);
    BOOST_CHECK_EQUAL(x1, 2);
    BOOST_CHECK_EQUAL(x2, -3);

    // 5x^2 - 5x - 30 = 5(x + 2)(x - 3) = 0
    result = solve_eqn_quadratic(5, -5, -30, &x1, &x2);
    BOOST_CHECK(result);
    BOOST_CHECK_EQUAL(x1, 3);
    BOOST_CHECK_EQUAL(x2, -2);

    // 5x^2 - 5 = 5(x - 1)(x + 1) = 0
    result = solve_eqn_quadratic(5, 0, -5, &x1, &x2);
    BOOST_CHECK(result);
    BOOST_CHECK_EQUAL(x1, 1);
    BOOST_CHECK_EQUAL(x2, -1);

    // 2x - 4 = 0
    result = solve_eqn_quadratic(0, 2, -4, &x1, &x2);
    BOOST_CHECK(result);
    BOOST_CHECK_EQUAL(x1, 2);
    BOOST_CHECK_EQUAL(x2, 2);

    // 1 = 0
    result = solve_eqn_quadratic(0, 0, 1, &x1, &x2);
    BOOST_CHECK(!result);
}
