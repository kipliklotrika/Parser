cmake_minimum_required(VERSION 3.5)

project(simpletest LANGUAGES CXX)

add_definitions(-DGTEST_LANGUAGE_CXX11)
set(CMAKE_CXX_STANDARD 11)

find_package(Threads REQUIRED)

if ($ENV{GOOGLETEST_DIR})
    set(GOOGLETEST_DIR $ENV{GOOGLETEST_DIR})
else ()
    if (NOT "/opt/local/src/googletest" STREQUAL "")
        message(WARNING "Using googletest src dir specified at Qt Creator wizard")
    endif ()
    set(GOOGLETEST_DIR "/opt/local/src/")
endif ()
if (EXISTS ${GOOGLETEST_DIR})
    set(GTestSrc ${GOOGLETEST_DIR}/googletest)
    set(GMockSrc ${GOOGLETEST_DIR}/googlemock)
elseif (UNIX AND EXISTS /usr/src/gtest)
    set(GTestSrc /usr/src/gtest)
    message(WARNING "Using gtest from system")
    if (EXISTS /usr/src/gmock)
        set(GMockSrc /usr/src/gmock)
    endif ()
else ()
    message( FATAL_ERROR "No googletest src dir found - set GOOGLETEST_DIR to enable!")
endif ()

set(GTestFiles ${GTestSrc}/src/gtest-all.cc)
set(GTestIncludes ${GTestSrc} ${GTestSrc}/include)
if (NOT ${GMockSrc} STREQUAL "")
    list(APPEND GTestFiles ${GMockSrc}/src/gmock-all.cc)
    list(APPEND GTestIncludes ${GMockSrc} ${GMockSrc}/include)
endif ()

set(ParserFiles ../astnode.h
    ../interpreter.cpp
    ../lexer.h
    ../number.h
    ../binaryoperator.cpp
    ../interpreter.h
    ../parser.cpp
    ../token.h
    ../astnode.cpp
    ../binaryoperator.h
    ../lexer.cpp
    ../number.cpp
    ../parser.h)
set(ParserIncludes ../)


include_directories(${GTestIncludes})
include_directories(${ParserIncludes})

add_executable(simpletest main.cpp tst_simpletest.h
               ${GTestFiles}
               ${ParserFiles})
add_test(NAME simpletest COMMAND simpletest)
target_link_libraries(simpletest PRIVATE Threads::Threads)

