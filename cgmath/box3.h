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
#ifndef CGMATH_INCLUDED_BOX3_H
#define CGMATH_INCLUDED_BOX3_H

#if 0
#include <cgmath/range.hpp>
#include <cgmath/vec3.hpp>

namespace cgmath {
    class mat33;
    class mat44;

    /// 3-dimensional bounding box class
    class box3 {
    public:
        box3() 
            : x(), y(), z() {}

        template <typename T> box3( const vec3<T>& v )
            : x(v.x), y(v.y), z(v.z) {}

        template <typename T> box3( const vec3<T>& v, const vec3<T>& w )
            : x(v.x, w.x), y(v.y, w.y), z(v.z, w.z) {}

        bool operator==( const box3 &b ) const {
        }

        bool operator!=( const box3 &b ) const {
            return !this->operator==(b);
        }

        bool is_empty() const {
            return x.is_empty() && y.is_empty() && z.is_empty();
        }

        bool is_point() const {
            return x.is_point() && y.is_point() && z.is_point();
        }

        template <typename T> bool contains( const vec3<T> &v ) const {
            return x.contains(v.x) && y.contains(v.y) && z.contains(v.z);
        }

        bool contains( const box3 &b ) const {
            return x.contains(b.x) && y.contains(b.y) && z.contains(b.z);
        }

        bool intersects( const box3 &b ) const {
            return x.intersects(b.x) && y.intersects(b.y) && z.intersects(b.z);
        }

        vec3<> get_min() const {
            return vec3<>(x.get_min(), y.get_min(), z.get_min());
        }

        vec3<> get_max() const {
            return vec3<>(x.get_max(), y.get_max(), z.get_max());
        }

        vec3<> get_center() const {
            return vec3<>(x.get_center(), y.get_center(), z.get_center());
        }

        vec3<> get_size() const {
            return vec3<>(x.get_size(), y.get_size(), z.get_size());
        }

        double get_volume() const {
            vec3<> sz = get_size();
            return sz.x * sz.y * sz.z;
        }

        void clear() {
            x.clear();
            y.clear();
            z.clear();
        }

        void set( const vec3<>& v ) {
            x.set(v.x);
            y.set(v.y);
            z.set(v.z);
        }

        void set( const vec3<>& v, const vec3<>& w ) {
            x.set(v.x, w.x);
            y.set(v.y, w.y);
            z.set(v.z, w.z);
        }

        template <typename T> box3& extend_by( const vec3<T>& v ) {
            x.extend_by(v.x);
            y.extend_by(v.y);
            z.extend_by(v.z);
            return *this;
        }

        box3& extend_by( const box3& b ) {
            x.extend_by(b.x);
            y.extend_by(b.y);
            z.extend_by(b.z);
            return *this;
        }

        box3& expand( double dt ) {
            x.expand(dt);
            y.expand(dt);
            z.expand(dt);
            return *this;
        }
        
        box3& expand( double dx, double dy, double dz ) {
            x.expand(dx);
            y.expand(dy);
            z.expand(dz);
            return *this;
        }

        box3& transform_by( const mat33& m );
        box3& transform_by( const mat44& m );

        vec3<> clip( const vec3<>& v ) const;
        vec3<> closest_point( const vec3<>& v ) const;
        vec3<> project_to_boundary( const vec3<>& v ) const;

    private:
        range<double> x;
        range<double> y;
        range<double> z;
    };

    /*
    std::ostream& operator<<( std::ostream& os, const box3& b );
    std::istream& operator>>( std::istream& is, box3& b );
    */
} 
#endif
#endif

