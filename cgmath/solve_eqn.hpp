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
#ifndef LIBMATH3D_INCLUDED_SOLVE_EQN_HPP
#define LIBMATH3D_INCLUDED_SOLVE_EQN_HPP

#include <math3d/types.hpp>
#include <GL/glew.h>

namespace math3d {

    bool solve_eqn_linear( double a, double b, double *x );
    bool solve_eqn_quadratic( double a, double b, double c, double *x1, double *x2 );
    bool solve_eqn_cubic( double a, double b, double c, double d, double *x1, double *x2, double *x3 );

} 
#endif