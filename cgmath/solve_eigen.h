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
#ifndef CGMATH_INCLUDED_SOLVE_EIGEN_HPP
#define CGMATH_INCLUDED_SOLVE_EIGEN_HPP

namespace cgmath {

    void solve_eigen_symm_2x2 ( double E, double F, double G, 
                                double* lambda1, double *e1, 
                                double* lambda2, double *e2 );
}

#endif