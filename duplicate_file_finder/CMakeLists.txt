cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(bayan VERSION ${PROJECT_VERSION})

add_executable(bayan main.cpp)

file(GLOB_RECURSE ENDF6_SRC ${PROJECT_SOURCE_DIR} src/*.h src/*.cpp)

add_library(bayan_lib ${ENDF6_SRC})
find_package(Boost COMPONENTS program_options regex filesystem REQUIRED )
include_directories(${Boost_INCLUDE_DIR})

target_link_libraries(bayan bayan_lib
    ${Boost_LIBRARIES}
)

set_target_properties(bayan bayan_lib PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(bayan
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_compile_options(bayan PRIVATE
    -Wall -Wextra -pedantic -Werror
)

target_compile_options(bayan_lib PRIVATE
    -Wall -Wextra -pedantic -Werror
)

install(TARGETS bayan RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
