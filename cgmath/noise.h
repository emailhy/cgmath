/*
    Copyright (C) 2007 by Jan Eric Kyprianidis <www.kyprianidis.com>
    All rights reserved.
*/
#ifndef CGMATH_INCLUDED_NOISE_HPP
#define CGMATH_INCLUDED_NOISE_HPP

namespace cgmath {

    float noise( float x );
    float noise( float x, float y );
    float noise( float x, float y, float z );
    float noise( float x, float y, float z, float w );
    
    float pnoise( float x, int px );
    float pnoise( float x, float y, int px, int py );
    float pnoise( float x, float y, float z, int px, int py, int pz);
    float pnoise( float x, float y, float z, float w, int px, int py, int pz, int pw );

}

#endif

