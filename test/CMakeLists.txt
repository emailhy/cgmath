FIND_PACKAGE(Boost)

INCLUDE_DIRECTORIES( 
    ${cgmath_SOURCE_DIR} 
    ${Boost_INCLUDE_DIR})

ADD_DEFINITIONS(-DBOOST_TEST_NO_LIB)

ADD_EXECUTABLE(test
    main.cpp
    test_range.cpp
    test_vec2.cpp
    test_vec2_util.cpp
    test_vec3.cpp
    test_vec3_util.cpp
    test_mat33.cpp
    test_solve_eqn.cpp
    test_solve_eigen.cpp)

TARGET_LINK_LIBRARIES(test cgmath)
IF(MSVC)
    SET_TARGET_PROPERTIES(test PROPERTIES COMPILE_FLAGS "/EHa")
ENDIF(MSVC)

IF(MSVC_IDE)
    ADD_CUSTOM_COMMAND(TARGET test
	    POST_BUILD
        COMMAND "${CMAKE_CURRENT_BINARY_DIR}/$(ConfigurationName)/test.exe")
ENDIF(MSVC_IDE)
