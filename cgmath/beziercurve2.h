/*
    Copyright (C) 2011 by Jan Eric Kyprianidis <www.kyprianidis.com>
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
#pragma once

#include <cgmath/vec2.h>

namespace cgmath {

    template <typename T> class BezierCurve2 {
    public:
        typedef T value_type;
        
        BezierCurve2() {}

        BezierCurve2( const Vec2<T>& p0,  const Vec2<T>& p3 ) {
            p[0] = p[1] = p0; p[2] = p[3] = p3;
        }

        BezierCurve2( const Vec2<T>& p0,  const Vec2<T>& p1, 
                      const Vec2<T>& p2, const Vec2<T>& p3 ) 
        {
            p[0] = p0; p[1] = p1; p[2] = p2; p[3] = p3;
        }

        Vec2<T>& operator[](int index) {
            return p[index];
        }

        const Vec2<T>& operator[](int index) const {
            return p[index];
        }

        Vec2<T> blossom(T t1, T t2, T t3) const {
	        T s1 = 1 - t1;
            Vec2<T> q0 = s1 * p[0] + t1 * p[1];
	        Vec2<T> q1 = s1 * p[1] + t1 * p[2];
	        Vec2<T> q2 = s1 * p[2] + t1 * p[3];

	        T s2 = 1 - t2;
	        Vec2<T> r0 = s2 * q0 + t2 * q1;
	        Vec2<T> r1 = s2 * q1 + t2 * q2;

	        return (1 - t3) * r0 + t3 * r1;
        }

        Vec2<T> eval(T t) const {
            T s = 1 - t;
            return s*s*s*p[0] + 3*t*s*s*p[1] + 3*t*t*s*p[2] + t*t*t*p[3];
        }

        void split(BezierCurve2 *c1, BezierCurve2 *c2) const {
            qreal c = (p[1] + p[2]) / 2;

            c1->p[0] = p[0];
            c1->p[1] = (p[0] + p[1]) / 2;
            c1->p[2] = (p[2] + 2*p[1] + p[0]) / 4;
            c1->p[3] = (p[0] + 3*(p[1] + p[2]) + p[4]) / 8;

            c2->p[0] = c1->p[3];
            c2->p[1] = (p[1] + 2*p[2] + p[3]) / 4;
            c2->p[2] = (p[2] + p[3]) / 2;
            c2->p[3] = p[3];
        }

    private:
        Vec2<T> p[4];
    };

    typedef BezierCurve2<float> BezierCurve2f;
    typedef BezierCurve2<double> BezierCurve2d;
} 
