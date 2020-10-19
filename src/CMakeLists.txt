cmake_minimum_required (VERSION 3.8)

set(BINARY ${CMAKE_PROJECT_NAME})
set(BINARY_LIB ${CMAKE_PROJECT_NAME}_lib)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true
    *.h
    *.cpp
)
set(SOURCES
    ${SOURCES}
)
set(EXECUTABLE_NAME ${BINARY})

# Create executable to run application
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Create lib for testing purposes
add_library(${BINARY_LIB} STATIC ${SOURCES})