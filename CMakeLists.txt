cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME BatchCommandHandler)
set(LIBRARY_NAME async)

if(DEFINED ENV{GITHUB_RUN_NUMBER})
    project(${PROJECT_NAME} VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
else()
    project(${PROJECT_NAME})
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB HRDS
    include/*.h
)
file(GLOB SRCS
    src/*.cpp
)

add_library(${LIBRARY_NAME} STATIC  src/async.cpp  include/async.h)

add_executable(${PROJECT_NAME} ${SRCS} )

target_include_directories(${PROJECT_NAME}
    PUBLIC "${CMAKE_BINARY_DIR}"
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARY_NAME})

target_link_libraries(${PROJECT_NAME} PUBLIC pthread)
target_include_directories(${LIBRARY_NAME} PRIVATE "${CMAKE_BINARY_DIR}")
target_include_directories(${LIBRARY_NAME} PRIVATE "${PATHS}")

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
    )
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
install(TARGETS ${LIBRARY_NAME} LIBRARY DESTINATION lib)


set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
