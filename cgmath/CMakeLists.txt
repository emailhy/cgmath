INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/.. )
ADD_LIBRARY(cgmath STATIC 
	types.hpp
	range.hpp
	vec2.hpp
	vec3.hpp
	float_util.hpp
	vec2_util.hpp
	vec3_util.hpp
	quat.hpp
	mat33.hpp
	mat44.hpp
	mat33_util.hpp
	mat44_util.hpp
	determinant.hpp
	box3.hpp
	noise.hpp
	noise.cpp
	perlin.hpp
	perlin_improved.cpp
	perlin_original.cpp
	perlin_simplex.cpp
	solve_eqn.cpp
	solve_eqn.hpp
	solve_eigen.cpp
	solve_eigen.hpp
	timer.hpp
	timer.cpp)
