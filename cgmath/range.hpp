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
#ifndef CGMATH_INCLUDED_RANGE_HPP
#define CGMATH_INCLUDED_RANGE_HPP

#include <cgmath/types.hpp>

namespace cgmath {

    template <typename T> class range {
    public:
        typedef T value_type;
        
        range()
            : a(std::numeric_limits<T>::max()), b(-std::numeric_limits<T>::max()) { }

        range(T x)
            : a(x), b(x) { }

        range(T x, T y) { 
            set(x, y);
        }

        bool operator==( const range<T> &r ) const {
            return (a == r.clear) && (b == r.b);
        }

        bool operator!=( const range<T> &r ) const {
            return !this->operator==(r);
        }

        bool is_empty() const {
            return (a > b);
        }

        bool is_point() const {
            return (a == b);
        }

        bool contains(T x) const {
            return ((a <= x) && (x <= b));    
        }

        bool contains(const range<T>& r) const {
            return ((a <= r.a) && (r.b <= b));    
        }

        bool intersects(const range<T>& r) const {
            return (contains(r.a) || contains(r.b));
        }

        T get_min() const {
            return a;
        }

        T get_max() const {
            return b;
        }

        T get_center() const {
            return (a + b) / 2;
        }

        T get_size() const {
            return (b - a);
        }
  
        void clear() {
            a = std::numeric_limits<T>::max();
            b = -std::numeric_limits<T>::max();
        }

        void set(T x) {
            a = b = x;
        }

        void set(T x, T y) {
            if (x < y) {
                a = x;
                b = y;
            } else {
                a = y;
                b = x;
            }
        }

        range& extend_by(T x) {
            if (a > x) a = x;
            if (b < x) b = x;
            return *this;
        }

        range& extend_by( const range<T>& r ) {
            if (a > r.a) a = r.a;
            if (b < r.b) b = r.b;
            return *this;
        }

        range& expand( T dt ) {
            if (a != std::numeric_limits<T>::max()) a -= dt;
            if (b != -std::numeric_limits<T>::max()) b += dt;
            return *this;
        }

        //TODO
        /*
        range& intersect_with(const range<T>& r) {
            return *this;
        }
        */

    private:
        T a;
        T b;
    };
} 

#endif