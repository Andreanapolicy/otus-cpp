cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(bulk VERSION ${PROJECT_VERSION})

add_executable(bulk main.cpp)

file(GLOB_RECURSE ENDF6_SRC ${PROJECT_SOURCE_DIR} src/*.h src/*.cpp)

add_library(bulk_lib ${ENDF6_SRC})

target_link_libraries(bulk bulk_lib)

set_target_properties(bulk bulk_lib PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(bulk
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_compile_options(bulk PRIVATE
    -Wall -Wextra -pedantic -Werror
)

target_compile_options(bulk_lib PRIVATE
    -Wall -Wextra -pedantic -Werror
)

install(TARGETS bulk RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
