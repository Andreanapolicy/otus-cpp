cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(matrix VERSION ${PROJECT_VERSION})

add_executable(matrix main.cpp)

file(GLOB_RECURSE ENDF6_SRC ${PROJECT_SOURCE_DIR} *.h *.cpp)

add_library(matrix_lib ${ENDF6_SRC})

target_link_libraries(matrix
matrix_lib
)

set_target_properties(matrix matrix_lib PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(matrix
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_compile_options(matrix PRIVATE
    -Wall -Wextra -pedantic -Werror
)

target_compile_options(matrix_lib PRIVATE
    -Wall -Wextra -pedantic -Werror
)

install(TARGETS matrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
