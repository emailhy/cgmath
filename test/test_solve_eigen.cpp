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
#include <cgmath/solve_eigen.h>
#include <cgmath/mat33.h>

using namespace cgmath;


BOOST_AUTO_TEST_CASE( test_solve_eigen_symm_2x2 ) {
	double l1, l2;
	double e1[2], e2[2];
	solve_eigen_symm_2x2(
		9.0 / 4.0, sqrt(3.0) / 4.0, 11.0 / 4.0,
		&l1,
		e1,
		&l2,
		e2
	);
	BOOST_CHECK_EQUAL(l1, 2);
	BOOST_CHECK_EQUAL(l2, 3);
	BOOST_CHECK_CLOSE(e1[0], -0.8660254037, 1e-8);
	BOOST_CHECK_EQUAL(e1[1], 0.5);
	BOOST_CHECK_EQUAL(e2[0], 0.5);
	BOOST_CHECK_CLOSE(e2[1], 0.8660254037, 1e-8);

	solve_eigen_symm_2x2(
		11.0 / 4.0, -sqrt(3.0) / 4.0, 9.0 / 4.0,
		&l1,
		e1,
		&l2,
		e2
	);
	BOOST_CHECK_EQUAL(l1, 2);
	BOOST_CHECK_EQUAL(l2, 3);
	BOOST_CHECK_EQUAL(e1[0], -0.5);
	BOOST_CHECK_CLOSE(e1[1], -0.8660254037, 1e-8);
	BOOST_CHECK_CLOSE(e2[0], 0.8660254037, 1e-8);
	BOOST_CHECK_EQUAL(e2[1], -0.5);


	solve_eigen_symm_2x2(
		2, 1e-8, 3,
		&l1,
		e1,
		&l2,
		e2
	);
	BOOST_CHECK_EQUAL(l1, 2);
	BOOST_CHECK_EQUAL(l2, 3);
	BOOST_CHECK_EQUAL(e1[0], 1);
	BOOST_CHECK_EQUAL(e1[1], 0);
	BOOST_CHECK_EQUAL(e2[0], 0);
	BOOST_CHECK_EQUAL(e2[1], 1);

	solve_eigen_symm_2x2(
		3, 1e-8, 2,
		&l1,
		e1,
		&l2,
		e2
		);
	BOOST_CHECK_EQUAL(l1, 2);
	BOOST_CHECK_EQUAL(l2, 3);
	BOOST_CHECK_EQUAL(e1[0], 0);
	BOOST_CHECK_EQUAL(e1[1], 1);
	BOOST_CHECK_EQUAL(e2[0], 1);
	BOOST_CHECK_EQUAL(e2[1], 0);
}
