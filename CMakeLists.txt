cmake_minimum_required(VERSION 3.10)

project(convert_image)

# public server not showing full path
set(OpenCV_DIR ../../../github/build_opencv)

find_package(OpenCV REQUIRED )

# public server not showing full path
include_directories( ../../../github/opencv/include)

add_executable(convert_image src/main.cpp)

# public server not showing full path
target_link_libraries(convert_image ../../../../github/build_opencv/lib)