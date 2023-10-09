cmake_minimum_required(VERSION 3.0) # version of cmake
project(Path_Tracer) # name of the exe
set(CMAKE_CXX_STANDARD 20) # set the c++ version

# Generating a JSON compilation database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set all warning flags 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")

# set file paths
set(src_dir "${PROJECT_SOURCE_DIR}/src/")
set(include_dir "${PROJECT_SOURCE_DIR}/include/")

# get the files
file (GLOB source_files "${src_dir}/*.cc")
file (GLOB include_files "${include_dir}/*.h")

add_executable(${PROJECT_NAME} ${source_files} ${include_files}) 