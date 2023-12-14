project (prog)

set( CMAKE_CXX_STANDARD 17)
#set( CMAKE_CXX_FLAGS "${ CMAKE_CXX_FLAGS } -std=c++17")

set( SOURCE_FILES main.cpp foo.cpp foo.h)

add_executable (prog ${ SOURCE_FILES })