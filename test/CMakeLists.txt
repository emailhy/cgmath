INCLUDE_DIRECTORIES( ${cgmath_SOURCE_DIR} )
ADD_EXECUTABLE(test
	main.cpp
	test_vec3.cpp
	#test_mat33.cpp
	test_solve_eqn.cpp
)
TARGET_LINK_LIBRARIES(test cgmath)
IF (MSVC)
	SET_TARGET_PROPERTIES(test PROPERTIES COMPILE_FLAGS "/EHa")
ENDIF(MSVC)
