# CMakeList.txt : CMake project for Patterns

cmake_minimum_required (VERSION 3.8)

project (Patterns VERSION 0.1.0)

# Set the source files
set(SOURCES
    Sources/Patterns.h
    Sources/Patterns.cpp
    Sources/ChainOfResponsibility.h
)

# Get the current Git commit hash
execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the commit message of the current Git commit
execute_process(
    COMMAND git log -1 --pretty=format:%s
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_MESSAGE
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the author of the current Git commit
execute_process(
    COMMAND git log -1 --pretty=format:%an
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_AUTHOR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the commit time of the current Git commit
execute_process(
    COMMAND git log -1 --pretty=format:%ci
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_TIME
    OUTPUT_STRIP_TRAILING_WHITESPACE
)



# Add the commit hash and author to the preprocessor definitions
add_definitions(-DGIT_COMMIT_HASH="${GIT_COMMIT_HASH}")
add_definitions(-DGIT_COMMIT_AUTHOR="${GIT_COMMIT_AUTHOR}")
add_definitions(-DGIT_COMMIT_TIME="${GIT_COMMIT_TIME}")
add_definitions(-DGIT_COMMIT_MESSAGE="${GIT_COMMIT_MESSAGE}")

configure_file(PatternsConfig.h.in Sources/PatternsConfig.h)

add_executable(Patterns ${SOURCES})

target_include_directories(Patterns PRIVATE ${PROJECT_BINARY_DIR}/Sources)
