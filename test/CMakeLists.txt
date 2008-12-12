FIND_PATH(BOOST_INCLUDE_DIR boost/test/unit_test.hpp
	PATH_SUFFIXES
	boost_1_36_0 boost_1_36_1 boost_1_37_0
	PATHS
	"$ENV{PROGRAMFILES}/boost"
	/usr/local
)

INCLUDE_DIRECTORIES( ${cgmath_SOURCE_DIR} ${BOOST_INCLUDE_DIR} )
ADD_DEFINITIONS(-DBOOST_TEST_NO_LIB)

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
