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
#ifndef CGMATH_INCLUDED_DETERMINANT_HPP
#define CGMATH_INCLUDED_DETERMINANT_HPP

namespace cgmath {

    template <typename T> T determinant_2x2 ( T a, T b, T c, T d ) {
        return a * d - b * c;
    }

    template <typename T> T determinant_3x3 ( T a1, T a2, T a3, 
                                              T b1, T b2, T b3, 
                                              T c1, T c2, T c3) {
        return  a1 * det2x2(b2, b3, c2, c3) - 
                b1 * det2x2(a2, a3, c2, c3) + 
                c1 * det2x2(a2, a3, b2, b3);
    }

}

#endif
