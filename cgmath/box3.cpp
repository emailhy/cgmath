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
#include <math3d/types.hpp>
#include <math3d/box3.hpp>
#include <iostream>

namespace math3d {

    double box3::get_volume() const {
        vec3<> sz = get_size();
        return sz.x * sz.y * sz.z;
    }


    box3& box3::expand( double dt ) {
        x.expand(dt);
        y.expand(dt);
        z.expand(dt);
        return *this;
    }


    box3& box3::expand( double dx, double dy, double dz ) {
        x.expand(dx);
        y.expand(dy);
        z.expand(dz);
        return *this;
    }


    /*
    box3& box3::transform_by( const mat33 &m ) {

    }

    box3& box3::transform_by( const mat44 &m ) {

    }


    vec3 box3::clip( const vec3<>& v ) const {

    }


    vec3 box3::closest_point( const vec3<>& v ) const {

    }


    vec3 box3::project_to_boundary( const vec3<>& v ) const {

    }
    */
}


