INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/.. )
ADD_LIBRARY(cgmath STATIC 
    types.h
    range.h
    vec2.h
    vec3.h
    vec4.h
    float_util.h
    quat.h
    mat22.h
    mat33.h
    mat44.h
    mat44_util.h
    determinant.h
    box3.h
    noise.h
    noise.cpp
    perlin.h
    perlin_improved.cpp
    perlin_original.cpp
    perlin_simplex.cpp
    solve_eqn.h
    solve_eqn.cpp
    solve_eigen.h
    solve_eigen.cpp
    timer.h
    timer.cpp)
