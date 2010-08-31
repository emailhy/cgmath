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
#include <cgmath/solve_eigen.h>
#include <cmath>

namespace cgmath {

    void solve_eigen_symm_2x2 ( double E, double F, double G, 
                                double* lambda1, double *e1, 
                                double* lambda2, double *e2 ) {
        if (fabs(F) <= 1e-7) {
			if (E < G) {
				if (lambda1) *lambda1 = E; 
				if (lambda2) *lambda2 = G; 
				if (e1) {
					e1[0] = 1; 
					e1[1] = 0;
				}
				if (e2) {
					e2[0] = 0; 
					e2[1] = 1;
				}
			} else {
				if (lambda1) *lambda1 = G; 
				if (lambda2) *lambda2 = E; 
				if (e1) {
					e1[0] = 0; 
					e1[1] = 1;
				}
				if (e2) {
					e2[0] = 1; 
					e2[1] = 0;
				}
			}
        } else {
            double tr2 = (E + G) / 2;
			double det = E * G - F * F;
            double s = sqrt( tr2 * tr2 - det ); 
            *lambda1 = tr2 - s;
            *lambda2 = tr2 + s;
    
            double eg2 = (E - G) / 2;
            if (eg2 < 0) {
                e1[0] = +eg2 - s;
                e1[1] = F;
				e2[0] = F;
				e2[1] = -eg2 + s;
            } else {
                e1[0] = F;
                e1[1] = -eg2 - s;
				e2[0] = +eg2 + s;
				e2[1] = F;
            }
    
            double l;
            l = sqrt(e1[0] * e1[0] + e1[1] * e1[1]);
            e1[0] /= l;
            e1[1] /= l;
            l = sqrt(e2[0] * e2[0] + e2[1] * e2[1]);
            e2[0] /= l;
            e2[1] /= l;
        }
    }

}
