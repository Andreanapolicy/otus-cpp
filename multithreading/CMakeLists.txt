cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(async VERSION ${PROJECT_VERSION})

add_executable(async_cli main.cpp)

file(GLOB_RECURSE ENDF6_SRC ${PROJECT_SOURCE_DIR} src/*.h src/*.cpp)

add_library(async ${ENDF6_SRC})
find_package(Boost 1.74.0 COMPONENTS program_options regex filesystem REQUIRED )
include_directories(${Boost_INCLUDE_DIR})

target_link_libraries(async_cli async
    ${Boost_LIBRARIES}
)

set_target_properties(async_cli async PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(async PROPERTIES PUBLIC_HEADER async.h)

target_include_directories(async_cli
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_compile_options(async_cli PRIVATE
    -Wall -Wextra -pedantic -Werror
)

target_compile_options(async PRIVATE
    -Wall -Wextra -pedantic -Werror
)

install(TARGETS async LIBRARY DESTINATION bin)
install(TARGETS async LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION include)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
