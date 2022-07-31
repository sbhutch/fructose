###############################################################################
# Set project name.
###############################################################################
cmake_minimum_required(VERSION 3.14)
project(fructose)

###############################################################################
# Set project variables.
###############################################################################
set(CONTENT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/content)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)

###############################################################################
# Find external dependencies.
###############################################################################
find_package(SDL2 CONFIG REQUIRED)

###############################################################################
# Create target executable.
###############################################################################
file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

###############################################################################
# Set target dependencies.
###############################################################################
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)

###############################################################################
# Set target C++ standard.
###############################################################################
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

###############################################################################
# Set target warning flags.
###############################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
endif()

###############################################################################
# Copy content to target file directory.
###############################################################################
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CONTENT_DIR} $<TARGET_FILE_DIR:${PROJECT_NAME}>/content)
