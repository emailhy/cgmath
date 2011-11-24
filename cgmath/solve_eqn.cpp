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
#include <cgmath/solve_eqn.h>
#include <cmath>


//
// Calculates the real roots of a quadratic equation: ax^2 + bx + c = 0.
// 
// James F. Blinn, "How to solve a Quadratic Equation", 
// IEEE Computer Graphics and Applications, 
// vol. 25,  no. 6,  pp. 76-79, 2005. 
//
bool cgmath::solve_eqn_quadratic ( double a, double b, double c, 
                                   double *x1, double *x2 ) 
{
    if (a != 0) {
        double B = b / 2;
        double d = B*B - a*c;

        if (d < 0) 
            return false;   

        if (B > 0) {
            double q = B + sqrt(d);
            *x1 = -c / q;
            *x2 = -q / a;
        } else if (B < 0) {
            double q = -B + sqrt(d);
            *x1 = q / a;
            *x2 = c / q;
        } else {
            *x1 = sqrt(d) / a;
            *x2 = -*x1;
        }

    } else if (b != 0) {
        *x1 = *x2 = -c / b;
    } else {
        return false;
    }

    return true;
}


//TODO
/*
bool solve_eqn_cubic( double a, double b, double c, double d, double *x1, double *x2, double *x3 ) {
}
*/
