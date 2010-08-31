/*
    Copyright (C) 2007 by Jan Eric Kyprianidis <www.kyprianidis.com>
    All rights reserved.
*/
#ifndef CGMATH_INCLUDED_PERLIN_HPP
#define CGMATH_INCLUDED_PERLIN_HPP

namespace cgmath {

    float perlin_original_noise1( float x );
    float perlin_original_noise2( float x, float y );
    float perlin_original_noise3( float x, float y, float z );

    double perlin_improved_noise3( double x, double y, double z );
    double perlin_simplex_noise3( double x, double y, double z );

}

#endif

