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

set(project_sources
    batch_command.cpp
    batch_command_handler.cpp
    tokenizer.cpp
    Output/console_output.cpp
    Output/logfile_output.cpp
    main.cpp
    )


add_library(${LIBRARY_NAME} STATIC  async.cpp  async.h)

add_executable(${PROJECT_NAME} ${project_sources} )

target_include_directories(${PROJECT_NAME}
    PUBLIC "${CMAKE_BINARY_DIR}"
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${NAME_LIBRARY})
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
