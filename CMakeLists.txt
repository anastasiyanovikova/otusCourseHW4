cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "5" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(print_ip VERSION ${PROJECT_VESRION})

add_executable(print_ip main.cpp)
add_library(print_iplib printIplib.cpp)

set_target_properties(print_iplib print_ip PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(print_iplib
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(print_ip
print_iplib
)

if (MSVC)
    target_compile_options(print_iplib PRIVATE
        /W4
    )
    target_compile_options(print_ip PRIVATE
        /W4
    )
else ()
    target_compile_options(print_iplib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(print_ip PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "NN")
include(CPack)
