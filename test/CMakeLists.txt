OPTION(cgmath_ENABLE_TESTS "Build test suite" OFF)
IF(cgmath_ENABLE_TESTS)
    SET(Boost_ADDITIONAL_VERSIONS "1.47" REQUIRED)
    FIND_PACKAGE(Boost)
    
    INCLUDE_DIRECTORIES( 
        ${cgmath_SOURCE_DIR} 
        ${Boost_INCLUDE_DIR})

    ADD_DEFINITIONS(-DBOOST_TEST_NO_LIB)

    FILE(GLOB_RECURSE sources *.c *.cpp *.h)
    SOURCE_GROUP(src REGULAR_EXPRESSION "c$|cpp$|h$")

    ADD_EXECUTABLE(test ${sources})

    TARGET_LINK_LIBRARIES(test cgmath)
    IF(MSVC)
        SET_TARGET_PROPERTIES(test PROPERTIES COMPILE_FLAGS "/EHa")
    ENDIF(MSVC)

    IF(MSVC_IDE)
        ADD_CUSTOM_COMMAND(TARGET test
            POST_BUILD
            COMMAND "${CMAKE_CURRENT_BINARY_DIR}/$(ConfigurationName)/test.exe")
    ENDIF(MSVC_IDE)
ENDIF()