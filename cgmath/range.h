/*
    Copyright (C) 2007-2011 by Jan Eric Kyprianidis <www.kyprianidis.com>
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
#ifndef CGMATH_INCLUDED_RANGE_H
#define CGMATH_INCLUDED_RANGE_H

#include <limits>

namespace cgmath {

    template <typename T> class Range {
    public:
        typedef T value_type;
        
        Range()
            : a(std::numeric_limits<T>::max()), b(-std::numeric_limits<T>::max()) { }

        Range(T x)
            : a(x), b(x) { }

        Range(T x, T y) { 
            if (x < y) {
                a = x;
                b = y;
            } else {
                a = y;
                b = x;
            }
        }

        bool operator==( const Range<T>& r ) const {
            return (a == r.a) && (b == r.b);
        }

        bool operator!=( const Range<T>& r ) const {
            return !this->operator==(r);
        }

        T size() const {
            return (b - a);
        }

        T start() const {
            return a;
        }

        T end() const {
            return b;
        }

        T center() const {
            return (a + b) / 2;
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

        bool contains(const Range<T>& r) const {
            return ((a <= r.a) && (r.b <= b));    
        }

        bool intersects(const Range<T>& r) const {
            return (contains(r.a) || contains(r.b));
        }

        const Range<T> operator+( T s ) const {
            return Range<T>(a + s, b + s);
        }

        const Range<T> operator-( T s ) const {
            return Range<T>(a - s, b - s);
        }

        const Range<T> operator*( T s ) const {
            return Range<T>(a * s, b * s);
        }

        const Range<T> operator/( T s ) const {
            return Range<T>(a / s, b / s);
        }

        const Range<T> expanded( T dt ) {
            return Range<T>(
                (a != std::numeric_limits<T>::max())? a - dt : a,
                (b != -std::numeric_limits<T>::max()) b + dt : b
            );
        }

        const Range<T> united( T x ) {
            return Range<T>(std::min(a, x), std::max(b, x));
        }

        const Range<T> united( const Range<T>& r ) {
            return Range<T>(std::min(a, r.a), std::max(b, r.b));
        }

        const Range<T> intersected(const Range<T>& r) {
            return Range<T>(std::max(a, r.a), std::min(b, r.b));
        }

    private:
        T a;
        T b;
    };

    template<typename T> std::ostream& operator<<(std::ostream& os, const Range<T>& r) {
        return (os << r.start() << " " << r.end());
    }

    template<typename T> std::istream& operator>>(std::istream& is, Range<T>& r) {
        T a, b;
        is >> a >> b;
        if (a < b) 
            r.set(a, b);
        else 
            r.clear();
        return is;
    }
} 

#endif
