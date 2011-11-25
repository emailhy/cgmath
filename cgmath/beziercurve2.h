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

        Vec2<T>& operator[] (int index ) {
            return p[index];
        }

        const Vec2<T>& operator[]( int index ) const {
            return p[index];
        }

        T poly_length() const {
            return distance(p[0], p[1]) + distance(p[1], p[2]) + distance(p[2], p[3]);
        }

        T chord_length() const {
            return distance(p[0], p[3]);
        }

        T arc_length( T t, T eps=1e-1 ) const {
            return left(t).length(eps);
        }

        T length( T eps=1e-1 ) const {
            T Lp = poly_length();
            T Lc = chord_length();
            if (Lp - Lc < eps) {
                return (2*Lc + 3*Lp) / 5;
            }
            BezierCurve2 l,r;
            split(&l, &r);
            return l.length(eps/2) + r.length(eps/2);
        }

        T parameter_at_length( T len, T eps=1e-1 ) const { // FIXME
            if (len <= 0) return 0;
            if (len >= length()) return 1;
            T max_t = 1;
            T t = static_cast<T>(0.5);
            for (;;) {
                T slen = arc_length(t);
                if (abs(slen - len) < eps) {
                    return t;
                }

                if (slen < len) {
                    t += (max_t - t) / 2;
                } else {
                    max_t = t;
                    t /= 2;
                }
            }
        }

        Vec2<T> blossom( T t1, T t2, T t3 ) const {
	        T s1 = 1 - t1;
            Vec2<T> q0 = s1 * p[0] + t1 * p[1];
	        Vec2<T> q1 = s1 * p[1] + t1 * p[2];
	        Vec2<T> q2 = s1 * p[2] + t1 * p[3];

	        T s2 = 1 - t2;
	        Vec2<T> r0 = s2 * q0 + t2 * q1;
	        Vec2<T> r1 = s2 * q1 + t2 * q2;

	        return (1 - t3) * r0 + t3 * r1;
        }

        Vec2<T> operator()( T t ) const {
            return eval(t);
        }

        Vec2<T> eval( T t ) const {
            T s = 1 - t;
            return s*s*s*p[0] + 3*t*s*s*p[1] + 3*t*t*s*p[2] + t*t*t*p[3];
        }

        Vec2<T> first_derivative( T t ) const {
            T s = 1 - t;
            return -3*s*s * p[0] + 
                   (3*s*s - 6*s*t) * p[1] +
                   (6*s*t - 3*t*t) * p[2] +
                   3*t*t * p[3];
        }

        Vec2<T> second_derivative( T t ) const {
            T s = 1 - t;
            return 6*s * p[0] + 
                   (6*t - 12*s) * p[1] +
                   (6*s - 12*t) * p[2] +
                   6*t * p[3];
        }

        Vec2<T> normal( T t ) const {
            Vec2<T> tn = normalize(first_derivative(t));
            return Vec2<T>(tn.y, -tn.x);
        }

        void split( BezierCurve2 *c1, BezierCurve2 *c2 ) const {
            Vec2<T> q0 = (p[0] + p[1]) / 2;
	        Vec2<T> q1 = (p[1] + p[2]) / 2;
	        Vec2<T> q2 = (p[2] + p[3]) / 2;
	        Vec2<T> r0 = (q0 + q1) / 2;
	        Vec2<T> r1 = (q1 + q2) / 2;
	        Vec2<T> s0 = (r0 + r1) / 2;

            c1->p[0] = p[0];
            c1->p[1] = q0;
            c1->p[2] = r0;
            c1->p[3] = s0;

            c2->p[0] = s0;
            c2->p[1] = r1;
            c2->p[2] = q2;
            c2->p[3] = p[3];
        }

        BezierCurve2 left( T t = static_cast<T>(0.5) ) const {
            T s = 1 - t;
            Vec2<T> q0 = s*p[0] + t*p[1];
	        Vec2<T> q1 = s*p[1] + t*p[2];
	        Vec2<T> q2 = s*p[2] + t*p[3];
	        Vec2<T> r0 = s*q0 + t*q1;
	        Vec2<T> r1 = s*q1 + t*q2;
	        Vec2<T> s0 = s*r0 + t*r1;
            return BezierCurve2(p[0], q0, r0, s0);
        }

        BezierCurve2 right( T t = static_cast<T>(0.5) ) const {
            T s = 1 - t;
            Vec2<T> q0 = s*p[0] + t*p[1];
	        Vec2<T> q1 = s*p[1] + t*p[2];
	        Vec2<T> q2 = s*p[2] + t*p[3];
	        Vec2<T> r0 = s*q0 + t*q1;
	        Vec2<T> r1 = s*q1 + t*q2;
	        Vec2<T> s0 = s*r0 + t*r1;
            return BezierCurve2(s0, r1, q20, p[3]);
        }

        void divide( BezierCurve2 *c1, BezierCurve2 *c2, T t ) const {
            T s = 1 - t;
            Vec2<T> q0 = s*p[0] + t*p[1];
	        Vec2<T> q1 = s*p[1] + t*p[2];
	        Vec2<T> q2 = s*p[2] + t*p[3];
	        Vec2<T> r0 = s*q0 + t*q1;
	        Vec2<T> r1 = s*q1 + t*q2;
	        Vec2<T> s0 = s*r0 + t*r1;

            c1->p[0] = p[0];
            c1->p[1] = q0;
            c1->p[2] = r0;
            c1->p[3] = s0;

            c2->p[0] = s0;
            c2->p[1] = r1;
            c2->p[2] = q2;
            c2->p[3] = p[3];
        }

        BezierCurve2 segment( T t0, T t1 ) const {
            return BezierCurve2(eval(t0), blossom(t0,t0,t1), blossom(t0,t1,t1), eval(t1));
        }

    private:
        Vec2<T> p[4];
    };

    typedef BezierCurve2<float> BezierCurve2f;
    typedef BezierCurve2<double> BezierCurve2d;
} 
