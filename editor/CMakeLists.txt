cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(editor VERSION ${PROJECT_VERSION})

add_executable(editor main.cpp)

#file(GLOB_RECURSE editor_lib_SRC CONFIGURE_DEPENDS "*.h" "*.cpp")
file(GLOB_RECURSE ENDF6_SRC ${PROJECT_SOURCE_DIR} *.h *.cpp)

add_library(editor_src ${ENDF6_SRC})

target_link_libraries(editor
    editor_src
)

set_target_properties(editor editor_src PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(editor
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_compile_options(editor PRIVATE
    -Wall -Wextra -pedantic -Werror
)

target_compile_options(editor_src PRIVATE
    -Wall -Wextra -pedantic -Werror
)

install(TARGETS editor RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
